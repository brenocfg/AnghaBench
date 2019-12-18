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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int LOG_ERR ; 
 int LOG_SYSLOG ; 
 int /*<<< orphan*/  LocalHostName ; 
 int /*<<< orphan*/  dprintf (char*,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  logmsg (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void
logerror(const char *msg)
{
	char buf[512];
	static int recursed = 0;

	/* If there's an error while trying to log an error, give up. */
	if (recursed)
		return;
	recursed++;
	if (errno != 0) {
		(void)snprintf(buf, sizeof(buf), "%s: %s", msg,
		    strerror(errno));
		msg = buf;
	}
	errno = 0;
	dprintf("%s\n", buf);
	logmsg(LOG_SYSLOG|LOG_ERR, NULL, LocalHostName, "syslogd", NULL, NULL,
	    NULL, msg, 0);
	recursed--;
}