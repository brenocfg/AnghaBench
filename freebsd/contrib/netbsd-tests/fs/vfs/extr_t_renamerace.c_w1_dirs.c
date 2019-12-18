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
 int /*<<< orphan*/  atf_tc_fail_errno (char*) ; 
 int /*<<< orphan*/  quittingtime ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int /*<<< orphan*/ ) ; 
 int rump_sys_mkdir (char*,int) ; 
 int /*<<< orphan*/  rump_sys_rmdir (char*) ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void *
w1_dirs(void *arg)
{

	rump_pub_lwproc_newlwp(wrkpid);

	while (!quittingtime) {
		if (rump_sys_mkdir("rename.test1", 0777) == -1)
			atf_tc_fail_errno("mkdir");
		rump_sys_rmdir("rename.test1");
	}

	return NULL;
}