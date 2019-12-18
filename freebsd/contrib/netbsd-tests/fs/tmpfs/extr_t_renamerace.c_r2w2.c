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
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  quittingtime ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void *
r2w2(void *arg)
{
	int fd;

	rump_pub_lwproc_newlwp(wrkpid);

	while (!quittingtime) {
		fd = rump_sys_open("/dir/file1", O_RDWR);
		if (fd != -1)
			rump_sys_close(fd);
	}

	return NULL;
}