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
 int PRINT_DEC_BUFSZ ; 
 int print_hex_ll (char*,int,unsigned long long) ; 
 int /*<<< orphan*/  print_num (char**,size_t*,int*,int,int,int,int,int,int,int,int,int,char*,int) ; 

__attribute__((used)) static void
print_num_llp(char** at, size_t* left, int* ret, void* value,
	int minw, int precision, int prgiven, int zeropad, int minus,
	int plus, int space)
{
	char buf[PRINT_DEC_BUFSZ];
	int negative = 0;
	int zero = (value == 0);
#if defined(SIZE_MAX) && defined(UINT32_MAX) && (UINT32_MAX == SIZE_MAX || INT32_MAX == SIZE_MAX)
	/* avoid warning about upcast on 32bit systems */
	unsigned long long llvalue = (unsigned long)value;
#else
	unsigned long long llvalue = (unsigned long long)value;
#endif
	int len = print_hex_ll(buf, (int)sizeof(buf), llvalue);
	if(zero) {
		buf[0]=')';
		buf[1]='l';
		buf[2]='i';
		buf[3]='n';
		buf[4]='(';
		len = 5;
	} else {
		/* put '0x' in front of the (reversed) buffer result */
		if(len < PRINT_DEC_BUFSZ)
			buf[len++] = 'x';
		if(len < PRINT_DEC_BUFSZ)
			buf[len++] = '0';
	}
	print_num(at, left, ret, minw, precision, prgiven, zeropad, minus,
		plus, space, zero, negative, buf, len);
}