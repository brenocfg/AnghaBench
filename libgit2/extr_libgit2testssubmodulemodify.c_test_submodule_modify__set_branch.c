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
typedef  int /*<<< orphan*/  git_submodule ;

/* Variables and functions */
 int /*<<< orphan*/ * SM_LIBGIT2_BRANCH ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/ * git_submodule_branch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_submodule_set_branch (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

void test_submodule_modify__set_branch(void)
{
	git_submodule *sm;

	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_changed_head"));
	cl_assert(git_submodule_branch(sm) == NULL);
	git_submodule_free(sm);

	cl_git_pass(git_submodule_set_branch(g_repo, "sm_changed_head", SM_LIBGIT2_BRANCH));
	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_changed_head"));
	cl_assert_equal_s(SM_LIBGIT2_BRANCH, git_submodule_branch(sm));
	git_submodule_free(sm);

	cl_git_pass(git_submodule_set_branch(g_repo, "sm_changed_head", NULL));
	cl_git_pass(git_submodule_lookup(&sm, g_repo, "sm_changed_head"));
	cl_assert(git_submodule_branch(sm) == NULL);
	git_submodule_free(sm);
}