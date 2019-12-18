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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int O_CREAT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TEST_NONROOT_ID ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  rump_sys_chmod (char*,int) ; 
 int /*<<< orphan*/  rump_sys_chown (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int,int) ; 
 scalar_t__ rump_sys_setegid (int /*<<< orphan*/ ) ; 
 scalar_t__ rump_sys_seteuid (int /*<<< orphan*/ ) ; 
 int rump_sys_write (int,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
quota_test1(const char *testopts)
{
	static char buf[512];
	int fd;
	int error;
	rump_sys_chown(".", TEST_NONROOT_ID, TEST_NONROOT_ID);
	rump_sys_chmod(".", 0777);
	if (rump_sys_setegid(TEST_NONROOT_ID) != 0) {
		error = errno;
		warn("rump_sys_setegid");
		return error;
	}
	if (rump_sys_seteuid(TEST_NONROOT_ID) != 0) {
		error = errno;
		warn("rump_sys_seteuid");
		return error;
	}
	fd = rump_sys_open("test_fillup", O_CREAT | O_RDWR, 0644);
	if (fd < 0) {
		error = errno;
		warn("rump_sys_open");
	} else {
		/*
		 * write up to the soft limit, wait a bit, an try to
		 * keep on writing
		 */
		int i;

		/* write 2k: with the directory this makes 2.5K */
		for (i = 0; i < 4; i++) {
			error = rump_sys_write(fd, buf, sizeof(buf));
			if (error != sizeof(buf))
				err(1, "write failed early");
		}
		sleep(2);
		/* now try to write an extra .5k */
		if (rump_sys_write(fd, buf, sizeof(buf)) != sizeof(buf))
			error = errno;
		else
			error = 0;
	}
	rump_sys_close(fd);
	rump_sys_seteuid(0);
	rump_sys_setegid(0);
	return error;
}