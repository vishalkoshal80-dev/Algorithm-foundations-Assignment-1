
#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

// ----------- TASK 1 -----------
void constantTime(int n) {
    int x = n * 2;
}

void linearTime(int n) {
    int sum = 0;
    for(int i=0;i<n;i++) sum += i;
}

void quadraticTime(int n) {
    int sum = 0;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            sum += i + j;
}

void logarithmicTime(int n) {
    int count = 0;
    while(n > 1){
        n /= 2;
        count++;
    }
}

double measure(void (*func)(int), int n){
    auto start = high_resolution_clock::now();
    func(n);
    auto stop = high_resolution_clock::now();
    return duration<double>(stop-start).count();
}

// ----------- TASK 2 -----------
bool linearSearch(vector<int>& arr, int target){
    for(int x: arr)
        if(x == target) return true;
    return false;
}

bool binarySearch(vector<int>& arr, int target){
    int l=0, r=arr.size()-1;
    while(l<=r){
        int mid=(l+r)/2;
        if(arr[mid]==target) return true;
        else if(arr[mid]<target) l=mid+1;
        else r=mid-1;
    }
    return false;
}

// ----------- TASK 3 -----------
int callCount = 0;

int fibRecursive(int n){
    callCount++;
    if(n<=1) return n;
    return fibRecursive(n-1)+fibRecursive(n-2);
}

int fibDP(int n){
    vector<int> dp(n+1);
    dp[0]=0; dp[1]=1;
    for(int i=2;i<=n;i++)
        dp[i]=dp[i-1]+dp[i-2];
    return dp[n];
}

// ----------- TASK 4 -----------
int callCounter = 0;

int recurrence1(int n){
    callCounter++;
    if(n<=1) return 1;
    return recurrence1(n/2) + n;
}

int recurrence2(int n){
    callCounter++;
    if(n<=1) return 1;
    return recurrence2(n/2) + recurrence2(n/2) + n;
}

// ----------- MAIN -----------
int main(){

    cout << "TASK 1: Growth Observation\n";
    vector<int> sizes = {10,100,500,1000};

    for(int n: sizes){
        cout << "n="<<n<<" ";
        cout << "O(1): "<<measure(constantTime,n)<<" ";
        cout << "O(n): "<<measure(linearTime,n)<<" ";
        cout << "O(n^2): "<<measure(quadraticTime,n)<<" ";
        cout << "O(log n): "<<measure(logarithmicTime,n)<<"\n";
    }

    cout << "\nTASK 2: Search Comparison\n";
    for(int n: {100,500,1000}){
        vector<int> arr(n);
        for(int i=0;i<n;i++) arr[i]=i+1;

        int target = arr.back();

        auto start = high_resolution_clock::now();
        linearSearch(arr,target);
        auto stop = high_resolution_clock::now();
        cout << "Linear Search time: "<<duration<double>(stop-start).count()<<"\n";

        start = high_resolution_clock::now();
        binarySearch(arr,target);
        stop = high_resolution_clock::now();
        cout << "Binary Search time: "<<duration<double>(stop-start).count()<<"\n";
    }

    cout << "\nTASK 3: Fibonacci Comparison\n";
    for(int n: {5,10,20}){
        callCount = 0;
        fibRecursive(n);
        cout << "n="<<n<<" Recursive Calls="<<callCount<<"\n";

        fibDP(n);
    }

    cout << "\nTASK 4: Recurrences\n";
    for(int n: {10,50,100}){
        callCounter = 0;
        recurrence1(n);
        cout << "T(n)=T(n/2)+n calls: "<<callCounter<<"\n";

        callCounter = 0;
        recurrence2(n);
        cout << "T(n)=2T(n/2)+n calls: "<<callCounter<<"\n";
    }

    return 0;
}
