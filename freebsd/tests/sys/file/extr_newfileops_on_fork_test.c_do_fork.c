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
 scalar_t__ EBADF ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 scalar_t__ ftruncate (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ listen_fd ; 
 int /*<<< orphan*/  waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
do_fork(void)
{
	int pid;

	pid = fork();
	if (pid < 0)
		err(1, "fork");
	if (pid > 0) {
		waitpid(pid, NULL, 0);
		exit(0);
	}

	/*
	 * We will call ftruncate(2) on the next available file descriptor,
	 * listen_fd+1, and get back EBADF if it's not a valid descriptor,
	 * and EINVAL if it is.  This (currently) works fine in practice.
	 */
	if (ftruncate(listen_fd + 1, 0) < 0) {
		if (errno == EBADF)
			exit(0);
		else if (errno == EINVAL)
			errx(1, "file descriptor still open in child");
		else
			err(1, "unexpected error");
	} else
		errx(1, "ftruncate succeeded");
}