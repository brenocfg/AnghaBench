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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_EBAREREPO ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

void test_diff_workdir__cannot_diff_against_a_bare_repository(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_tree *tree;

	g_repo = cl_git_sandbox_init("testrepo.git");

	cl_assert_equal_i(
		GIT_EBAREREPO, git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	cl_git_pass(git_repository_head_tree(&tree, g_repo));

	cl_assert_equal_i(
		GIT_EBAREREPO, git_diff_tree_to_workdir(&diff, g_repo, tree, &opts));

	git_tree_free(tree);
}