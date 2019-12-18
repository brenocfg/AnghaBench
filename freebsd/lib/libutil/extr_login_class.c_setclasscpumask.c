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
typedef  int /*<<< orphan*/  maskset ;
typedef  int /*<<< orphan*/  login_cap_t ;
typedef  int /*<<< orphan*/  cpusetid_t ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_LEVEL_CPUSET ; 
 int /*<<< orphan*/  CPU_WHICH_PID ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 scalar_t__ cpuset (int /*<<< orphan*/ *) ; 
 scalar_t__ cpuset_setaffinity (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  list2cpuset (char const*,int /*<<< orphan*/ *) ; 
 char* login_getcapstr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char const*,...) ; 

void
setclasscpumask(login_cap_t *lc)
{
	const char *maskstr;
	cpuset_t maskset;
	cpusetid_t setid;

	maskstr = login_getcapstr(lc, "cpumask", NULL, NULL);
	CPU_ZERO(&maskset);
	if (maskstr == NULL)
		return;
	if (strcasecmp("default", maskstr) == 0)
		return;
	if (!list2cpuset(maskstr, &maskset)) {
		syslog(LOG_WARNING,
		    "list2cpuset(%s) invalid mask specification", maskstr);
		return;
	}

	if (cpuset(&setid) != 0) {
		syslog(LOG_ERR, "cpuset(): %s", strerror(errno));
		return;
	}

	if (cpuset_setaffinity(CPU_LEVEL_CPUSET, CPU_WHICH_PID, -1,
	    sizeof(maskset), &maskset) != 0)
		syslog(LOG_ERR, "cpuset_setaffinity(%s): %s", maskstr,
		    strerror(errno));
}