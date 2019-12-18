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
 int LINESIZE ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTSTP ; 
 int /*<<< orphan*/  SIGTTIN ; 
 int /*<<< orphan*/  SIGTTOU ; 
 scalar_t__ SIG_IGN ; 
 scalar_t__ execute (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 scalar_t__ hangup ; 
 scalar_t__ incfile () ; 
 int /*<<< orphan*/  input ; 
 scalar_t__ intr ; 
 scalar_t__ loading ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* prompt ; 
 scalar_t__ readline (int /*<<< orphan*/ ,char*,int) ; 
 int reset_on_stop ; 
 int /*<<< orphan*/  setexit () ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sourcing ; 
 int /*<<< orphan*/  sreset () ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ stop ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  unstack () ; 
 int /*<<< orphan*/ * value (char*) ; 

void
commands(void)
{
	int n, eofloop = 0;
	char linebuf[LINESIZE];

	if (!sourcing) {
		if (signal(SIGINT, SIG_IGN) != SIG_IGN)
			(void)signal(SIGINT, intr);
		if (signal(SIGHUP, SIG_IGN) != SIG_IGN)
			(void)signal(SIGHUP, hangup);
		(void)signal(SIGTSTP, stop);
		(void)signal(SIGTTOU, stop);
		(void)signal(SIGTTIN, stop);
	}
	setexit();
	for (;;) {
		/*
		 * Print the prompt, if needed.  Clear out
		 * string space, and flush the output.
		 */
		if (!sourcing && value("interactive") != NULL) {
			if ((value("autoinc") != NULL) && (incfile() > 0))
				printf("New mail has arrived.\n");
			reset_on_stop = 1;
			printf("%s", prompt);
		}
		(void)fflush(stdout);
		sreset();
		/*
		 * Read a line of commands from the current input
		 * and handle end of file specially.
		 */
		n = 0;
		for (;;) {
			if (readline(input, &linebuf[n], LINESIZE - n) < 0) {
				if (n == 0)
					n = -1;
				break;
			}
			if ((n = strlen(linebuf)) == 0)
				break;
			n--;
			if (linebuf[n] != '\\')
				break;
			linebuf[n++] = ' ';
		}
		reset_on_stop = 0;
		if (n < 0) {
				/* eof */
			if (loading)
				break;
			if (sourcing) {
				unstack();
				continue;
			}
			if (value("interactive") != NULL &&
			    value("ignoreeof") != NULL &&
			    ++eofloop < 25) {
				printf("Use \"quit\" to quit.\n");
				continue;
			}
			break;
		}
		eofloop = 0;
		if (execute(linebuf, 0))
			break;
	}
}