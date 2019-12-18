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
 int /*<<< orphan*/  MOUNT_KERNFS ; 
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  rump_init () ; 
 int rump_sys_mkdir (char*,int) ; 
 int rump_sys_mount (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mountkernfs(void)
{

	rump_init();

	if (rump_sys_mkdir("/kern", 0777) == -1)
		atf_tc_fail_errno("mkdir /kern");
	if (rump_sys_mount(MOUNT_KERNFS, "/kern", 0, NULL, 0) == -1)
		atf_tc_fail_errno("could not mount kernfs");
}