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
 unsigned int GIT_SUBMODULE_STATUS_WD_MODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_submodule_status (unsigned int*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

void test_index_bypath__add_submodule(void)
{
	unsigned int status;
	const char *sm_name = "sm_changed_head";

	cl_git_pass(git_submodule_status(&status, g_repo, sm_name, 0));
	cl_assert_equal_i(GIT_SUBMODULE_STATUS_WD_MODIFIED, status & GIT_SUBMODULE_STATUS_WD_MODIFIED);
	cl_git_pass(git_index_add_bypath(g_idx, sm_name));
	cl_git_pass(git_submodule_status(&status, g_repo, sm_name, 0));
	cl_assert_equal_i(0, status & GIT_SUBMODULE_STATUS_WD_MODIFIED);
}