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
 int /*<<< orphan*/  isdigit (unsigned char) ; 

int
atoint(
	const char *str,
	long *ival
	)
{
	register long u;
	register const char *cp;
	register int isneg;
	register int oflow_digit;

	cp = str;

	if (*cp == '-') {
		cp++;
		isneg = 1;
		oflow_digit = '8';
	} else {
		isneg = 0;
		oflow_digit = '7';
	}

	if (*cp == '\0')
	    return 0;

	u = 0;
	while (*cp != '\0') {
		if (!isdigit((unsigned char)*cp))
		    return 0;
		if (u > 214748364 || (u == 214748364 && *cp > oflow_digit))
		    return 0;	/* overflow */
		u = (u << 3) + (u << 1);
		u += *cp++ - '0';	/* ascii dependent */
	}

	if (isneg)
	    *ival = -u;
	else 
	    *ival = u;
	return 1;
}