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
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ EFAULT ; 
 scalar_t__ cap_enter () ; 
 scalar_t__ cap_getmode (unsigned int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int pdfork (int*,int /*<<< orphan*/ ) ; 
 int pdwait (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(void)
{
	unsigned int mode;
	pid_t pid;
	int pfd;

	printf("1..27\n");

	mode = 666;
	CHECK(cap_getmode(&mode) == 0);
	/* If cap_getmode() succeeded mode should be modified. */
	CHECK(mode != 666);
	/* We are not in capability mode. */
	CHECK(mode == 0);

	/* Expect EFAULT. */
	errno = 0;
	CHECK(cap_getmode(NULL) == -1);
	CHECK(errno == EFAULT);
	errno = 0;
	CHECK(cap_getmode((void *)(uintptr_t)0xdeadc0de) == -1);
	CHECK(errno == EFAULT);

	/* If parent is not in capability mode, child after fork() also won't be. */
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		mode = 666;
		CHECK(cap_getmode(&mode) == 0);
		/* If cap_getmode() succeeded mode should be modified. */
		CHECK(mode != 666);
		/* We are not in capability mode. */
		CHECK(mode == 0);
		exit(0);
	default:
		if (waitpid(pid, NULL, 0) == -1)
			err(1, "waitpid() failed");
	}

	/* If parent is not in capability mode, child after pdfork() also won't be. */
	pid = pdfork(&pfd, 0);
	switch (pid) {
	case -1:
		err(1, "pdfork() failed");
	case 0:
		mode = 666;
		CHECK(cap_getmode(&mode) == 0);
		/* If cap_getmode() succeeded mode should be modified. */
		CHECK(mode != 666);
		/* We are not in capability mode. */
		CHECK(mode == 0);
		exit(0);
	default:
		if (pdwait(pfd) == -1)
			err(1, "pdwait() failed");
		close(pfd);
	}

	/* In capability mode... */

	CHECK(cap_enter() == 0);

	mode = 666;
	CHECK(cap_getmode(&mode) == 0);
	/* If cap_getmode() succeeded mode should be modified. */
	CHECK(mode != 666);
	/* We are in capability mode. */
	CHECK(mode == 1);

	/* Expect EFAULT. */
	errno = 0;
	CHECK(cap_getmode(NULL) == -1);
	CHECK(errno == EFAULT);
	errno = 0;
	CHECK(cap_getmode((void *)(uintptr_t)0xdeadc0de) == -1);
	CHECK(errno == EFAULT);

	/* If parent is in capability mode, child after fork() also will be. */
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		mode = 666;
		CHECK(cap_getmode(&mode) == 0);
		/* If cap_getmode() succeeded mode should be modified. */
		CHECK(mode != 666);
		/* We are in capability mode. */
		CHECK(mode == 1);
		exit(0);
	default:
		/*
		 * wait(2) and friends are not permitted in the capability mode,
		 * so we can only just wait for a while.
		 */
		sleep(1);
	}

	/* If parent is in capability mode, child after pdfork() also will be. */
	pid = pdfork(&pfd, 0);
	switch (pid) {
	case -1:
		err(1, "pdfork() failed");
	case 0:
		mode = 666;
		CHECK(cap_getmode(&mode) == 0);
		/* If cap_getmode() succeeded mode should be modified. */
		CHECK(mode != 666);
		/* We are in capability mode. */
		CHECK(mode == 1);
		exit(0);
	default:
		if (pdwait(pfd) == -1)
			err(1, "pdwait() failed");
		close(pfd);
	}

	exit(0);
}