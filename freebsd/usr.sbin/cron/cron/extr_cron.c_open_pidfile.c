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
typedef  int /*<<< orphan*/  pidfile ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 scalar_t__ EEXIST ; 
 int /*<<< orphan*/  ERROR_EXIT ; 
 int MAX_FNAME ; 
 int MAX_TEMPSTR ; 
 int /*<<< orphan*/  PIDDIR ; 
 char* PIDFILE ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  log_it (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * pfh ; 
 int /*<<< orphan*/ * pidfile_open (char*,int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 char* strerror (scalar_t__) ; 

__attribute__((used)) static void
open_pidfile(void)
{
	char	pidfile[MAX_FNAME];
	char	buf[MAX_TEMPSTR];
	int	otherpid;

	(void) snprintf(pidfile, sizeof(pidfile), PIDFILE, PIDDIR);
	pfh = pidfile_open(pidfile, 0600, &otherpid);
	if (pfh == NULL) {
		if (errno == EEXIST) {
			snprintf(buf, sizeof(buf),
			    "cron already running, pid: %d", otherpid);
		} else {
			snprintf(buf, sizeof(buf),
			    "can't open or create %s: %s", pidfile,
			    strerror(errno));
		}
		log_it("CRON", getpid(), "DEATH", buf);
		errx(ERROR_EXIT, "%s", buf);
	}
}