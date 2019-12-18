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
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  execve (char*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ pipe (int*) ; 
 int vfork () ; 

__attribute__((used)) static void
cmd_popen(char *command, FILE **iop)
{
	char *argv[4];
	int pdes[4];
	int pid;

	if (pipe(pdes) < 0)
		goto error;

	if (pipe(pdes + 2) < 0) {
		close(pdes[0]);
		close(pdes[1]);
		goto error;
	}
	argv[0] = "sh";
	argv[1] = "-c";
	argv[2] = command;
	argv[3] = NULL;

	switch ((pid = vfork())) {
	case -1:			/* Error. */
		close(pdes[0]);
		close(pdes[1]);
		close(pdes[2]);
		close(pdes[3]);
		goto error;
	case 0:			/* Child. */
		dup2(pdes[1], STDOUT_FILENO);
		dup2(pdes[2], STDIN_FILENO);
		close(pdes[0]);
		close(pdes[3]);
		execve("/bin/sh", argv, environ);
		exit(127);
	default:
		break;
	}
	iop[0] = fdopen(pdes[3], "w");
	iop[1] = fdopen(pdes[0], "r");
	close(pdes[1]);
	close(pdes[2]);
	return;
error:
	iop[0] = iop[1] = NULL;
}