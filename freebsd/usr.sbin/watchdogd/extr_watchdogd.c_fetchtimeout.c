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
 int /*<<< orphan*/  EX_USAGE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,...) ; 
 long strtol (char const*,char**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long
fetchtimeout(int opt, const char *longopt, const char *myoptarg, int zero_ok)
{
	const char *errstr;
	char *p;
	long rv;

	errstr = NULL;
	p = NULL;
	errno = 0;
	rv = strtol(myoptarg, &p, 0);
	if ((p != NULL && *p != '\0') || errno != 0)
		errstr = "is not a number";
	if (rv < 0 || (!zero_ok && rv == 0))
		errstr = "must be greater than zero";
	if (errstr) {
		if (longopt) 
			errx(EX_USAGE, "--%s argument %s", longopt, errstr);
		else 
			errx(EX_USAGE, "-%c argument %s", opt, errstr);
	}
	return (rv);
}