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
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int rump_sys_rmdir (char const*) ; 
 int rump_sys_unmount (char const*,int) ; 

int
udf_fstest_unmount(const atf_tc_t *tc, const char *path, int flags)
{
	int res;

	res = rump_sys_unmount(path, flags);
	if (res == -1)
		return res;

	res = rump_sys_rmdir(path);
	return res;
}