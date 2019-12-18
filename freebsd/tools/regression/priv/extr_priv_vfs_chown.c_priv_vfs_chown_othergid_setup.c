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
 int /*<<< orphan*/  GID_OWNER ; 
 int /*<<< orphan*/  GID_WHEEL ; 
 int /*<<< orphan*/  UID_OWNER ; 
 int /*<<< orphan*/  UID_ROOT ; 
 int /*<<< orphan*/  fpath ; 
 int fpath_initialized ; 
 int /*<<< orphan*/  setup_file (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
priv_vfs_chown_othergid_setup(int asroot, int injail, struct test *test)
{

	/*
	 * Create a file with a matching uid to the test process with a
	 * matching gid.
	 */
	setup_file("priv_vfs_chown_othergid: fpath", fpath, asroot ? UID_ROOT
	    : UID_OWNER, asroot ? GID_WHEEL : GID_OWNER, 0600);
	fpath_initialized = 1;
	return (0);
}