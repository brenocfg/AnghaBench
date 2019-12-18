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
struct ffstestargs {int /*<<< orphan*/  ta_uargs; } ;
typedef  int /*<<< orphan*/  atf_tc_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_FFS ; 
 int rump_sys_mkdir (char const*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 

int
ffs_fstest_mount(const atf_tc_t *tc, void *buf, const char *path, int flags)
{
	int res;
	struct ffstestargs *args = buf;

	res = rump_sys_mkdir(path, 0777);
	if (res == -1)
		return res;

	res = rump_sys_mount(MOUNT_FFS, path, flags, &args->ta_uargs,
	    sizeof(args->ta_uargs));
	return res;
}