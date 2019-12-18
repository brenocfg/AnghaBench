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
 int /*<<< orphan*/  FLUSHTAPEBUF () ; 
 int /*<<< orphan*/  HIGHDENSITYTREC ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NTREC ; 
 char* _PATH_DEVNULL ; 
 char* _PATH_TTY ; 
 scalar_t__ bflag ; 
 int /*<<< orphan*/  done (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  getuid () ; 
 char* host ; 
 int /*<<< orphan*/ * magtape ; 
 int /*<<< orphan*/  newtapebuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntrec ; 
 int /*<<< orphan*/  pipecmdin ; 
 int /*<<< orphan*/  pipein ; 
 scalar_t__ rmthost (char*) ; 
 scalar_t__ setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * stdin ; 
 char* strchr (char*,char) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/ * strdup (char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * terminal ; 

void
setinput(char *source, int ispipecommand)
{
	FLUSHTAPEBUF();
	if (bflag)
		newtapebuf(ntrec);
	else
		newtapebuf(MAX(NTREC, HIGHDENSITYTREC));
	terminal = stdin;

	if (ispipecommand)
		pipecmdin++;
	else
#ifdef RRESTORE
	if (strchr(source, ':')) {
		host = source;
		source = strchr(host, ':');
		*source++ = '\0';
		if (rmthost(host) == 0)
			done(1);
	} else
#endif
	if (strcmp(source, "-") == 0) {
		/*
		 * Since input is coming from a pipe we must establish
		 * our own connection to the terminal.
		 */
		terminal = fopen(_PATH_TTY, "r");
		if (terminal == NULL) {
			(void)fprintf(stderr, "cannot open %s: %s\n",
			    _PATH_TTY, strerror(errno));
			terminal = fopen(_PATH_DEVNULL, "r");
			if (terminal == NULL) {
				(void)fprintf(stderr, "cannot open %s: %s\n",
				    _PATH_DEVNULL, strerror(errno));
				done(1);
			}
		}
		pipein++;
	}
	/* no longer need or want root privileges */
	if (setuid(getuid()) != 0) {
		fprintf(stderr, "setuid failed\n");
		done(1);
	}
	magtape = strdup(source);
	if (magtape == NULL) {
		fprintf(stderr, "Cannot allocate space for magtape buffer\n");
		done(1);
	}
}