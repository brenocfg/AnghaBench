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
typedef  int /*<<< orphan*/  targs ;
struct tmpfs_args {int /*<<< orphan*/  ta_version; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOUNT_TMPFS ; 
 int /*<<< orphan*/  TMPFS_ARGS_VERSION ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct tmpfs_args*,int) ; 

__attribute__((used)) static void
begin(void)
{
	struct tmpfs_args targs = { .ta_version = TMPFS_ARGS_VERSION, };

	if (rump_sys_mkdir("/stor", 0777) == -1)
		atf_tc_fail_errno("mkdir /stor");
	if (rump_sys_mount(MOUNT_TMPFS, "/stor", 0, &targs,sizeof(targs)) == -1)
		atf_tc_fail_errno("mount storage");
}