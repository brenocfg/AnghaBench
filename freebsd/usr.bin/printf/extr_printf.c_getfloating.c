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
 scalar_t__ ERANGE ; 
 long double asciicode () ; 
 scalar_t__ errno ; 
 char** gargv ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 long double strtod (char*,char**) ; 
 long double strtold (char*,char**) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static int
getfloating(long double *dp, int mod_ldbl)
{
	char *ep;
	int rval;

	if (!*gargv) {
		*dp = 0.0;
		return (0);
	}
	if (**gargv == '"' || **gargv == '\'') {
		*dp = asciicode();
		return (0);
	}
	rval = 0;
	errno = 0;
	if (mod_ldbl)
		*dp = strtold(*gargv, &ep);
	else
		*dp = strtod(*gargv, &ep);
	if (ep == *gargv) {
		warnx("%s: expected numeric value", *gargv);
		rval = 1;
	} else if (*ep != '\0') {
		warnx("%s: not completely converted", *gargv);
		rval = 1;
	}
	if (errno == ERANGE) {
		warnx("%s: %s", *gargv, strerror(ERANGE));
		rval = 1;
	}
	++gargv;
	return (rval);
}