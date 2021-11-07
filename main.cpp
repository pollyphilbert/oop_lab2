#include <iostream>
using namespace std;

#include<string>
#include<algorithm>
using namespace std;



class LongNumberStr {
public:
	string s;
	int length;


	LongNumberStr appendZeroLng(int n) {
		while (n > 0) {
			this.s = "0" + this.s;
			n--;
		}
		return this;
	}

	LongNumberStr multiplyXY(LongNumberStr other) {
		LongNumberStr x;
		LongNumberStr y;
		x = this;
		y = other;
		int product;
		product = ((int)x.s[0] - '0') * ((int)y.s[0] - '0');
		return to_string(product);
	}

	LongNumberStr multiplyLng(LongNumberStr other) {
		LongNumberStr x;
		LongNumberStr y;
		x = this;
		y = other;
		int product;
		LongNumberStr res;
		product = ((int)x.s[0] - '0') * ((int)y.s[0] - '0');
		res.s = to_string(product);
		return res;
	}

	LongNumberStr addXY(LongNumberStr other) {
		LongNumberStr x;
		LongNumberStr y;
		x = this;
		y = other;

		if (x.s.length() > y.slength()) {
			y = appendZeroLng(x.s.length() - y.s.length());
		}
		else {
			x = appendZeroLng(y.s.length() - x.s.length());
		}
		
		int carry = 0, sum;
		string result = "";
		for (int i = x.s.length() - 1; i >= 0; i--) {
			sum = ((int)x.s[i] - '0') + ((int)y.s[i] - '0') + carry;

			if (sum > 9) {
				result = to_string(sum % 10) + result;
				carry = sum / 10;
			}
			else {
				result = to_string(sum) + result;
				carry = 0;
			}
		}
		if (carry != 0) {
			result = to_string(carry) + result;
		}
		return result;
	}

	LongNumberStr subtractXY(LongNumberStr other) {
		LongNumberStr x;
		LongNumberStr y;
		x = this;
		y = other;
		if (x.s.length() > y.s.length()) {
			y = appendZeroLng(x.s.length() - y.s.length());
		}
		else {
			x = appendZeroLng(y.s.length() - x.s.length());
		}

		string result = "";
		
		int borrow = 0, a, b;
		for (int i = x.s.length() - 1; i >= 0; i--) {
			a = (int)x.s[i] - '0';
			b = (int)y.s[i] - '0';
			if (borrow == 1) {
				a = a - 1;
			}
			if (a >= b) {
				result = to_string(a - b) + result;
				borrow = 0;
			}
			else {
				a = a + 10;
				result = to_string(a - b) + result;
				borrow = 1;
			}
		}
		return removeZero(result);
	}

	LongNumberStr removeZero(LongNumberStr str) {
		reverse(str.begin(), str.end());
		for (int i = str.length() - 1; i >= 0; i--) {
			if (str[i] == '0') {
				str.pop_back();
			}
			else {
				break;
			}
		}
		if (str.empty()) {
			return "0";
		}
		else {
			reverse(str.begin(), str.end());
			return str;
		}
	}


	LongNumberStr multiply10( int n) {
		while (n > 0) {
			this.s = this.s + "0";
			n--;
		}
		return str;
	}
};

LongNumberStr karatsuba(LongNumberStr x, LongNumberStr y) {

	LongNumberStr result;

	if (x.length() == 1 && y.length() == 1) {
		result = x.multiplyXY(y);
		return result;
	}

	if (x.s.length() > y.s.length()) {
		y.appendZeroLng(x.s.length() - y.s.length());
	}
	else {
		x.appendZeroLng(y.s.length() - x.s.length());
	}
	if (x.s.length() % 2 != 0) {
		x.s = "0" + x.s;
		y.s = "0" + y.s;
	}

	LongNumberStr x_left, x_right, y_left, y_right, st1, st2, st3, st4, st5, st6, st7, st8, res;
	int n = x.s.length();

	x_left.s = x.s.substr(0, x.s.length() / 2);
	x_right.s = x.s.substr(x.s.length() / 2);
	y_left.s = y.s.substr(0, y.s.length() / 2);
	y_right.s = y.s.substr(y.s.length() / 2);

	st1 = karatsuba(x_left, y_left);
	st2 = karatsuba(x_left.addXY(x_right), y_left.addXY(y_right));
	st3 = karatsuba(x_right, y_right);
	st4 = st2.subtractXY(st1);
	st5 = st4.subtractXY(st3);
	st6 = st5.multiply10(n / 2);
	st7 = st1.multiply10(n);
	st8 = st7.addXY(st6);
	res = st8.addXY(st3);
	return res;
}

int main() {
	LongNumberStr x;
	LongNumberStr y;
	LongNumberStr res;

	//string x, y;
	getline(cin, x.s);
	getline(cin, y.s);
	if (x.s == "0" || y.s == "0") {
		cout << "0" << endl;
	}
	else {
		if (x.s.length() > y.s.length()) {
			y = y.appendZeroLng(x.s.length() - y.s.length());
		}
		else {
			x = x.appendZeroLng(y.s.length() - x.s.length());
		}
		res.s = karatsuba(x.s, y.s);
		cout << removeZero(res.s) << endl;
	}
	return 0;
}


/*
string appendZero(string str, int n) {
	while (n > 0) {
		str = "0" + str;
		n--;
	}
	return str;
}

string multiplyXY(string x, string y) {
	int product;
	product = ((int)x[0] - '0') * ((int)y[0] - '0');
	return to_string(product);
}

string addXY(string x, string y) {
	if (x.length() > y.length()) {
		y = appendZero(y, x.length() - y.length());
	}
	else {
		x = appendZero(x, y.length() - x.length());
	}
	int carry = 0, sum;
	string result = "";
	for (int i = x.length() - 1; i >= 0; i--) {
		sum = ((int)x[i] - '0') + ((int)y[i] - '0') + carry;

		if (sum > 9) {
			result = to_string(sum % 10) + result;
			carry = sum / 10;
		}
		else {
			result = to_string(sum) + result;
			carry = 0;
		}
	}
	if (carry != 0) {
		result = to_string(carry) + result;
	}
	return result;
}

string subtractXY(string x, string y) {
	if (x.length() > y.length()) {
		y = appendZero(y, x.length() - y.length());
	}
	else {
		x = appendZero(x, y.length() - x.length());
	}

	string result = "";
	int borrow = 0, a, b;
	for (int i = x.length() - 1; i >= 0; i--) {
		a = (int)x[i] - '0';
		b = (int)y[i] - '0';
		if (borrow == 1) {
			a = a - 1;
		}
		if (a >= b) {
			result = to_string(a - b) + result;
			borrow = 0;
		}
		else {
			a = a + 10;
			result = to_string(a - b) + result;
			borrow = 1;
		}
	}
	return removeZero(result);
}

string removeZero(string str) {
	reverse(str.begin(), str.end());
	for (int i = str.length() - 1; i >= 0; i--) {
		if (str[i] == '0') {
			str.pop_back();
		}
		else {
			break;
		}
	}
	if (str.empty()) {
		return "0";
	}
	else {
		reverse(str.begin(), str.end());
		return str;
	}
}

string multiply10(string str, int n) {
	while (n > 0) {
		str = str + "0";
		n--;
	}
	return str;
}
*/