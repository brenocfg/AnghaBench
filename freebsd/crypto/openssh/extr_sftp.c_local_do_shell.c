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
 scalar_t__ EINTR ; 
 scalar_t__ WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 char* _PATH_BSHELL ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  debug3 (char*,char*,...) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  execl (char*,char*,char*,...) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int fork () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (scalar_t__) ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
local_do_shell(const char *args)
{
	int status;
	char *shell;
	pid_t pid;

	if (!*args)
		args = NULL;

	if ((shell = getenv("SHELL")) == NULL || *shell == '\0')
		shell = _PATH_BSHELL;

	if ((pid = fork()) == -1)
		fatal("Couldn't fork: %s", strerror(errno));

	if (pid == 0) {
		/* XXX: child has pipe fds to ssh subproc open - issue? */
		if (args) {
			debug3("Executing %s -c \"%s\"", shell, args);
			execl(shell, shell, "-c", args, (char *)NULL);
		} else {
			debug3("Executing %s", shell);
			execl(shell, shell, (char *)NULL);
		}
		fprintf(stderr, "Couldn't execute \"%s\": %s\n", shell,
		    strerror(errno));
		_exit(1);
	}
	while (waitpid(pid, &status, 0) == -1)
		if (errno != EINTR)
			fatal("Couldn't wait for child: %s", strerror(errno));
	if (!WIFEXITED(status))
		error("Shell exited abnormally");
	else if (WEXITSTATUS(status))
		error("Shell exited with status %d", WEXITSTATUS(status));
}