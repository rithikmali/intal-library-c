#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"intal.h"

static char** helperForGreater_Lesser(char* intal1,char* intal2)
{
    int cmp = intal_compare(intal1,intal2);
    char* result = (char*)malloc(sizeof(char)*100);
    char* greater = intal2;
    char* lesser = intal1;

    if (cmp==1)
    {
        greater = intal1;
        lesser = intal2;
    }

    char** return_value = (char**)malloc(sizeof(char*)*3);
    return_value[0]=lesser;
    return_value[1]=greater;
    return_value[2]=result;

    return return_value;
    
}

char* intal_add(char* intal1, char* intal2)
{
    char** arr = helperForGreater_Lesser(intal1,intal2);
    char* lesser = arr[0];
    char* greater = arr[1];
    char* result = arr[2];
    int lenL = strlen(lesser);
    int lenG = strlen(greater);

    int carry=0;
    int sum=0;
    int k=lenG-1;
    int i=lenL-1;
    int j =lenG-1;
    for(i; i>=0; i--)
    {
        int n1 = lesser[i]  - '0';
        int n2 = greater[j]  - '0';
        sum=n1 + n2 + carry;
        //printf("PSum: %d",sum);
        carry = sum/10;
        sum = sum % 10;
        //printf(" sum:%d , carry:%d\n",sum,carry);
        result[k] = sum + '0';
        k--;j--;
    }

    if(j>=0)
    {
        for(j;j>=0;j--)
        {
            int n2 = greater[j]  - '0';
            result[k] = (n2 + carry) + '0';
            carry=0;
            k--;
        }
    }

    result[lenG] = '\0';
    
    if(carry!=0)
    {
        for (i = lenG; i > 0; i--)
        {
            result[i] = result[i-1];
        }
        result[0] = carry + '0';
        result[lenG+1] = '\0';
    }

    return result;
}

int intal_compare(char* intal1, char* intal2)
{
    int len1 = strlen(intal1);
    int len2 = strlen(intal2);

    if (len1>len2)
    {
        return 1;
    }
    else if (len2>len1)
    {
        return -1;
    }
    else
    {
        for (int i = 0; i < len1; i++)
        {
            int n1 = intal1[i]  - '0';
            int n2 = intal2[i]  - '0';
            if (n1 > n2)
                return 1;
            else if(n2 > n1)
                return -1;
        }
        return 0;
    }
}

char* intal_diff(char* intal1, char* intal2)
{
    int lenL = strlen(intal1);
    int lenG = strlen(intal2);
    int cmp = intal_compare(intal1,intal2);
    char* result = (char*)malloc(sizeof(char)*100);
    
    char* greater = intal2;
    char* lesser = intal1;

    if (cmp==1)
    {
        int temp =lenL;
        lenL=lenG;
        lenG=temp;
        greater = intal1;
        lesser = intal2;
    }
    else if(cmp==0)
    {
        result="0";
        return result;
    }
    if (lesser=="0")
    {
        strcpy(result,greater);
        return result;
    }
    
    int carry=0;
    int diff=0;
    int k=lenG-1;
    int i=lenL-1;
    int j =lenG-1;
    for(i; i>=0; i--)
    {
        int n1 = lesser[i]  - '0';
        int n2 = greater[j]  - '0';
        if(n2>=(n1+carry))
        {
            diff=n2-n1-carry;
            carry=0;
        }
        else
        {
            diff=n2+10-n1-carry;
            carry=1;
        }
        
        //printf("Pdiff: %d",diff);
        // printf(" diff:%d , carry:%d\n",diff,carry);
        result[k] = diff + '0';
       
        k--;j--;
    }

    if(j>=0)
    {
        for(j;j>=0;j--)
        {
            int n2 = greater[j]  - '0';
            result[k] = (n2 - carry) + '0';
            carry=0;
            k--;
        }
    }


    result[lenG] = '\0';
    int count=0;
    i=0;
    while(i<lenG)
    {
        if(result[i]=='0')
        {
            count++;
        }
        else
        {
            break;
        }
        i++;
    }
    for(i=count-1;i<lenG;i++)
    {
        result[i-count] = result[i];
    }

    result[i-count] = '\0';
    return result;
}

