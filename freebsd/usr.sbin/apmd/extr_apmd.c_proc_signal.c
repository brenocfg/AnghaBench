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
 int /*<<< orphan*/  LOG_NOTICE ; 
#define  SIGCHLD 130 
#define  SIGHUP 129 
#define  SIGTERM 128 
 int read (int,int*,int) ; 
 int /*<<< orphan*/  restart () ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wait_child () ; 
 int /*<<< orphan*/  warn (char*,int) ; 

int
proc_signal(int fd)
{
	int rc = 0;
	int sig;

	while (read(fd, &sig, sizeof sig) == sizeof sig) {
		syslog(LOG_INFO, "caught signal: %d", sig);
		switch (sig) {
		case SIGHUP:
			syslog(LOG_NOTICE, "restart by SIG");
			restart();
			break;
		case SIGTERM:
			syslog(LOG_NOTICE, "going down on signal %d", sig);
			rc = -1;
			return rc;
		case SIGCHLD:
			wait_child();
			break;
		default:
			warn("unexpected signal(%d) received.", sig);
			break;
		}
	}
	return rc;
}