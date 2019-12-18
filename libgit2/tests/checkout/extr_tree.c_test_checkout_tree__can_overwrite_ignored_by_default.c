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
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  checkout_tree_with_blob_ignored_in_workdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_overwrite_ignored_by_default(void)
{
	cl_git_pass(checkout_tree_with_blob_ignored_in_workdir(GIT_CHECKOUT_SAFE, false));

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/subtrees"));

	cl_assert(git_path_isfile("testrepo/ab/4.txt"));

	assert_on_branch(g_repo, "subtrees");
}