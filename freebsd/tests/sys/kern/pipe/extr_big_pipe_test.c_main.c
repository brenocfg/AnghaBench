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
 int BIG_PIPE_SIZE ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*,...) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int fork () ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int read (int,char*,int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_frame (int,char*,int) ; 

int
main(void)
{
	/* any value over PIPE_SIZE should do */
	char buf[BIG_PIPE_SIZE];
	int i, flags, fd[2];

	if (pipe(fd) < 0)
		errx(1, "pipe failed");

	flags = fcntl(fd[1], F_GETFL);
	if (flags == -1 || fcntl(fd[1], F_SETFL, flags|O_NONBLOCK) == -1) {
		printf("fcntl failed: %s\n", strerror(errno));
		exit(1);
	}

	switch (fork()) {
	case -1:
		err(1, "fork failed: %s\n", strerror(errno));
		break;
	case 0:
		close(fd[1]);
		for (;;) {
			/* Any small size should do */
			i = read(fd[0], buf, 256);
			if (i == 0)
				break;
			if (i < 0)
				err(1, "read");
		}
		exit(0);
	default:
		break;
	}

	close(fd[0]);
	memset(buf, 0, sizeof buf);
	for (i = 0; i < 1000; i++)
		write_frame(fd[1], buf, sizeof buf);

	printf("ok\n");
	exit(0);
}