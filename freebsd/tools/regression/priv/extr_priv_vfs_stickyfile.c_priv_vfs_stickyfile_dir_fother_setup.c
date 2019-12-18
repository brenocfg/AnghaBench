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
 int /*<<< orphan*/  UID_OTHER ; 
 int /*<<< orphan*/  dpath ; 
 int dpath_initialized ; 
 int /*<<< orphan*/  setup_dir (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
priv_vfs_stickyfile_dir_fother_setup(int asroot, int injail,
    struct test *test)
{

	setup_dir("priv_vfs_stickyfile_fother_setup: dpath", dpath,
	    UID_OTHER, GID_OTHER, 0700);
	dpath_initialized = 1;
	return (0);
}