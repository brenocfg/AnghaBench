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
 int /*<<< orphan*/  LOG_WARNING ; 
 int LPD_ADDFROMLINE ; 
 int LPD_LOGCONNERR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 char* from_host ; 
 char* local_host ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void
fhosterr(int ch_opts, char *sysmsg, char *usermsg)
{

	/*
	 * If lpd was started up to print connection errors, then write
	 * the syslog message before the user message.
	 * And for many of the syslog messages, it is helpful to first
	 * write the from_host (if it is known) as a separate syslog
	 * message, since the hostname may be so long.
	 */
	if (ch_opts & LPD_LOGCONNERR) {
		if (ch_opts & LPD_ADDFROMLINE) {
		    syslog(LOG_WARNING, "for connection from %s:", from_host);
		}
		syslog(LOG_WARNING, "%s", sysmsg);
	}

	/*
	 * Now send the error message to the remote host which is trying
	 * to make the connection.
	 */
	printf("%s [@%s]: %s\n", progname, local_host, usermsg);
	fflush(stdout);

	/* 
	 * Add a minimal delay before exiting (and disconnecting from the
	 * sending-host).  This is just in case that machine responds by
	 * INSTANTLY retrying (and instantly re-failing...).  This may also
	 * give the other side more time to read the error message.
	 */
	sleep(2);			/* a paranoid throttling measure */
	exit(1);
}