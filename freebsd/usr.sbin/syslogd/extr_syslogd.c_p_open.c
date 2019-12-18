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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  STDERR_FILENO ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  _PATH_BSHELL ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  alarm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  execvp (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  logerror (char*) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pipe (int*) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 char* strdup (char const*) ; 

__attribute__((used)) static int
p_open(const char *prog, pid_t *rpid)
{
	int pfd[2], nulldesc;
	pid_t pid;
	char *argv[4]; /* sh -c cmd NULL */
	char errmsg[200];

	if (pipe(pfd) == -1)
		return (-1);
	if ((nulldesc = open(_PATH_DEVNULL, O_RDWR)) == -1)
		/* we are royally screwed anyway */
		return (-1);

	switch ((pid = fork())) {
	case -1:
		close(nulldesc);
		return (-1);

	case 0:
		(void)setsid();	/* Avoid catching SIGHUPs. */
		argv[0] = strdup("sh");
		argv[1] = strdup("-c");
		argv[2] = strdup(prog);
		argv[3] = NULL;
		if (argv[0] == NULL || argv[1] == NULL || argv[2] == NULL) {
			logerror("strdup");
			exit(1);
		}

		alarm(0);

		/* Restore signals marked as SIG_IGN. */
		(void)signal(SIGINT, SIG_DFL);
		(void)signal(SIGQUIT, SIG_DFL);
		(void)signal(SIGPIPE, SIG_DFL);

		dup2(pfd[0], STDIN_FILENO);
		dup2(nulldesc, STDOUT_FILENO);
		dup2(nulldesc, STDERR_FILENO);
		closefrom(STDERR_FILENO + 1);

		(void)execvp(_PATH_BSHELL, argv);
		_exit(255);
	}
	close(nulldesc);
	close(pfd[0]);
	/*
	 * Avoid blocking on a hung pipe.  With O_NONBLOCK, we are
	 * supposed to get an EWOULDBLOCK on writev(2), which is
	 * caught by the logic above anyway, which will in turn close
	 * the pipe, and fork a new logging subprocess if necessary.
	 * The stale subprocess will be killed some time later unless
	 * it terminated itself due to closing its input pipe (so we
	 * get rid of really dead puppies).
	 */
	if (fcntl(pfd[1], F_SETFL, O_NONBLOCK) == -1) {
		/* This is bad. */
		(void)snprintf(errmsg, sizeof errmsg,
			       "Warning: cannot change pipe to PID %d to "
			       "non-blocking behaviour.",
			       (int)pid);
		logerror(errmsg);
	}
	*rpid = pid;
	return (pfd[1]);
}