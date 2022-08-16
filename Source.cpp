#include <iostream>
using namespace std;

int test;
int spining_odds[5]={0};
int bet_coin[5]={0};
int money;

int betmoney(int vec[], int parts){
	int i = 0;
		for (int n = 0; n < parts; n++) {
			i += vec[n];
		}
	return i;
}

bool find_positive_value(int vec[5]) {
	for (int a = 0; a < 5; a++) {
		if (vec[a] < 0) {
			return false;
		}
	}
	return true;
}

double expectedvalue(int vec[5]) {
	return vec[4] * 0.04 + vec[3] * 0.08 + vec[2] * 0.16 + vec[1] * 0.24 + vec[0] * 0.48;
}



//mainfunction
int main() {
	/*Set the betting environment*/
	cout << "Please type your spining odds (part 1:48%;part 2:24%;part 3:16%;part 4:8%;part 5:4%):\n";
	for (int n = 0; n < 5; n++) {
		cin >> spining_odds[n];
	}

	/*bet the coins in each parts*/
	cout << "User bet number in each odds: \n";
	for (int n = 0; n < 5; n++) {
		cin >> bet_coin[n];
	}

	/*show the result for all situations*/
	for (int n = 0; n < 5; n++) {
		int losemoney = 0;

		losemoney = betmoney(bet_coin,5) - bet_coin[n];
		cout << "Spining " << n+1 << " part result:" << spining_odds[n] * bet_coin[n] - losemoney << endl;
		
	}


	/*show the best strategy*/
	cout << "How many money do you have?: ";
	cin >> money;
	int part[5]={0};
	int result[5]={0};
	double exp = 0.0;
	double answer = -500000.0;
	int anspart[5]={0};
	int ansresult[5]={0};
	/*create all money situation*/
	for (int n = money; n >= 0; n--) {
		part[0] = n;
		for (int x = money - n; x >= 0 ; x--) {
			part[1] = x;
			for (int y = money - n - x; y >= 0 ; y--) {
				part[2] = y;
				for (int z = money - n - x - y; z >= 0 ; z--) {
					part[3] = z;
					part[4] = money-n-x-y-z;

					/*caculating all possible situation result*/
					for (int g = 0; g < 5; g++) {
						int losemoney = 0;

						losemoney = betmoney(part, 5) - part[g];
						result[g] = spining_odds[g] * part[g] - losemoney;
					}
					exp = expectedvalue(result);
					/*check the maximum expected value*/
					if (exp-answer>=0.00000001) {
						answer = exp;
						for (int a = 0; a < 5; a++) {
							anspart[a] = part[a];
							ansresult[a] = result[a];
						}//renew answer
					}
					exp = 0.0;
				}
			}
		}
	}

	/*Show the answer to the player to decide*/
	cout << "The optimal betting strategy is:\n";
	cout << "part 1: " << anspart[0] << " " << "part 2: " << anspart[1] << " " << "part 3: " << anspart[2] << " " << "part 4: " << anspart[3] << " " << "part 5: " << anspart[4] << endl;
	for (int h = 0; h < 5; h++) {
		cout << "If spin to part " << h+1 << " , the result will be: " << ansresult[h]<<endl;
	}
	cout << endl << "Expected value of the game: " << answer << endl;

	return 0;
}

