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
 int /*<<< orphan*/  check_file_contents (char*,char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 scalar_t__ git_path_supports_symlinks (char*) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  populate_symlink_workdir () ; 

void test_checkout_index__honor_coresymlinks_default_false(void)
{
	cl_must_pass(p_mkdir("symlink", 0777));

#ifndef GIT_WIN32
	/*
	 * This test is largely for Windows platforms to ensure that
	 * we respect an unset core.symlinks even when the platform
	 * supports symlinks.  Bail entirely on POSIX platforms that
	 * do support symlinks.
	 */
	if (git_path_supports_symlinks("symlink/test"))
		cl_skip();
#endif

	populate_symlink_workdir();
	check_file_contents("./symlink/link_to_new.txt", "new.txt");
}