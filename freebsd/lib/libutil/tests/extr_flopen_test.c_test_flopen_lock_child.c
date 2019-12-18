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
 int O_CREAT ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int volatile) ; 
 int /*<<< orphan*/  errno ; 
 int flopen (char const*,int,...) ; 
 int fork () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  select (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

const char *
test_flopen_lock_child(void)
{
	const char *fn = "test_flopen_lock_child";
	const char *result = NULL;
	pid_t pid;
	volatile int fd1, fd2;

	unlink(fn);
	fd1 = flopen(fn, O_RDWR|O_CREAT, 0640);
	if (fd1 < 0) {
		result = strerror(errno);
	} else {
		pid = fork();
		if (pid == -1) {
			result = strerror(errno);
		} else if (pid == 0) {
			select(0, 0, 0, 0, 0);
			_exit(0);
		}
		close(fd1);
		if ((fd2 = flopen(fn, O_RDWR|O_NONBLOCK)) != -1) {
			result = "second open succeeded";
			close(fd2);
		}
		kill(pid, SIGINT);
	}
	unlink(fn);
	return (result);
}