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
typedef  int /*<<< orphan*/  str ;

/* Variables and functions */
 scalar_t__ LONG_MAX ; 
 long LONG_MIN ; 
 char* stringn (char*,int) ; 

char *stringd(long n) {
	char str[25], *s = str + sizeof (str);
	unsigned long m;

	if (n == LONG_MIN)
		m = (unsigned long)LONG_MAX + 1;
	else if (n < 0)
		m = -n;
	else
		m = n;
	do
		*--s = m%10 + '0';
	while ((m /= 10) != 0);
	if (n < 0)
		*--s = '-';
	return stringn(s, str + sizeof (str) - s);
}