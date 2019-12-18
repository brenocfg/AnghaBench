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
 int /*<<< orphan*/  dpath ; 
 scalar_t__ dpath_initialized ; 
 int /*<<< orphan*/  rmdir (int /*<<< orphan*/ ) ; 

void
priv_vfs_stickyfile_dir_cleanup(int asroot, int injail, struct test *test)
{

	if (dpath_initialized) {
		(void)rmdir(dpath);
		dpath_initialized = 0;
	}
}