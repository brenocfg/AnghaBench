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
typedef  scalar_t__ time_t ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  intmax_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 char* ctime (scalar_t__*) ; 
 char* ident ; 
 int /*<<< orphan*/ * realpath (char*,char*) ; 
 char* remotehost ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*,char*,char*,int /*<<< orphan*/ ,long) ; 
 scalar_t__ statfd ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  time (scalar_t__*) ; 
 int /*<<< orphan*/  write (scalar_t__,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
logxfer(char *name, off_t size, time_t start)
{
	char buf[MAXPATHLEN + 1024];
	char path[MAXPATHLEN + 1];
	time_t now;

	if (statfd >= 0) {
		time(&now);
		if (realpath(name, path) == NULL) {
			syslog(LOG_NOTICE, "realpath failed on %s: %m", path);
			return;
		}
		snprintf(buf, sizeof(buf), "%.20s!%s!%s!%s!%jd!%ld\n",
			ctime(&now)+4, ident, remotehost,
			path, (intmax_t)size,
			(long)(now - start + (now == start)));
		write(statfd, buf, strlen(buf));
	}
}