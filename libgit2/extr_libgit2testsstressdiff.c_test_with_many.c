#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_7__ {void* flags; } ;
typedef  TYPE_1__ git_diff_find_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_8__ {int /*<<< orphan*/  files; int /*<<< orphan*/ * file_status; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_RENAMED ; 
 void* GIT_DIFF_FIND_ALL ; 
 TYPE_1__ GIT_DIFF_FIND_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

__attribute__((used)) static void test_with_many(int expected_new)
{
	git_index *index;
	git_tree *tree, *new_tree;
	git_diff *diff = NULL;
	diff_expects exp;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	git_diff_find_options opts = GIT_DIFF_FIND_OPTIONS_INIT;

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(
		git_revparse_single((git_object **)&tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(p_rename("renames/ikeepsix.txt", "renames/ikeepsix2.txt"));
	cl_git_pass(git_index_remove_bypath(index, "ikeepsix.txt"));
	cl_git_pass(git_index_add_bypath(index, "ikeepsix2.txt"));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, tree, index, &diffopts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, NULL, NULL, NULL, &exp));
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(expected_new + 1, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(expected_new + 2, exp.files);

	opts.flags = GIT_DIFF_FIND_ALL;
	cl_git_pass(git_diff_find_similar(diff, &opts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, NULL, NULL, NULL, &exp));
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_RENAMED]);
	cl_assert_equal_i(expected_new, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(expected_new + 1, exp.files);

	git_diff_free(diff);

	cl_repo_commit_from_index(NULL, g_repo, NULL, 1372350000, "yoyoyo");
	cl_git_pass(git_revparse_single(
		(git_object **)&new_tree, g_repo, "HEAD^{tree}"));

	cl_git_pass(git_diff_tree_to_tree(
		&diff, g_repo, tree, new_tree, &diffopts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, NULL, NULL, NULL, &exp));
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(expected_new + 1, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(expected_new + 2, exp.files);

	opts.flags = GIT_DIFF_FIND_ALL;
	cl_git_pass(git_diff_find_similar(diff, &opts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, NULL, NULL, NULL, &exp));
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_RENAMED]);
	cl_assert_equal_i(expected_new, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(expected_new + 1, exp.files);

	git_diff_free(diff);

	git_tree_free(new_tree);
	git_tree_free(tree);
	git_index_free(index);
}