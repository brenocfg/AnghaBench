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
struct pmcstat_target {int /*<<< orphan*/  pt_pid; } ;
struct pmcstat_args {int /*<<< orphan*/  pa_targets; int /*<<< orphan*/ * pa_argv; } ;
struct kevent {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNIX ; 
 size_t CHILDSOCKET ; 
 int /*<<< orphan*/  EVFILT_PROC ; 
 int EV_ADD ; 
 int EV_ONESHOT ; 
 int /*<<< orphan*/  EV_SET (struct kevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  EX_SOFTWARE ; 
 int /*<<< orphan*/  NOTE_EXIT ; 
 size_t PARENTSOCKET ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct pmcstat_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fork () ; 
 int /*<<< orphan*/  getppid () ; 
 scalar_t__ kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmcstat_target* malloc (int) ; 
 int /*<<< orphan*/  pt_next ; 
 scalar_t__ read (int,char*,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int write (int,char*,int) ; 

void
pmcstat_create_process(int *pmcstat_sockpair, struct pmcstat_args *args,
    int pmcstat_kq)
{
	char token;
	pid_t pid;
	struct kevent kev;
	struct pmcstat_target *pt;

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, pmcstat_sockpair) < 0)
		err(EX_OSERR, "ERROR: cannot create socket pair");

	switch (pid = fork()) {
	case -1:
		err(EX_OSERR, "ERROR: cannot fork");
		/*NOTREACHED*/

	case 0:		/* child */
		(void) close(pmcstat_sockpair[PARENTSOCKET]);

		/* Write a token to tell our parent we've started executing. */
		if (write(pmcstat_sockpair[CHILDSOCKET], "+", 1) != 1)
			err(EX_OSERR, "ERROR (child): cannot write token");

		/* Wait for our parent to signal us to start. */
		if (read(pmcstat_sockpair[CHILDSOCKET], &token, 1) < 0)
			err(EX_OSERR, "ERROR (child): cannot read token");
		(void) close(pmcstat_sockpair[CHILDSOCKET]);

		/* exec() the program requested */
		execvp(*args->pa_argv, args->pa_argv);
		/* and if that fails, notify the parent */
		kill(getppid(), SIGCHLD);
		err(EX_OSERR, "ERROR: execvp \"%s\" failed", *args->pa_argv);
		/*NOTREACHED*/

	default:	/* parent */
		(void) close(pmcstat_sockpair[CHILDSOCKET]);
		break;
	}

	/* Ask to be notified via a kevent when the target process exits. */
	EV_SET(&kev, pid, EVFILT_PROC, EV_ADD | EV_ONESHOT, NOTE_EXIT, 0,
	    NULL);
	if (kevent(pmcstat_kq, &kev, 1, NULL, 0, NULL) < 0)
		err(EX_OSERR, "ERROR: cannot monitor child process %d", pid);

	if ((pt = malloc(sizeof(*pt))) == NULL)
		errx(EX_SOFTWARE, "ERROR: Out of memory.");

	pt->pt_pid = pid;
	SLIST_INSERT_HEAD(&args->pa_targets, pt, pt_next);

	/* Wait for the child to signal that its ready to go. */
	if (read(pmcstat_sockpair[PARENTSOCKET], &token, 1) < 0)
		err(EX_OSERR, "ERROR (parent): cannot read token");

	return;
}