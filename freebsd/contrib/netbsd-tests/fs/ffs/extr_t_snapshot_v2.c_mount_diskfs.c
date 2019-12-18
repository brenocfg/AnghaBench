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
typedef  int /*<<< orphan*/  uargs ;
struct ufs_args {int /*<<< orphan*/  fspec; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_FFS ; 
 int /*<<< orphan*/  __UNCONST (char const*) ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*,char const*) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,struct ufs_args*,int) ; 

__attribute__((used)) static void
mount_diskfs(const char *fspec, const char *path)
{
	struct ufs_args uargs;

	uargs.fspec = __UNCONST(fspec);

	if (rump_sys_mount(MOUNT_FFS, path, 0, &uargs, sizeof(uargs)) == -1)
		atf_tc_fail_errno("mount ffs %s", path);
}