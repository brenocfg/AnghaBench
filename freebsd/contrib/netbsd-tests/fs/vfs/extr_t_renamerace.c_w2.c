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
 int /*<<< orphan*/  quittingtime ; 
 int /*<<< orphan*/  rump_pub_lwproc_newlwp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rump_sys_rename (char*,char*) ; 
 int /*<<< orphan*/  wrkpid ; 

__attribute__((used)) static void *
w2(void *arg)
{

	rump_pub_lwproc_newlwp(wrkpid);

	while (!quittingtime) {
		rump_sys_rename("rename.test1", "rename.test2");
	}

	return NULL;
}