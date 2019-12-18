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
 int O_RDWR ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*,char const*) ; 
 int /*<<< orphan*/  rump_sys_close (int) ; 
 int rump_sys_open (char const*,int,int) ; 

__attribute__((used)) static void
xtouch(const char *path)
{
	int fd;

	fd = rump_sys_open(path, O_CREAT | O_RDWR, 0777);
	if (fd == -1)
		atf_tc_fail_errno("create %s", path);
	rump_sys_close(fd);
}