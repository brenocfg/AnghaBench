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
 int /*<<< orphan*/  fpath ; 
 int fpath_initialized ; 
 int /*<<< orphan*/  setup_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
priv_vfs_utimes_fother_setup(int asroot, int injail, struct test *test)
{

	/*
	 * In the 'other' case, we make the file writable by the test user so
	 * we can evaluate the difference between setting the time to NULL,
	 * which is possible as a writer, and non-NULL, which requires
	 * ownership.
	 */
	setup_file("priv_vfs_utimes_fother_setup: fpath", fpath,
	    UID_OTHER, GID_OTHER, 0666);
	fpath_initialized = 1;
	return (0);
}