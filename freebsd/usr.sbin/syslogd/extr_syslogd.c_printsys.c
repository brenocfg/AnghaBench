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
 int DEFSPRI ; 
 int IGN_CONS ; 
 long INT_MAX ; 
 int LOG_CONSOLE ; 
 int LOG_FACMASK ; 
 int LOG_PRIMASK ; 
 int /*<<< orphan*/  LocalHostName ; 
 int SYNC_FILE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  logmsg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static void
printsys(char *msg)
{
	char *p, *q;
	long n;
	int flags, isprintf, pri;

	flags = SYNC_FILE;	/* fsync after write */
	p = msg;
	pri = DEFSPRI;
	isprintf = 1;
	if (*p == '<') {
		errno = 0;
		n = strtol(p + 1, &q, 10);
		if (*q == '>' && n >= 0 && n < INT_MAX && errno == 0) {
			p = q + 1;
			pri = n;
			isprintf = 0;
		}
	}
	/*
	 * Kernel printf's and LOG_CONSOLE messages have been displayed
	 * on the console already.
	 */
	if (isprintf || (pri & LOG_FACMASK) == LOG_CONSOLE)
		flags |= IGN_CONS;
	if (pri &~ (LOG_FACMASK|LOG_PRIMASK))
		pri = DEFSPRI;
	logmsg(pri, NULL, LocalHostName, "kernel", NULL, NULL, NULL, p, flags);
}