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
typedef  int /*<<< orphan*/  cstat ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fail_errno (char*) ; 
 int fork () ; 
 scalar_t__ pipe (int*) ; 
 scalar_t__ read (int,int*,int) ; 
 scalar_t__ waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write (int,int*,int) ; 

__attribute__((used)) static int
child_worker(int (*func)(void *arg), void *arg, int *stat)
{
	pid_t pid;
	int pfd[2], cstat;

	if (pipe(pfd) < 0) {
		fail_errno("pipe");
		return (-1);
	}

	pid = fork();
	switch (pid) {
	case -1:
		/* Error. */
		fail_errno("fork");
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	case 0:
		/* Child. */
		cstat = func(arg);
		write(pfd[1], &cstat, sizeof(cstat));
		exit(0);
	}

	if (read(pfd[0], stat, sizeof(*stat)) < 0) {
		fail_errno("read(pipe)");
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	if (waitpid(pid, NULL, 0) < 0) {
		fail_errno("wait");
		close(pfd[0]);
		close(pfd[1]);
		return (-1);
	}
	close(pfd[0]);
	close(pfd[1]);
	return (0);
}