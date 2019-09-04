#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_4__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_CONFLICTED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_index__to_index(void)
{
	const char *a_commit = "26a125ee1bf"; /* the current HEAD */
	git_tree *old_tree;
	git_index *old_index;
	git_index *new_index;
	git_diff *diff;
	diff_expects exp;

	cl_git_pass(git_index_new(&old_index));
	old_tree = resolve_commit_oid_to_tree(g_repo, a_commit);
	cl_git_pass(git_index_read_tree(old_index, old_tree));

	cl_git_pass(git_repository_index(&new_index, g_repo));

	cl_git_pass(git_diff_index_to_index(&diff, g_repo, old_index, new_index, NULL));

	memset(&exp, 0, sizeof(diff_expects));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(8, exp.files);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_CONFLICTED]);

	git_diff_free(diff);
	git_index_free(new_index);
	git_index_free(old_index);
	git_tree_free(old_tree);
}