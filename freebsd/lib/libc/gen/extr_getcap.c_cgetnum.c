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
 char* cgetcap (char*,char const*,char) ; 

int
cgetnum(char *buf, const char *cap, long *num)
{
	long n;
	int base, digit;
	char *bp;

	/*
	 * Find numeric capability cap
	 */
	bp = cgetcap(buf, cap, '#');
	if (bp == NULL)
		return (-1);

	/*
	 * Look at value and determine numeric base:
	 *	0x... or 0X...	hexadecimal,
	 * else	0...		octal,
	 * else			decimal.
	 */
	if (*bp == '0') {
		bp++;
		if (*bp == 'x' || *bp == 'X') {
			bp++;
			base = 16;
		} else
			base = 8;
	} else
		base = 10;

	/*
	 * Conversion loop ...
	 */
	n = 0;
	for (;;) {
		if ('0' <= *bp && *bp <= '9')
			digit = *bp - '0';
		else if ('a' <= *bp && *bp <= 'f')
			digit = 10 + *bp - 'a';
		else if ('A' <= *bp && *bp <= 'F')
			digit = 10 + *bp - 'A';
		else
			break;

		if (digit >= base)
			break;

		n = n * base + digit;
		bp++;
	}

	/*
	 * Return value and success.
	 */
	*num = n;
	return (0);
}