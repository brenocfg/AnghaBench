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
typedef  int /*<<< orphan*/  state_func_t ;
typedef  int /*<<< orphan*/  blocked ;
typedef  int /*<<< orphan*/  block ;

/* Variables and functions */
 int /*<<< orphan*/  death_single ; 
 int /*<<< orphan*/  revoke_ttys () ; 
 int /*<<< orphan*/  runshutdown () ; 
 int sysctlbyname (char*,int*,size_t*,int*,int) ; 

__attribute__((used)) static state_func_t
death(void)
{
	int block, blocked;
	size_t len;

	/* Temporarily block suspend. */
	len = sizeof(blocked);
	block = 1;
	if (sysctlbyname("kern.suspend_blocked", &blocked, &len,
	    &block, sizeof(block)) == -1)
		blocked = 0;

	/*
	 * Also revoke the TTY here.  Because runshutdown() may reopen
	 * the TTY whose getty we're killing here, there is no guarantee
	 * runshutdown() will perform the initial open() call, causing
	 * the terminal attributes to be misconfigured.
	 */
	revoke_ttys();

	/* Try to run the rc.shutdown script within a period of time */
	runshutdown();

	/* Unblock suspend if we blocked it. */
	if (!blocked)
		sysctlbyname("kern.suspend_blocked", NULL, NULL,
		    &blocked, sizeof(blocked));

	return (state_func_t) death_single;
}