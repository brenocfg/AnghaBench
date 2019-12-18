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
typedef  int u_long ;

/* Variables and functions */
 int /*<<< orphan*/  isdigit (unsigned char) ; 

int
octtoint(
	const char *str,
	u_long *ival
	)
{
	register u_long u;
	register const char *cp;

	cp = str;

	if (*cp == '\0')
	    return 0;

	u = 0;
	while (*cp != '\0') {
		if (!isdigit((unsigned char)*cp) || *cp == '8' || *cp == '9')
		    return 0;
		if (u >= 0x20000000)
		    return 0;	/* overflow */
		u <<= 3;
		u += *cp++ - '0';	/* ascii dependent */
	}
	*ival = u;
	return 1;
}