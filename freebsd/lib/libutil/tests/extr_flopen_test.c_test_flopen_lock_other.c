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
 int O_CREAT ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int volatile) ; 
 int /*<<< orphan*/  errno ; 
 int flopen (char const*,int,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 
 scalar_t__ vfork () ; 

const char *
test_flopen_lock_other(void)
{
	const char *fn = "test_flopen_lock_other";
	const char *result = NULL;
	volatile int fd1, fd2;

	unlink(fn);
	fd1 = flopen(fn, O_RDWR|O_CREAT, 0640);
	if (fd1 < 0) {
		result = strerror(errno);
	} else {
		fd2 = -42;
		if (vfork() == 0) {
			fd2 = flopen(fn, O_RDWR|O_NONBLOCK);
			close(fd2);
			_exit(0);
		}
		if (fd2 == -42)
			result = "vfork() doesn't work as expected";
		if (fd2 >= 0)
			result = "second open succeeded";
		close(fd1);
	}
	unlink(fn);
	return (result);
}