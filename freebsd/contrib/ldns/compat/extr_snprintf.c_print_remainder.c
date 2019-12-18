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

/* Variables and functions */
 int print_dec_ll (char*,int,unsigned long long) ; 

__attribute__((used)) static int
print_remainder(char* buf, int max, double r, int prec)
{
	unsigned long long cap = 1;
	unsigned long long value;
	int len, i;
	if(prec > 19) prec = 19; /* max we can do */
	if(max < prec) return 0;
	for(i=0; i<prec; i++) {
		cap *= 10;
	}
	r *= (double)cap;
	value = (unsigned long long)r;
	/* see if we need to round up */
	if(((unsigned long long)((r - (double)value)*10.0)) >= 5) {
		value++;
		/* that might carry to numbers before the comma, if so,
		 * just ignore that rounding. failure because 64bitprintout */
		if(value >= cap)
			value = cap-1;
	}
	len = print_dec_ll(buf, max, value);
	while(len < prec) { /* pad with zeroes, e.g. if 0.0012 */
		buf[len++] = '0';
	}
	if(len < max)
		buf[len++] = '.';
	return len;
}