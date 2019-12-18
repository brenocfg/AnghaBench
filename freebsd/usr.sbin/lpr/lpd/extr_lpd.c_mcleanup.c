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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  _PATH_SOCKETNAME ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ lflag ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcleanup(int signo)
{
	/*
	 * XXX syslog(3) is not signal-safe.
	 */
	if (lflag) {
		if (signo)
			syslog(LOG_INFO, "exiting on signal %d", signo);
		else
			syslog(LOG_INFO, "exiting");
	}
	unlink(_PATH_SOCKETNAME);
	exit(0);
}