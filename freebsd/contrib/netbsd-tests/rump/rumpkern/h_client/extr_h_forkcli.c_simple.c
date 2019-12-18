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
struct rumpclient_fork {int dummy; } ;
typedef  int pid_t ;
typedef  int /*<<< orphan*/  fd ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  WEXITSTATUS (int) ; 
 int /*<<< orphan*/  WIFEXITED (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*,...) ; 
 int fork () ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_getpid () ; 
 int rump_sys_open (char*,int) ; 
 int rump_sys_write (int,int*,int) ; 
 int rumpclient_fork_init (struct rumpclient_fork*) ; 
 struct rumpclient_fork* rumpclient_prefork () ; 
 int wait (int*) ; 

__attribute__((used)) static void
simple(void)
{
	struct rumpclient_fork *rf;
	pid_t pid1, pid2;
	int fd, status;

	if ((pid1 = rump_sys_getpid()) < 2)
		errx(1, "unexpected pid %d", pid1);

	fd = rump_sys_open("/dev/null", O_CREAT | O_RDWR);
	if (rump_sys_write(fd, &fd, sizeof(fd)) != sizeof(fd))
		errx(1, "write newlyopened /dev/null");

	if ((rf = rumpclient_prefork()) == NULL)
		err(1, "prefork");

	switch (fork()) {
	case -1:
		err(1, "fork");
		break;
	case 0:
		if (rumpclient_fork_init(rf) == -1)
			err(1, "postfork init failed");

		if ((pid2 = rump_sys_getpid()) < 2)
			errx(1, "unexpected pid %d", pid2);
		if (pid1 == pid2)
			errx(1, "child and parent pids are equal");

		/* check that we can access the fd, the close it and exit */
		if (rump_sys_write(fd, &fd, sizeof(fd)) != sizeof(fd))
			errx(1, "write child /dev/null");
		rump_sys_close(fd);
		break;
	default:
		/*
		 * check that we can access the fd, wait for the child, and
		 * check we can still access the fd
		 */
		if (rump_sys_write(fd, &fd, sizeof(fd)) != sizeof(fd))
			errx(1, "write parent /dev/null");
		if (wait(&status) == -1)
			err(1, "wait failed");
		if (!WIFEXITED(status) || WEXITSTATUS(status) != 0)
			errx(1, "child exited with status %d", status);
		if (rump_sys_write(fd, &fd, sizeof(fd)) != sizeof(fd))
			errx(1, "write parent /dev/null");
		break;
	}
}