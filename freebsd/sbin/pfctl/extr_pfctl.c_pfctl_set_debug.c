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
typedef  int /*<<< orphan*/  u_int32_t ;
struct pfctl {int debug_set; int opts; int /*<<< orphan*/  debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIOCSETDEBUG ; 
 int PFCTL_FLAG_OPTION ; 
 int /*<<< orphan*/  PF_DEBUG_MISC ; 
 int /*<<< orphan*/  PF_DEBUG_NOISY ; 
 int /*<<< orphan*/  PF_DEBUG_NONE ; 
 int /*<<< orphan*/  PF_DEBUG_URGENT ; 
 int PF_OPT_NOACTION ; 
 int PF_OPT_VERBOSE ; 
 int /*<<< orphan*/  dev ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int loadopt ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

int
pfctl_set_debug(struct pfctl *pf, char *d)
{
	u_int32_t	level;

	if ((loadopt & PFCTL_FLAG_OPTION) == 0)
		return (0);

	if (!strcmp(d, "none"))
		pf->debug = PF_DEBUG_NONE;
	else if (!strcmp(d, "urgent"))
		pf->debug = PF_DEBUG_URGENT;
	else if (!strcmp(d, "misc"))
		pf->debug = PF_DEBUG_MISC;
	else if (!strcmp(d, "loud"))
		pf->debug = PF_DEBUG_NOISY;
	else {
		warnx("unknown debug level \"%s\"", d);
		return (-1);
	}

	pf->debug_set = 1;
	level = pf->debug;

	if ((pf->opts & PF_OPT_NOACTION) == 0)
		if (ioctl(dev, DIOCSETDEBUG, &level))
			err(1, "DIOCSETDEBUG");

	if (pf->opts & PF_OPT_VERBOSE)
		printf("set debug %s\n", d);

	return (0);
}