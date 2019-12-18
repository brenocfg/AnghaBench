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
 scalar_t__ strcasecmp (char const*,char*) ; 
 long strtoul (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*,char const*) ; 

__attribute__((used)) static int
is_true(const char *boolean)
{
	char *endp;
	long val;

	val = strtoul(boolean, &endp, 0);
	if (*endp == '\0')
		return (val != 0 ? 1 : 0);
	if (strcasecmp(boolean, "true") == 0 ||
	    strcasecmp(boolean, "yes") == 0 ||
	    strcasecmp(boolean, "enable") == 0)
		return (1);
	if (strcasecmp(boolean, "false") == 0 ||
	    strcasecmp(boolean, "no") == 0 ||
	    strcasecmp(boolean, "disable") == 0)
		return (0);
	/* Well, I have no idea what the user wants, so... */
	warnx("invalid boolean argument \"%s\"", boolean);
	usage();
	/* NOTREACHED */

	return (0);
}