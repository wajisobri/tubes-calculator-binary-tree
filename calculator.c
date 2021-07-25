#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include "binarytree.h"

#define UNDEFINE -9999
#define PI 3.14159265

char* calculatorMenu() {
	int pilihan;
	static char math_expression[1001] = "";
	int char_counter = 0;

	do {
		printf("===============================\n");
		printf("%s\n", math_expression);
		printf("===============================\n");

		printf("\n");

		printf("(0) 0     (10) (       (20) log\n");
		printf("(1) 1     (11) )       (21) ln\n");
		printf("(2) 2     (12) +       (22) =\n");
		printf("(3) 3     (13) -       (23) <-\n");
		printf("(4) 4     (14) *       (24) CE\n");
		printf("(5) 5     (15) /        \n");
		printf("(6) 6     (16) ^        \n");
		printf("(7) 7     (17) sin      \n");
		printf("(8) 8     (18) cos      \n");
		printf("(9) 9     (19) tan      \n");

		printf("INPUT: ");
		scanf("%d", &pilihan);

		if ((pilihan < 0) && (pilihan >24)) {
			// user mamasukkan opsi yang tidak sesuai
			printf("Pilih opsi yang benar!");
		} else if (pilihan == 23) {
			// user memilih opsi <- (23) hapus 1 char
			if (char_counter == 0) {
				continue;
			}
			char_counter--;
			math_expression[char_counter] = '\0';
		} else if (pilihan == 24) {
			// user memilih opsi CE (24) hapus semua
			for (int i=char_counter-1; i >= 0; i--) {
				math_expression[i] = '\0';
			}
			char_counter = 0;
		} else {
			if (pilihan < 10) {
				math_expression[char_counter] = pilihan + '0';
			} else {
				switch (pilihan) {
					case 10:
						math_expression[char_counter] = '(';
						break;

					case 11:
						math_expression[char_counter] = ')';
						break;
	
					case 12:
						math_expression[char_counter] = '+';
						break;
					
					case 13:
						math_expression[char_counter] = '-';
						break;

					case 14:
						math_expression[char_counter] = '*';
						break;

					case 15:
						math_expression[char_counter] = '/';
						break;

					case 16:
						math_expression[char_counter] = '^';
						break;

					case 17:
						math_expression[char_counter] = 's';
						break;

					case 18:
						math_expression[char_counter] = 'c';
						break;
							
					case 19:
						math_expression[char_counter] = 't';
						break;

					case 20:
						math_expression[char_counter] = 'l';
						break;

					case 21:
						math_expression[char_counter] = 'n';
						break;

					default:
						break;
				}
			}
			char_counter++;
		}
	} while (pilihan != 22);

	return (char*) math_expression;
}

int getDegree(char operator) {
	switch(operator){
		case '+' : return 1; break;
		case '-' : return 1; break;
		case '*' : return 2; break;
		case '/' : return 2; break;
		case '^' : return 3; break;
		case 'v' : return 3; break;
		case 's' : return 4; break;
		case 'c' : return 4; break;
		case 't' : return 4; break;
		case 'l' : return 4; break;
		case 'n' : return 4; break;
		case '.' : return 5; break;
		default : return 99; break;
	}
}

int getCharType(char value) {
	switch(value){
		case '0' : return 0; break;
		case '1' : return 1; break;
		case '2' : return 2; break;
		case '3' : return 3; break;
		case '4' : return 4; break;
		case '5' : return 5; break;
		case '6' : return 6; break;
		case '7' : return 7; break;
		case '8' : return 8; break;
		case '9' : return 9; break;
		case '(' : return -2; break;
		default : return -1; break;
	}
}

float evaluateTree(addrNode T, bool *isValid) {
	float calcResult=0;
	if(*isValid){
		float leftCalc=0, rightCalc=0;
		bool isValid2=true;
		
		if((Info(T)).operator == 'b'){
			calcResult = (Info(T)).value;
		} else if((Info(T)).operator == '+') { // Operasi Addition ( + )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);

			calcResult = leftCalc+rightCalc;
		} else if((Info(T)).operator == '-') { // Operasi Substraction ( - )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);
			
			calcResult = leftCalc-rightCalc;
		} else if((Info(T)).operator == '*') { // Operasi Multiplication ( * )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);
			
			calcResult = leftCalc*rightCalc;
		} else if((Info(T)).operator == '/') { // Operasi Division ( / )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc != 0){
				calcResult = leftCalc/rightCalc;
			} else{
				*isValid = false;
			}
		} else if((Info(T)).operator == '^') { // Operasi Exponent ( ^ )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);
			
			if((leftCalc < 0) && ((rightCalc) > (-1)) && (leftCalc < 1)){ // operand tidak boleh negatif
				*isValid = false;
			} else{
				calcResult = pow(leftCalc,rightCalc);
			}
		} else if((Info(T)).operator == 'v') { // Operasi Square Root ( √ )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) { // operand tidak boleh negatif
				*isValid = false;
			} else {
				calcResult = sqrt(rightCalc);
			}
		} else if((Info(T)).operator == 's') { // Operasi Trigonometri ( Sin )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) {
				*isValid = false;
			} else {
				calcResult = sin(rightCalc*PI/180);
			}
		} else if((Info(T)).operator == 'c') { // Operasi Trigonometri ( Cos )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) {
				*isValid = false;
			} else {
				calcResult = cos(rightCalc*PI/180);
			}
		} else if((Info(T)).operator == 't') { // Operasi Trigonometri ( Tan )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) {
				*isValid = false;
			} else {
				calcResult = tan(rightCalc*PI/180);
			}
		} else if((Info(T)).operator == 'l') { // Operasi Logaritma ( Log10 )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) {
				*isValid = false;
			} else {
				calcResult = log10(rightCalc);
			}
		} else if((Info(T)).operator == 'n') { // Operasi Logaritma ( Ln )
			if(Left(T) != Nil) leftCalc = evaluateTree(Left(T),&isValid2);
			if(Right(T) != Nil) rightCalc = evaluateTree(Right(T),&isValid2);
			
			if(rightCalc < 0) {
				*isValid = false;
			} else {
				calcResult = log(rightCalc);
			}
		} else if((Info(T)).operator == '.') { // Operasi Lain ( Decimal )
			leftCalc = evaluateTree(Left(T),&isValid2);
			rightCalc = evaluateTree(Right(T),&isValid2);
			
			while((rightCalc > 1) || (rightCalc < -1)){
				rightCalc /= 10;
			}
			
			calcResult = leftCalc+rightCalc;
		} else {
			calcResult = 0;
		}
	}

	return calcResult;
}

