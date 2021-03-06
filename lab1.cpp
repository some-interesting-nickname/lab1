#include <iostream>
#include <stdlib.h>
#include <bitset>
using namespace std;

int div(unsigned int r, int deg_m, unsigned int l2, unsigned int g){

	unsigned int mask = 1;
	for(int i = r; i >= 0; i--){
		if((l2 & (mask << (i + deg_m))) != 0) {
			l2 = (g << i) ^ l2;
		}
	}
	return l2;
}

int main() {
	unsigned int g = 0, k = 0, e = 0, l = 0;
	cout << "Enter g(x)"<< "\n";
	cin  >> g; 
	cout << "Enter k"<< "\n";
	cin  >> k;
	cout << "Enter e"<< "\n";
	cin  >> e;
	cout << "Enter l"<< "\n";
	cin  >> l;

	cout << "m(x): "<< bitset<8>(l).to_string() << "\n";

	int deg_m = k - 1;
	int r = 0;
	unsigned int tmp = g;
	for(int i = 0; i < 10; i++){
		if(tmp & 1 != 0)
			r = i;
		tmp = tmp >> 1;
	}

	tmp = l;
	for(int i = 0; i < 10; i++){
		if(tmp & 1 != 0)
			deg_m = i;
		tmp = tmp >> 1;
	}

	unsigned int l2 = l << r;
	cout << "m(x)*x^r: "<< bitset<8>(l2).to_string() << "\n";

	if(deg_m == k - 1){
		l2 = div(r, deg_m, l2, g);
	} else{
		l2 = div(r + deg_m - k + 1, deg_m - 1, l2, g);
		/*for(int i = r + deg_m - k + 1; i >= 0; i--){
			if((l2 & (mask << (i + deg_m - 1))) != 0) {
				l2 = (g << i) ^ l2;
			}
		}*/
	}
	
	cout << "c(x): "<< bitset<8>(l2).to_string() << "\n";

	unsigned int message = (l << r) | l2;

	cout << "a(x): "<< bitset<8>(message).to_string() << "\n";
	cout << "e(x): "<< bitset<8>(e).to_string() << "\n";


	message = message ^ e;

	cout << "b(x): "<< bitset<8>(message).to_string() << "\n";

	unsigned int message2 = message;
	if(deg_m == k - 1){
		message2 = 	div(r, deg_m, message2, g);
	} else{
		message2 = div(r + deg_m - k + 1, deg_m - 1, message2, g);
		/*for(int i = r + deg_m - k + 1; i >= 0; i--){
			if((message2 & (mask << (i + deg_m - 1))) != 0) {
				message2 = (g << i) ^ message2;
			}		
		}*/
	}
	
	if(message2 == 0) {
		cout << "Ok" << "\n";
		cout << (message >> r) << "\n";
	}
	else 
		cout << "Not Ok" << "\n";
	return 0;
}