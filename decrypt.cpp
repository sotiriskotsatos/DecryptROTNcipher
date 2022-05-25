#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <cmath>
//#include <math.h>
using namespace std;
 

double get_freq(int letter)
{
    double result = 0;
    switch(letter){
        case 1:
        result = log(0.08167);
        break;
        case 2:
        result = log(0.01492);
        break;
        case 3:
        result = log(0.02782);
        break;
        case 4:
        result = log(0.04253);
        break;
        case 5:
        result = log(0.12702);
        break;
        case 6:
        result = log(0.02228);
        break;
        case 7:
        result = log(0.02015);
        break;
        case 8:
        result = log(0.06094);
        break;
        case 9:
        result = log(0.06966);
        break;
        case 10:
        result = log(0.00153);
        break;
        case 11:
        result = log(0.00772);
        break;
        case 12:
        result = log(0.04025);
        break;
        case 13:
        result = log(0.02406);
        break;
        case 14:
        result = log(0.06749);
        break;
        case 15:
        result = log(0.07507);
        break;
        case 16:
        result = log(0.01929);
        break;
        case 17:
        result = log(0.00095);
        break;
        case 18:
        result = log(0.05987);
        break;
        case 19:
        result = log(0.06327);
        break;
        case 20:
        result = log(0.09056);
        break;
        case 21:
        result = log(0.02758);
        break;
        case 22:
        result = log(0.00978);
        break;
        case 23:
        result = log(0.02360);
        break;
        case 24:
        result = log(0.00150);
        break;
        case 25:
        result = log(0.01974);
        break;
        case 26:
        result = log(0.00074);
        break;
    }
    return result;
}



double entropy(double decryptedFreq,double generalFreq)
{
    return decryptedFreq*generalFreq;
}

double computeDecrFreq(string text,int textLength , int step)
{
    double counter =0;
    for (int i =0;i<textLength;i++)
    {
        if (text[i]==64+step || text[i]== 96+step)
        {
            counter++;
        }
    }
    return counter;
}

string decryptedText(string text,int textLength ,int step)
{
    for (int i=0 ; i<textLength;i++)
    {
        if(text[i]>64 && text[i]<91)
        {
            if (text[i]+ step>90)
            {
                int mod = (text[i]+ step)%90;
                text[i]= 64+mod;
            }
            else text[i]+= step;
        }
        else if(text[i]>96 &&text[i]<123)
        {
            if (text[i]+ step>122)
            {
                int mod = (text[i]+ step)%122;
                text[i]= 96+mod;
            }
            else text[i]+= step;
        }
    }
    return text;
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        cout << "Please enter a txt file" << endl;
        return -1;
    }
    string line;
    ifstream inFile(argv[1]) ;
    if (inFile.is_open())
    {
        string fileText;
        while ( getline (inFile,line) )
        {
            fileText+=line+'\n';
        }
        int length = fileText.length();
        double entropies[26];
        for (int ii=0;ii<26;ii++)
        {
            entropies[ii] = 0;
        }
        for (int i =1;i<27;i++)
        {
            string tempText = decryptedText(fileText,length,i);
            for (int j=1;j<27;j++)
            {
                entropies[i-1]+= entropy(computeDecrFreq(tempText,length,j),get_freq(j));
            }
        }
        double max = entropies[0] ;
        int maxIndex =0;
        for (int i =0;i<26;i++)
        {
            if (max<entropies[i]){
                max= entropies[i];
                maxIndex=i;
            }
        }
        cout << decryptedText(fileText,length,maxIndex+1);              
        inFile.close();
    }
    else cout << "Unable to open file "<< argv[1] ;
    return 0;
}
