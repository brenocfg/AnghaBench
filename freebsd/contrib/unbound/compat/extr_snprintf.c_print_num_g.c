#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int PRINT_FLOAT_BUFSZ ; 
 int print_float_g (char*,int,double,int) ; 
 int /*<<< orphan*/  print_num (char**,size_t*,int*,int,int,int /*<<< orphan*/ ,int,int,int,int,int,int,char*,int) ; 

__attribute__((used)) static void
print_num_g(char** at, size_t* left, int* ret, double value,
	int minw, int precision, int prgiven, int zeropad, int minus,
	int plus, int space)
{
	char buf[PRINT_FLOAT_BUFSZ];
	int negative = (value < 0);
	int zero = 0;
	int len;
	if(!prgiven) precision = 6;
	if(precision == 0) precision = 1;
	len = print_float_g(buf, (int)sizeof(buf), negative?-value:value,
		precision);
	print_num(at, left, ret, minw, 1, 0, zeropad, minus,
		plus, space, zero, negative, buf, len);
}