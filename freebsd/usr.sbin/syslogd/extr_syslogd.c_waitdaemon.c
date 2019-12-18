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
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGALRM ; 
 int STDERR_FILENO ; 
 int STDIN_FILENO ; 
 int STDOUT_FILENO ; 
 int /*<<< orphan*/  WCOREDUMP (int) ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  WIFSIGNALED (int) ; 
 int /*<<< orphan*/  WTERMSIG (int) ; 
 int /*<<< orphan*/  _PATH_DEVNULL ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  errx (int,char*,int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int getppid () ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int setsid () ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timedout ; 
 int wait3 (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
waitdaemon(int maxwait)
{
	int fd;
	int status;
	pid_t pid, childpid;

	switch (childpid = fork()) {
	case -1:
		return (-1);
	case 0:
		break;
	default:
		signal(SIGALRM, timedout);
		alarm(maxwait);
		while ((pid = wait3(&status, 0, NULL)) != -1) {
			if (WIFEXITED(status))
				errx(1, "child pid %d exited with return code %d",
					pid, WEXITSTATUS(status));
			if (WIFSIGNALED(status))
				errx(1, "child pid %d exited on signal %d%s",
					pid, WTERMSIG(status),
					WCOREDUMP(status) ? " (core dumped)" :
					"");
			if (pid == childpid)	/* it's gone... */
				break;
		}
		exit(0);
	}

	if (setsid() == -1)
		return (-1);

	(void)chdir("/");
	if ((fd = open(_PATH_DEVNULL, O_RDWR, 0)) != -1) {
		(void)dup2(fd, STDIN_FILENO);
		(void)dup2(fd, STDOUT_FILENO);
		(void)dup2(fd, STDERR_FILENO);
		if (fd > STDERR_FILENO)
			(void)close(fd);
	}
	return (getppid());
}