char* intal_multiply(char* intal1, char* intal2)
{
    char** arr = helperForGreater_Lesser(intal1,intal2);
    char* lesser = arr[0];
    char* greater = arr[1];
    char* result = arr[2];
    int lenL = strlen(lesser);
    int lenG = strlen(greater);
    char* IntermediateResult = (char*)malloc(sizeof(char)*1000);


    result="0";
    int carry=0;
    int product=0;
    int k=lenG-1;
    int ik=lenG;
    int i=lenL-1;
    int j =lenG-1;

    for(i; i>=0; i--)
    {
        int n1 = lesser[i]  - '0';
        ik=lenG;
        for (j = lenG-1; j >= 0; j--)
        {
            int n2 = greater[j]  - '0';
            product=n1*n2 + carry;
            carry = product/10;
            product = product % 10;
            IntermediateResult[--ik]=product+'0';
           // printf("j: %d, IR[%d] = %c\n",j,ik,IntermediateResult[ik]);
        }

        if (carry!=0)
        {
            for (ik = lenG; ik > 0; ik--)
            {
                IntermediateResult[ik] = IntermediateResult[ik-1];
            }
            IntermediateResult[0] = carry + '0';
            IntermediateResult[lenG+1] = '\0';
        }
        for (ik = 0; ik < (lenL-i-1); ik++)
        {
            IntermediateResult[lenG+ik]='0';
        }
        IntermediateResult[lenG-i+lenL]='\0';
        
        //printf("InResult: %s\n",IntermediateResult);
        result=intal_add(result,IntermediateResult);
        k--;j--;
    }
    free(IntermediateResult);
    return result;
}

static char* longDivision(char* number, int divisor) 
{ 
    // As result can be very large store it in string 
    char* ans = (char*)malloc(sizeof(char)*100); 
    
    // Find prefix of number that is larger 
    // than divisor. 
    int idx = 0; 
    int temp = number[idx] - '0'; 
    while (temp < divisor) 
       temp = temp * 10 + (number[++idx] - '0'); 
      
    // Repeatedly divide divisor with temp. After  
    // every division, update temp to include one  
    // more digit. 
    while (strlen(number)> idx)
    { 
        // Store result in answer i.e. temp / divisor 
        ans += (temp / divisor) + '0'; 
          
        // Take next digit of number 
        temp = (temp % divisor) * 10 + number[++idx] - '0'; 
    } 
      
    // If divisor is greater than number 
    if (strlen(ans) == 0) 
        return "0"; 
      
    // else return ans 
    return ans; 
} 

char* intal_mod(char* intal1, char* intal2)
{
    char** arr = helperForGreater_Lesser(intal1,intal2);
    char* lesser = arr[0];
    char* greater = arr[1];
    char* result = arr[2];
    int lenL = strlen(lesser);
    int lenG = strlen(greater);
}

int intal_max(char **arr, int n)
{
    int max=0;
    int cmp;
    for (int i = 0; i < n; ++i)
    {
        cmp=intal_compare(arr[i],arr[max]);
        if (cmp==1)
        {
            max=i;
        }
    }
    return max;
}

int intal_min(char **arr, int n)
{
    int min=0;
    int cmp;
    for (int i = 0; i < n; i++)
    {
        cmp=intal_compare(arr[i],arr[min]);
        if (cmp==-1)
        {
            min=i;
        }
    }
    return min;
}

int intal_search(char **arr, int n, char* key)
{
    int key_index = -1;
    int cmp;
    for (int i = 0; i < n; i++)
    {
        cmp = intal_compare(arr[i],key);
        if(!cmp)
        {
            key_index = i;
            return key_index;
        }
    }
    return key_index;
}

int intal_binsearch(char **arr, int n, char* key)
{
    int r = n-1;
    int l = 0;
    int cmp;
    while (l <= r) { 
        int m = l + (r - l) / 2; 
        cmp = intal_compare(arr[m],key);
        if (cmp==0) 
            return m; 
  
        if (cmp==-1) 
            l = m + 1; 
  
        else
            r = m - 1; 
    } 
  
    return -1; 
}

static void mergeHelp(char **arr, int l, int m, int r)
{
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 =  r - m; 

    char* L[n1];
    char* R[n2];
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1+ j]; 

    i = 0;
    j = 0; 
    k = l;

    while (i < n1 && j < n2) 
    { 
        int cmp = intal_compare(L[i],R[j]);
        if (cmp==0 || cmp==-1) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    }

    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    }

    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    }
}

static void mergeSortHelp(char **arr, int l, int r)
{
    if(l<r)
    {
        int m = (l + (r-1))/ 2;
        mergeSortHelp(arr,l,m);
        mergeSortHelp(arr,m+1,r);

        mergeHelp(arr,l,m,r);
    }
}

void intal_sort(char **arr, int n)
{
    mergeSortHelp(arr,0,n-1);
}

char* intal_fibonacci(unsigned int n)
{
    int i; 
    char* a = (char*)malloc(sizeof(char)*100);
    char* b = (char*)malloc(sizeof(char)*100);
    char* c = (char*)malloc(sizeof(char)*100);
    a[0]='0'; a[1]='\0';
    b[0]='1'; b[1]='\0';

    if( n == 0) 
        return a;
    for (i = 2; i <= n; i++) 
    { 
        c = intal_add(a,b); 
        strcpy(a,b);
        strcpy(b,c);
    } 
    free(a);
    free(c);
    return b;
}

//cmt