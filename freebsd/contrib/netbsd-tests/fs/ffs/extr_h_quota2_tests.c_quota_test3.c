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
 int O_EXCL ; 
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
 int /*<<< orphan*/  rump_sys_write (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
quota_test3(const char *testopts)
{
	static char buf[512];
	int fd;
	int error;
	int i;
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

	/*
	 * create files one past the soft limit: one less as we already own the
	 * root directory
	 */
	for (i = 0; i < 4; i++) {
		sprintf(buf, "file%d", i);
		fd = rump_sys_open(buf, O_EXCL| O_CREAT | O_RDWR, 0644);
		if (fd < 0)
			err(1, "file create failed early");
		sprintf(buf, "test file no %d", i);
		rump_sys_write(fd, buf, strlen(buf));
		rump_sys_close(fd);
	}
	/* now create an extra file after grace time: this should fail */
	sleep(2);
	sprintf(buf, "file%d", i);
	fd = rump_sys_open(buf, O_EXCL| O_CREAT | O_RDWR, 0644);
	if (fd < 0)
		error = errno;
	else
		error = 0;
	
	rump_sys_close(fd);
	rump_sys_seteuid(0);
	rump_sys_setegid(0);
	return error;
}