bool validateExpression(char *expression) {
	int leftParentheses=0, rightParentheses=0;
	
	while(*expression != '\0'){
		if(*expression == '(')
			leftParentheses++;
		else if(*expression == ')')
			rightParentheses++;
		
		expression++;
	}
	
	return (leftParentheses == rightParentheses);
}

void convertExpression(char **expression, float *calculateResult, bool *isValid) {
	addrNode T, lastNode, searchPos;
	infotype tempInfo;
	float tempCalcResult;
	int currentDegree;
	bool isLastOperator=false, isDecimal=false;

	*isValid = true;
	
	// inisialisasi Tree
	tempInfo = CreateInfo(0,'b');
	T = Tree(tempInfo);
	lastNode = T;
	currentDegree = 10;
	
	while(**expression != '\0' && **expression != ')' && *isValid) {
		// debug
		// printf("[%c %d] ",**expression, isLastOperator);
		if(getCharType(**expression) == -2){ // merupakan karakter '('
			*expression += 1;
			convertExpression(expression, &tempCalcResult, isValid);
			if(*isValid) {
				tempInfo = CreateInfo(tempCalcResult, 'b');
				if (Info(lastNode).operator == 'b') {
					//ubah node
					Info(lastNode) = tempInfo;
				} else {
					// add daun
					AddLeaf(&lastNode, false, tempInfo);
					lastNode = Right(lastNode);
				}
				isLastOperator = false;
			}
		} else if(getCharType(**expression) == -1){ // merupakan operator
			tempInfo = CreateInfo(UNDEFINE, **expression);
			if(getDegree(**expression) != 4) { // bukan merupakan operator trigonometri ( sin/cos/tan/log/ln )
				if(!isLastOperator){ // sebelumnya bukan operator
					if(getDegree(**expression) == 5){ // bertemu titik ( decimal )
						if(isDecimal){
							*isValid = false;
						} else {
							isDecimal = true;
							if(getDegree(**expression) <= currentDegree){
								ChangeRoot(&T, tempInfo, true);
								lastNode = T;
							} else{
								ChangeRoot(&lastNode, tempInfo, true);
							}
							currentDegree = getDegree(**expression);
							isLastOperator = true;
						}
					} else { // bukan titik ( operator )
						isDecimal = false;
						if(getDegree(**expression) < currentDegree){
							if(getDegree(Info(T).operator) < getDegree(**expression)) {
								searchPos = Parent(lastNode);
								while(getDegree(Info(Parent(searchPos)).operator) > getDegree(**expression)) {
									searchPos = Parent(searchPos);
								}
								ChangeRoot(&searchPos, tempInfo, true);
								lastNode = searchPos;
							} else {
								ChangeRoot(&T, tempInfo, true);
								lastNode = T;
							}
						} else {
							if(getDegree(**expression) == 1) {
								ChangeRoot(&T, tempInfo, true);
								lastNode = T;
							} else {
								ChangeRoot(&lastNode, tempInfo, true);
							}
						}
						currentDegree = getDegree(**expression);
						isLastOperator = true;
					}
				} else{
					*isValid = false;
				}
			} else { // merupakan operator trigonometri ( sin/cos/tan/log/ln )
				if(isLastOperator) { // sebelumnya operator
					isDecimal = false;
					AddLeaf(&lastNode, false, tempInfo);
					lastNode = Right(lastNode);
					currentDegree = getDegree(**expression);
					isLastOperator = true;
				} else { // sebelumnya bukan operator
					if(Info(lastNode).value != 0) { // node pertama
						*isValid = false;
					} else {
						isDecimal = false;
						Info(lastNode) = tempInfo;
						currentDegree = getDegree(**expression);
						isLastOperator = true;
					}
				}
			}
		} else { // merupakan operand
			if (Info(lastNode).operator == 'b') { // node pertama (operand pertama)
				Info(lastNode).value = Info(lastNode).value * 10 + getCharType(**expression);
			} else {
				// add daun
				tempInfo = CreateInfo(getCharType(**expression), 'b');
				AddLeaf(&lastNode, false, tempInfo);
				lastNode = Right(lastNode);
			}
			isLastOperator = false;
		}

		// debug
		// printf(" Last Node %c , %.2f\n",Info(lastNode).operator, Info(lastNode).value);

		// mengabaikan whitespace
		while (**expression == ' ') {
			*expression += 1;
		}

		// lanjut ke karakter selanjutnya
		*expression += 1;
	}

	// PrintTree(T);
	
	if(*isValid){
		*calculateResult = evaluateTree(T, isValid);
		if(!*isValid){
			printf("Calculation Error\n");
		}
	} else{
		printf("Syntax Error\n");
	}
	
	DestroyTree(T);
}