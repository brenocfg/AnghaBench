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
 char get_negsign (int,int,int) ; 
 int /*<<< orphan*/  print_pad (char**,size_t*,int*,char,int) ; 
 int /*<<< orphan*/  spool_str_rev (char**,size_t*,int*,char*,int) ; 

__attribute__((used)) static void
print_num(char** at, size_t* left, int* ret, int minw, int precision,
	int prgiven, int zeropad, int minus, int plus, int space,
	int zero, int negative, char* buf, int len)
{
	int w = len; /* excludes minus sign */
	char s = get_negsign(negative, plus, space);
	if(minus) {
		/* left adjust the number into the field, space padding */
		/* calc numw = [sign][zeroes][number] */
		int numw = w;
		if(precision == 0 && zero) numw = 0;
		if(numw < precision) numw = precision;
		if(s) numw++;

		/* sign */
		if(s) print_pad(at, left, ret, s, 1);

		/* number */
		if(precision == 0 && zero) {
			/* "" for the number */
		} else {
			if(w < precision)
				print_pad(at, left, ret, '0', precision - w);
			spool_str_rev(at, left, ret, buf, len);
		}
		/* spaces */
		if(numw < minw)
			print_pad(at, left, ret, ' ', minw - numw);
	} else {
		/* pad on the left of the number */
		/* calculate numw has width of [sign][zeroes][number] */
		int numw = w;
		if(precision == 0 && zero) numw = 0;
		if(numw < precision) numw = precision;
		if(!prgiven && zeropad && numw < minw) numw = minw;
		else if(s) numw++;

		/* pad with spaces */
		if(numw < minw)
			print_pad(at, left, ret, ' ', minw - numw);
		/* print sign (and one less zeropad if so) */
		if(s) {
			print_pad(at, left, ret, s, 1);
			numw--;
		}
		/* pad with zeroes */
		if(w < numw)
			print_pad(at, left, ret, '0', numw - w);
		if(precision == 0 && zero)
			return;
		/* print the characters for the value */
		spool_str_rev(at, left, ret, buf, len);
	}
}