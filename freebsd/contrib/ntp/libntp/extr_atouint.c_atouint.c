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
atouint(
	const char *str,
	u_long *uval
	)
{
	u_long u;
	const char *cp;

	cp = str;
	if ('\0' == *cp)
		return 0;

	u = 0;
	while ('\0' != *cp) {
		if (!isdigit((unsigned char)*cp))
			return 0;
		if (u > 429496729 || (u == 429496729 && *cp >= '6'))
			return 0;		/* overflow */
		/* hand-optimized u *= 10; */
		u = (u << 3) + (u << 1);
		u += *cp++ - '0';		/* not '\0' */
	}

	*uval = u;
	return 1;
}