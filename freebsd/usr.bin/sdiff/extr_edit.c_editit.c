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
typedef  int /*<<< orphan*/  sig_t ;
typedef  int pid_t ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGQUIT ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 char* _PATH_VI ; 
 int /*<<< orphan*/  _exit (int) ; 
 int errno ; 
 int /*<<< orphan*/  execlp (char const*,char const*,char const*,char*) ; 
 int fork () ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
editit(const char *pathname)
{
	sig_t sighup, sigint, sigquit, sigchld;
	pid_t pid;
	int saved_errno, st, ret = -1;
	const char *ed;

	ed = getenv("VISUAL");
	if (ed == NULL)
		ed = getenv("EDITOR");
	if (ed == NULL)
		ed = _PATH_VI;

	sighup = signal(SIGHUP, SIG_IGN);
	sigint = signal(SIGINT, SIG_IGN);
	sigquit = signal(SIGQUIT, SIG_IGN);
	sigchld = signal(SIGCHLD, SIG_DFL);
	if ((pid = fork()) == -1)
		goto fail;
	if (pid == 0) {
		execlp(ed, ed, pathname, (char *)NULL);
		_exit(127);
	}
	while (waitpid(pid, &st, 0) == -1)
		if (errno != EINTR)
			goto fail;
	if (!WIFEXITED(st))
		errno = EINTR;
	else
		ret = WEXITSTATUS(st);

 fail:
	saved_errno = errno;
	(void)signal(SIGHUP, sighup);
	(void)signal(SIGINT, sigint);
	(void)signal(SIGQUIT, sigquit);
	(void)signal(SIGCHLD, sigchld);
	errno = saved_errno;
	return (ret);
}