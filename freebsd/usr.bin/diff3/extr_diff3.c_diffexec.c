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
 int /*<<< orphan*/  PD_CLOEXEC ; 
 int /*<<< orphan*/  STDOUT_FILENO ; 
 int /*<<< orphan*/  close (int) ; 
 int dup2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  execvp (char const*,char**) ; 
 int pdfork (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
diffexec(const char *diffprog, char **diffargv, int fd[])
{
	int pid, pd;

	switch (pid = pdfork(&pd, PD_CLOEXEC)) {
	case 0:
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			err(2, "child could not duplicate descriptor");
		close(fd[1]);
		execvp(diffprog, diffargv);
		err(2, "could not execute diff: %s", diffprog);
		break;
	case -1:
		err(2, "could not fork");
		break;
	}
	close(fd[1]);
	return (pd);
}