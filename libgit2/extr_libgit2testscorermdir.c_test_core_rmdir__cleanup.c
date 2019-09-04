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
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_tmp_dir ; 
 int /*<<< orphan*/  git_futils_rmdir_r (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ git_path_exists (int /*<<< orphan*/ ) ; 

void test_core_rmdir__cleanup(void)
{
	if (git_path_exists(empty_tmp_dir))
		cl_git_pass(git_futils_rmdir_r(empty_tmp_dir, NULL, GIT_RMDIR_REMOVE_FILES));
}