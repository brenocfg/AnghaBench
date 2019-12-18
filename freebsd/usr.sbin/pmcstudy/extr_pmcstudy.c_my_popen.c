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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  execve (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 int /*<<< orphan*/  fork () ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 

__attribute__((used)) static FILE *
my_popen(const char *command, const char *dir, pid_t *p_pid)
{
	FILE *io_out, *io_in;
	int pdesin[2], pdesout[2];
	char *argv[4];
	pid_t pid;
	char cmd[4];
	char cmd2[1024];
	char arg1[4];

	if ((strcmp(dir, "r") != 0) &&
	    (strcmp(dir, "w") != 0)) {
		errno = EINVAL;
		return(NULL);
	}
	if (pipe(pdesin) < 0)
		return (NULL);

	if (pipe(pdesout) < 0) {
		(void)close(pdesin[0]);
		(void)close(pdesin[1]);
		return (NULL);
	}
	strcpy(cmd, "sh");
	strcpy(arg1, "-c");
	strcpy(cmd2, command);
	argv[0] = cmd;
	argv[1] = arg1;
	argv[2] = cmd2;
	argv[3] = NULL;

	switch (pid = fork()) {
	case -1:			/* Error. */
		(void)close(pdesin[0]);
		(void)close(pdesin[1]);
		(void)close(pdesout[0]);
		(void)close(pdesout[1]);
		return (NULL);
		/* NOTREACHED */
	case 0:				/* Child. */
		/* Close out un-used sides */
		(void)close(pdesin[1]);
		(void)close(pdesout[0]);
		/* Now prepare the stdin of the process */
		close(0);
		(void)dup(pdesin[0]);
		(void)close(pdesin[0]);
		/* Now prepare the stdout of the process */
		close(1);
		(void)dup(pdesout[1]);
		/* And lets do stderr just in case */
		close(2);
		(void)dup(pdesout[1]);
		(void)close(pdesout[1]);
		/* Now run it */
		execve("/bin/sh", argv, environ);
		exit(127);
		/* NOTREACHED */
	}
	/* Parent; assume fdopen can't fail. */
	/* Store the pid */
	*p_pid = pid;
	if (strcmp(dir, "r") != 0) {
		io_out = fdopen(pdesin[1], "w");
		(void)close(pdesin[0]);
		(void)close(pdesout[0]);
		(void)close(pdesout[1]);
		return(io_out);
 	} else {
		/* Prepare the input stream */
		io_in = fdopen(pdesout[0], "r");
		(void)close(pdesout[1]);
		(void)close(pdesin[0]);
		(void)close(pdesin[1]);
		return (io_in);
	}
}