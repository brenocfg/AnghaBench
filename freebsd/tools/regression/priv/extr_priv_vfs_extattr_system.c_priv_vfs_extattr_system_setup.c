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
struct test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  fpath ; 
 int fpath_initialized ; 
 int /*<<< orphan*/  setup_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
priv_vfs_extattr_system_setup(int asroot, int injail, struct test *test)
{

	/*
	 * Set file perms so that discretionary access control would grant
	 * write rights on non-system EAs on the file.
	 */
	setup_file("priv_vfs_extattr_system_setup: fpath", fpath, UID_ROOT,
	    GID_WHEEL, 0666);
	fpath_initialized = 1;
	return (0);
}