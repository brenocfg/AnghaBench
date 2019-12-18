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
 int /*<<< orphan*/  DIALTIMEOUT ; 
 char* DISCONNECT_CMD ; 
 int /*<<< orphan*/  FD ; 
 int /*<<< orphan*/  HOST ; 
 int /*<<< orphan*/  VERBOSE ; 
 int /*<<< orphan*/  biz31_disconnect () ; 
 int /*<<< orphan*/  bizsync (int /*<<< orphan*/ ) ; 
 scalar_t__ boolean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delock (int /*<<< orphan*/ ) ; 
 int detect (char*) ; 
 int /*<<< orphan*/  echo (char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush (char*) ; 
 int /*<<< orphan*/  logent (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/  number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ timeout ; 
 int /*<<< orphan*/  uucplock ; 
 int /*<<< orphan*/  value (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
biz_dialer(char *num, char *mod)
{
	int connected = 0;

	if (!bizsync(FD)) {
		logent(value(HOST), "", "biz", "out of sync");
		printf("bizcomp out of sync\n");
		delock(uucplock);
		exit(0);
	}
	if (boolean(value(VERBOSE)))
		printf("\nstarting call...");
	echo("#\rk$\r$\n");			/* disable auto-answer */
	echo("$>$.$ #\r");			/* tone/pulse dialing */
	echo(mod);
	echo("$\r$\n");
	echo("$>$.$ #\re$ ");			/* disconnection sequence */
	echo(DISCONNECT_CMD);
	echo("\r$\n$\r$\n");
	echo("$>$.$ #\rr$ ");			/* repeat dial */
	echo(num);
	echo("\r$\n");
	if (boolean(value(VERBOSE)))
		printf("ringing...");
	/*
	 * The reply from the BIZCOMP should be:
	 *	`^G NO CONNECTION\r\n^G\r\n'	failure
	 *	` CONNECTION\r\n^G'		success
	 */
	connected = detect(" ");
#ifdef ACULOG
	if (timeout) {
		char line[80];

		(void)snprintf(line, sizeof line, "%ld second dial timeout",
			number(value(DIALTIMEOUT)));
		logent(value(HOST), num, "biz", line);
	}
#endif
	if (!connected)
		flush(" NO CONNECTION\r\n\07\r\n");
	else
		flush("CONNECTION\r\n\07");
	if (timeout)
		biz31_disconnect();	/* insurance */
	return (connected);
}