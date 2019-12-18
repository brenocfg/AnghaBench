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
 int /*<<< orphan*/  CLOCK_UPTIME ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_USAGE ; 
 scalar_t__ clock_gettime (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ live ; 
 int /*<<< orphan*/  p_rtable_sysctl (int,int) ; 
 int sysctlbyname (char*,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uptime ; 
 int /*<<< orphan*/  xo_close_container (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_open_container (char*) ; 

void
routepr(int fibnum, int af)
{
	size_t intsize;
	int numfibs;

	if (live == 0)
		return;

	intsize = sizeof(int);
	if (fibnum == -1 &&
	    sysctlbyname("net.my_fibnum", &fibnum, &intsize, NULL, 0) == -1)
		fibnum = 0;
	if (sysctlbyname("net.fibs", &numfibs, &intsize, NULL, 0) == -1)
		numfibs = 1;
	if (fibnum < 0 || fibnum > numfibs - 1)
		errx(EX_USAGE, "%d: invalid fib", fibnum);
	/*
	 * Since kernel & userland use different timebase
	 * (time_uptime vs time_second) and we are reading kernel memory
	 * directly we should do rt_expire --> expire_time conversion.
	 */
	if (clock_gettime(CLOCK_UPTIME, &uptime) < 0)
		err(EX_OSERR, "clock_gettime() failed");

	xo_open_container("route-information");
	xo_emit("{T:Routing tables}");
	if (fibnum)
		xo_emit(" ({L:fib}: {:fib/%d})", fibnum);
	xo_emit("\n");
	p_rtable_sysctl(fibnum, af);
	xo_close_container("route-information");
}