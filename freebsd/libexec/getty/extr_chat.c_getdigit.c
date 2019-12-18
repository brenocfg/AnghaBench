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
 char* strchr (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tolower (char) ; 

__attribute__((used)) static int
getdigit(unsigned char **ptr, int base, int max)
{
	int i, val = 0;
	char * q;

	static const char xdigits[] = "0123456789abcdef";

	for (i = 0, q = *ptr; i++ < max; ++q) {
		int sval;
		const char * s = strchr(xdigits, tolower(*q));

		if (s == NULL || (sval = s - xdigits) >= base)
			break;
		val = (val * base) + sval;
	}
	*ptr = q;
	return val;
}