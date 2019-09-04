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
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_object ; 
 int /*<<< orphan*/  g_opts ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_path_isfile (char*) ; 
 int /*<<< orphan*/  git_repository_set_head (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_checkout_tree__can_checkout_and_remove_directory(void)
{
	cl_assert_equal_i(false, git_path_isdir("./testrepo/ab/"));

	/* Checkout brach "subtrees" and update HEAD, so that HEAD matches the
	 * current working tree
	 */
	cl_git_pass(git_revparse_single(&g_object, g_repo, "subtrees"));
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/subtrees"));

	cl_assert_equal_i(true, git_path_isdir("./testrepo/ab/"));
	cl_assert_equal_i(true, git_path_isfile("./testrepo/ab/de/2.txt"));
	cl_assert_equal_i(true, git_path_isfile("./testrepo/ab/de/fgh/1.txt"));

	git_object_free(g_object);
	g_object = NULL;

	/* Checkout brach "master" and update HEAD, so that HEAD matches the
	 * current working tree
	 */
	cl_git_pass(git_revparse_single(&g_object, g_repo, "master"));
	cl_git_pass(git_checkout_tree(g_repo, g_object, &g_opts));

	cl_git_pass(git_repository_set_head(g_repo, "refs/heads/master"));

	/* This directory should no longer exist */
	cl_assert_equal_i(false, git_path_isdir("./testrepo/ab/"));
}