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
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int flopen (char const*,int,...) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

const char *
test_flopen_lock_self(void)
{
	const char *fn = "test_flopen_lock_self";
	const char *result = NULL;
	int fd1, fd2;

	unlink(fn);
	fd1 = flopen(fn, O_RDWR|O_CREAT, 0640);
	if (fd1 < 0) {
		result = strerror(errno);
	} else {
		fd2 = flopen(fn, O_RDWR|O_NONBLOCK);
		if (fd2 >= 0) {
			result = "second open succeeded";
			close(fd2);
		}
		close(fd1);
	}
	unlink(fn);
	return (result);
}