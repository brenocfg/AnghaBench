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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  ioctl_tests_0 (int) ; 
 int /*<<< orphan*/  ioctl_tests_1 (int) ; 
 int /*<<< orphan*/  ioctl_tests_2 (int) ; 
 int /*<<< orphan*/  ioctl_tests_recv_0 (int) ; 
 int /*<<< orphan*/  ioctl_tests_send_0 (int) ; 
 int pdfork (int*,int /*<<< orphan*/ ) ; 
 int pdwait (int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int waitpid (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
main(void)
{
	int fd, pfd, sp[2];
	pid_t pid;

	printf("1..607\n");

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	ioctl_tests_0(fd);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	ioctl_tests_1(fd);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	ioctl_tests_2(fd);
	CHECK(close(fd) == 0);

	/* Child inherits descriptor and operates on it first. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		ioctl_tests_0(fd);
		CHECK(close(fd) == 0);
		exit(0);
	default:
		if (waitpid(pid, NULL, 0) == -1)
			err(1, "waitpid() failed");
		ioctl_tests_0(fd);
	}
	CHECK(close(fd) == 0);

	/* Child inherits descriptor, but operates on it after parent. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		sleep(1);
		ioctl_tests_0(fd);
		CHECK(close(fd) == 0);
		exit(0);
	default:
		ioctl_tests_0(fd);
		if (waitpid(pid, NULL, 0) == -1)
			err(1, "waitpid() failed");
	}
	CHECK(close(fd) == 0);

	/* Child inherits descriptor and operates on it first. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = pdfork(&pfd, 0);
	switch (pid) {
	case -1:
		err(1, "pdfork() failed");
	case 0:
		ioctl_tests_1(fd);
		exit(0);
	default:
		if (pdwait(pfd) == -1)
			err(1, "pdwait() failed");
		close(pfd);
		ioctl_tests_1(fd);
	}
	CHECK(close(fd) == 0);

	/* Child inherits descriptor, but operates on it after parent. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = pdfork(&pfd, 0);
	switch (pid) {
	case -1:
		err(1, "pdfork() failed");
	case 0:
		sleep(1);
		ioctl_tests_1(fd);
		exit(0);
	default:
		ioctl_tests_1(fd);
		if (pdwait(pfd) == -1)
			err(1, "pdwait() failed");
		close(pfd);
	}
	CHECK(close(fd) == 0);

	/* Child inherits descriptor and operates on it first. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		ioctl_tests_2(fd);
		exit(0);
	default:
		if (waitpid(pid, NULL, 0) == -1)
			err(1, "waitpid() failed");
		ioctl_tests_2(fd);
	}
	CHECK(close(fd) == 0);

	/* Child inherits descriptor, but operates on it after parent. */
	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	pid = fork();
	switch (pid) {
	case -1:
		err(1, "fork() failed");
	case 0:
		sleep(1);
		ioctl_tests_2(fd);
		exit(0);
	default:
		ioctl_tests_2(fd);
		if (waitpid(pid, NULL, 0) == -1)
			err(1, "waitpid() failed");
	}
	CHECK(close(fd) == 0);

	/* Send descriptors from parent to child. */
	CHECK(socketpair(AF_UNIX, SOCK_STREAM, 0, sp) == 0);
	CHECK((pid = fork()) >= 0);
	if (pid == 0) {
		CHECK(close(sp[0]) == 0);
		ioctl_tests_recv_0(sp[1]);
		CHECK(close(sp[1]) == 0);
		exit(0);
	} else {
		CHECK(close(sp[1]) == 0);
		ioctl_tests_send_0(sp[0]);
		CHECK(waitpid(pid, NULL, 0) == pid);
		CHECK(close(sp[0]) == 0);
	}

	/* Send descriptors from child to parent. */
	CHECK(socketpair(AF_UNIX, SOCK_STREAM, 0, sp) == 0);
	CHECK((pid = fork()) >= 0);
	if (pid == 0) {
		CHECK(close(sp[0]) == 0);
		ioctl_tests_send_0(sp[1]);
		CHECK(close(sp[1]) == 0);
		exit(0);
	} else {
		CHECK(close(sp[1]) == 0);
		ioctl_tests_recv_0(sp[0]);
		CHECK(waitpid(pid, NULL, 0) == pid);
		CHECK(close(sp[0]) == 0);
	}

	exit(0);
}