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
 int /*<<< orphan*/  GID_OTHER ; 
 int /*<<< orphan*/  UID_OWNER ; 
 int /*<<< orphan*/  fpath ; 
 int fpath_initialized ; 
 int /*<<< orphan*/  setup_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
priv_vfs_setgid_fother_setup(int asroot, int injail, struct test *test)
{

	/* NOTE: owner uid, *other* gid. */
	setup_file("priv_vfs_setgid_forther: fpath", fpath, UID_OWNER,
	    GID_OTHER, 0600);
	fpath_initialized = 1;
	return (0);
}