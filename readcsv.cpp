#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include <algorithm>
#include<regex>
#include<stack>
using namespace std;
string xoaKhoangTrangDauCuoi(string str) {
    // Xóa khoảng trắng đầu chuỗi
    size_t viTriDau = str.find_first_not_of(" \t\n\r");
    if (viTriDau == string::npos) {
        // Nếu chuỗi chỉ chứa khoảng trắng, tab và dấu xuống dòng,
        // thì trả về chuỗi rỗng
        return "";
    }
    str = str.substr(viTriDau);

    // Xóa khoảng trắng cuối chuỗi
    size_t viTriCuoi = str.find_last_not_of(" \t\n\r");
    if (viTriCuoi != string::npos) {
        str = str.substr(0, viTriCuoi + 1);
    }

    return str;
}
string toLowerCase(const std::string &input) {
    string result = input;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}
string xu_ly_token(string s){
    // chưa có hàm lọc dấu cách thừa [   "---"   ] - DONE
    // 0 stand for error;
    // hàm này chưa xử lí trường hợp '\'
    // hàm này cout cả error
    int pre=0;
    while(s[pre]==' ')
    {
        pre++;
    }
    int pos=s.length()-1;
    while(s[pos]==' ')
    {
        pos--;
    }
    s=s.substr(pre,pos-pre+1);
    // xóa khoảng trắng đầu trắng cuối thừa
    //cout<<"s sau khi bien doi: ["<<s<<"]"<<endl;
    int so_ngoac=0;
    string token="";
    string error_token="";
    if(s[0]=='"' && s[s.length()-1]=='"') 
    {
        for(int i=1; i<s.length()-1; i++)
        {
            //std::cout<<"s["<<i<<"]: "<<s[i]<<endl;
            while(s[i]=='"' && i<s.length()-1)
            {
                so_ngoac++;
                i++;
            }
            //cout<<"so_ngoac: "<<so_ngoac<<endl;
            if(so_ngoac%2==0)
            {
                for(int j=0; j<(so_ngoac/2); j++)
                {
                    token+='"';
                }
                if(s[i]=='\\') 
                {
                    if(i+1<s.length()-1)
                    {
                        i++;
                        token+=s[i];
                    } 
                    else 
                    {
                        //cout<<"ERROR type 0:  ";
                        std::cout<<"ERROR: near \""<<error_token<<"\""<<endl;
                        token="";
                        return token;
                    }
                    
                }
                if(s[i]!='"') token+=s[i];
                if(s[i]!='"') error_token+=s[i];
                so_ngoac=0;
            }
            else if (so_ngoac%2!=0)
            {
                //cout<<"ERROR type 1: ";
                std::cout<<"ERROR: near \""<<error_token<<"\""<<endl;
                token="";
                return token;
            }
        }
        //cout<<"element sau khi push vao vector: ["<<token<<"]"<<endl;
    }
    else if(s[0]!='"' && s[s.length()-1]!='"')
    {
        for(int i=0; i<s.length(); i++)
        {
            if(isdigit(s[i])) 
            {
                token+=s[i];
                error_token+=s[i];
            }
            else 
            {
                //cout<<"ERROR type 2: ";
                std::cout<<"ERROR: near \""<<error_token<<"\""<<endl;
                token="";
                return token;
            }
        }
    }
    else 
    {
        //cout<<"ERROR type 3: ";
        std::cout<<"ERROR: near \""<<error_token<<"\""<<endl;
        token="";
        return token;
    }
    return token;
}
void Xu_Ly_Data(string s, vector<string> &v){
    // hàm này xử lý kiểu dữ liệu s dạng "(---,---,---)"
    // đã qua kiểm tra có phát hiện s[0]=='('
    // hàm này chưa xử lí trường hợp '\'
    // vector<string> tmp;
    
    int number_of_element=0;
    int so_ngoac=0;
    string token="";
    for(int i=1; i<s.length()-1; i++) // xử lý 2 dấu ngoặc đơn đi
    {
        
        if(s[i]=='"') so_ngoac++;
        if(so_ngoac%2==0 && (s[i]==',' || s[i + 1] == ')'))
        {
            if(s[i+1]==')') token+=s[i];
            /*
            v.push_back(token);
            so_ngoac=0;
            token="";
            */
            //hàm xử lý tính đúng sai của token nhưng lưu ý khi token có độ dài >0 mà thôi
            ///*
            if(token.length()>0)
            {
                token=xu_ly_token(token);
                if(token.length()==0)
                {
                    // xóa sạch element trong lệnh insert
                    for(int i=0; i<number_of_element; i++)
                    {
                        v.pop_back();
                    }
                    return;
                }
                else if (token.length()>0)
                {
                    //cout<<"check: ["<<token<<"]"<<endl;
                    v.push_back(token);
                    number_of_element++;
                }
            }
            else v.push_back(token);
            so_ngoac=0;
            token="";
            //*/
        }
        else if (s[i+1] == ')')
        {
            token+=s[i];
            ///*
            token=xu_ly_token(token);
            if(token.length()>0)
            {
                if(token.length()==0)
                {
                    // xóa sạch element trong lệnh insert
                    for(int i=0; i<number_of_element; i++)
                    {
                        v.pop_back();
                    }
                    return;
                }
                else if (token.length()>0)
                {
                    v.push_back(token);
                    number_of_element++;
                }
            }
            else v.push_back(token);
            //*/
            /*
            v.push_back(token);
            so_ngoac=0;
            token="";
            */
        }
        else 
        {
            token+=s[i];
        }
    }
    /*
    std::cout<<"number element in vector v: "<<v.size()<<endl;
    std::cout<<"result: ";
    for(auto x: v)
    {
        std::cout<<"["<<x<<"]";
    }
    std::cout<<endl;
    */
}
int main()
{
    vector<string> v;
    ifstream INPUT;
    //string command="insert into filename.txt values (1,2,\"tung\",,45)";
    string command;
    getline(cin,command);
    stringstream ss(command);
    string token;
    ss>>token;
    token=toLowerCase(token);
    if(token=="insert")
    {
        cout<<"insert signal"<<endl;
        ss>>token;
        token=toLowerCase(token);
        if(token=="into")
        {
            cout<<"into signal"<<endl;
            ss>>token;
            INPUT.open(token);
            if(INPUT.is_open()==true)
            {
                ss>>token;
                cout<<"open successful signal"<<endl;
                token=toLowerCase(token);
                if(token=="values")
                {
                    cout<<"values signal"<<endl;
                    getline(ss,token);
                    cout<<"["<<token<<"]"<<endl;
                    token=xoaKhoangTrangDauCuoi(token);
                    cout<<"["<<token<<"]"<<endl;
                    Xu_Ly_Data(token,v);
                    for(auto x:v)
                    {
                        cout<<"["<<x<<"]  ";
                    }
                }
                else 
                {
                    cout<<"ERROR: near \""<<token<<"\" syntax error";
                    return 0;
                }
            }
            else
            {
                cout<<"There are no file name: "<<token<<endl;
                return 0;
            }
        }
        else 
        {
            cout<<"ERROR: near \""<<token<<"\" syntax error";
            return 0;
        }

    }
    else if(token=="select")
    {
        cout<<"select signal"<<endl;
        string tmp;
        vector<string> column;
        getline(ss,tmp);
        tmp=xoaKhoangTrangDauCuoi(tmp);
        cout<<"["<<tmp<<"]"<<endl;
        if(tmp[0]=='(')// có ngoặc trong column 
        {
            cout<<"SIGNAL"<<endl;
            stack<char> s; // chứa đóng mở ngoặc
            string sub_tmp="";
            int i=0;
            s.push(tmp[0]);
            sub_tmp+=tmp[0];
            cout<<"parser stack size: "<<s.size()<<endl;
            while(s.size()>0){
                if(i<tmp.length()){
                    i++;
                    if(i>=tmp.length()) break;
                    sub_tmp+=tmp[i];
                    if(s.top()=='\'' && tmp[i]=='\''){
                        s.pop();
                    }
                    else if(s.top()=='"' && tmp[i]=='"'){
                        s.pop();
                    }
                    else if(s.top()=='(' && tmp[i]==')'){
                        s.pop();
                    }
                }
                else{
                    if(s.size()>0) cout<<"ERROR: near \""<<tmp<<"\" syntax error"<<endl;
                    return 0;
                    break;
                }
                cout<<"IN-parser stack size: "<<s.size()<<endl;
                cout<<"IN-sub_tmp: "<<sub_tmp<<endl;
                cout<<"tmp[i]: "<<tmp[i]<<endl;
                cout<<"---------------------------------------"<<endl;
            }
            cout<<"sub_tmp  : ["<<sub_tmp<<"]"<<endl;
            cout<<"after tmp: ["<<tmp<<"]"<<endl;
            cout<<"i: "<<i<<endl;
            cout<<"tmp[i]: ["<<tmp[i]<<"]"<<endl;
            cout<<"3333["<<sub_tmp<<"]"<<endl;// expected result:= (.....)
            // after this index of tmp is contain ')'
            
        }
        else if (tmp[0] =='*') 
        {
            //TODO
        }
        else 
        {
            cout<<"ERROR: near \""<<tmp<<"\" syntax error"<<endl;
            return 0;
        }
    }
    else 
    {
        cout<<"ERROR: near \""<<token<<"\" syntax error";
        return 0;
    }

           
           
           
 
    INPUT.close();
    return 0;
}


