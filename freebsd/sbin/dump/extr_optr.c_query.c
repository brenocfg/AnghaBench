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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SIGALRM ; 
 scalar_t__ SIG_IGN ; 
 int /*<<< orphan*/  _PATH_TTY ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarmcatch (int /*<<< orphan*/ ) ; 
 char const* attnmessage ; 
 int /*<<< orphan*/  clearerr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  quit (char*,...) ; 
 scalar_t__ sig ; 
 scalar_t__ signal (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ timeout ; 

int
query(const char *question)
{
	char	replybuffer[64];
	int	back, errcount;
	FILE	*mytty;

	if ((mytty = fopen(_PATH_TTY, "r")) == NULL)
		quit("fopen on %s fails: %s\n", _PATH_TTY, strerror(errno));
	attnmessage = question;
	timeout = 0;
	alarmcatch(0);
	back = -1;
	errcount = 0;
	do {
		if (fgets(replybuffer, 63, mytty) == NULL) {
			clearerr(mytty);
			if (++errcount > 30)	/* XXX	ugly */
				quit("excessive operator query failures\n");
		} else if (replybuffer[0] == 'y' || replybuffer[0] == 'Y') {
			back = 1;
		} else if (replybuffer[0] == 'n' || replybuffer[0] == 'N') {
			back = 0;
		} else {
			(void) fprintf(stderr,
			    "  DUMP: \"Yes\" or \"No\"?\n");
			(void) fprintf(stderr,
			    "  DUMP: %s: (\"yes\" or \"no\") ", question);
		}
	} while (back < 0);

	/*
	 *	Turn off the alarm, and reset the signal to trap out..
	 */
	(void) alarm(0);
	if (signal(SIGALRM, sig) == SIG_IGN)
		signal(SIGALRM, SIG_IGN);
	(void) fclose(mytty);
	return(back);
}