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
struct printer {char** filters; int /*<<< orphan*/  printer; scalar_t__ remote; scalar_t__* lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOABORT ; 
 int /*<<< orphan*/  LOG_ERR ; 
 size_t LPF_INPUT ; 
 size_t LPF_OUTPUT ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  TFILENAME ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closeallfds (int) ; 
 int /*<<< orphan*/  closelog () ; 
 scalar_t__ dofork (struct printer const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execl (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  length ; 
 int mkstemp (int /*<<< orphan*/ ) ; 
 scalar_t__ of_pid ; 
 int ofd ; 
 int /*<<< orphan*/  opennet (struct printer const*) ; 
 int /*<<< orphan*/  openrem (struct printer const*) ; 
 int /*<<< orphan*/  opentty (struct printer const*) ; 
 int pfd ; 
 int /*<<< orphan*/  pipe (int*) ; 
 int /*<<< orphan*/ * strchr (scalar_t__*,char) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  syslog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int tfd ; 
 int /*<<< orphan*/  tfile ; 
 int /*<<< orphan*/  width ; 

__attribute__((used)) static void
openpr(const struct printer *pp)
{
	int p[2];
	char *cp;

	if (pp->remote) {
		openrem(pp);
		/*
		 * Lpd does support the setting of 'of=' filters for
		 * jobs going to remote machines, but that does not
		 * have the same meaning as 'of=' does when handling
		 * local print queues.  For remote machines, all 'of='
		 * filter processing is handled in sendfile(), and that
		 * does not use these global "output filter" variables.
		 */ 
		ofd = -1;
		of_pid = 0;
		return;
	} else if (*pp->lp) {
		if (strchr(pp->lp, '@') != NULL)
			opennet(pp);
		else
			opentty(pp);
	} else {
		syslog(LOG_ERR, "%s: no line printer device or host name",
		    pp->printer);
		exit(1);
	}

	/*
	 * Start up an output filter, if needed.
	 */
	if (pp->filters[LPF_OUTPUT] && !pp->filters[LPF_INPUT] && !of_pid) {
		pipe(p);
		if (pp->remote) {
			strcpy(tfile, TFILENAME);
			tfd = mkstemp(tfile);
		}
		if ((of_pid = dofork(pp, DOABORT)) == 0) {	/* child */
			dup2(p[0], STDIN_FILENO);	/* pipe is std in */
			/* tfile/printer is stdout */
			dup2(pp->remote ? tfd : pfd, STDOUT_FILENO);
			closelog();
			closeallfds(3);
			if ((cp = strrchr(pp->filters[LPF_OUTPUT], '/')) == NULL)
				cp = pp->filters[LPF_OUTPUT];
			else
				cp++;
			execl(pp->filters[LPF_OUTPUT], cp, width, length,
			      (char *)0);
			syslog(LOG_ERR, "%s: execl(%s): %m", pp->printer,
			    pp->filters[LPF_OUTPUT]);
			exit(1);
		}
		(void) close(p[0]);		/* close input side */
		ofd = p[1];			/* use pipe for output */
	} else {
		ofd = pfd;
		of_pid = 0;
	}
}