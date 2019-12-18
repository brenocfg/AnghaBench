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
typedef  int uintmax_t ;

/* Variables and functions */
 char hex2ascii (int) ; 
 char hex2ascii_upper (int) ; 

__attribute__((used)) static char *
ksprintn(char *nbuf, uintmax_t num, int base, int *lenp, int upper)
{
	char *p, c;

	p = nbuf;
	*p = '\0';
	do {
		c = upper ? hex2ascii_upper(num % base) :
		    hex2ascii(num % base);
		*++p = c;
	} while (num /= base);
	if (lenp)
		*lenp = p - nbuf;
	return (p);
}