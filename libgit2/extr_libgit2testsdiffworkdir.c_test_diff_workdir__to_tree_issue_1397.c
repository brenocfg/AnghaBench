#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {int context_lines; int interhunk_lines; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_10__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_tree_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_workdir__to_tree_issue_1397(void)
{
	const char *a_commit = "7f483a738"; /* the current HEAD */
	git_tree *a;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_diff *diff2 = NULL;
	diff_expects exp;

	g_repo = cl_git_sandbox_init("issue_1397");

	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	a = resolve_commit_oid_to_tree(g_repo, a_commit);

	opts.context_lines = 3;
	opts.interhunk_lines = 1;

	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, a, &opts));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(0, exp.files);
	cl_assert_equal_i(0, exp.hunks);
	cl_assert_equal_i(0, exp.lines);

	git_diff_free(diff);
	diff = NULL;

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, a, NULL, &opts));
	cl_git_pass(git_diff_index_to_workdir(&diff2, g_repo, NULL, &opts));
	cl_git_pass(git_diff_merge(diff, diff2));
	git_diff_free(diff2);

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(0, exp.files);
	cl_assert_equal_i(0, exp.hunks);
	cl_assert_equal_i(0, exp.lines);

	git_diff_free(diff);
	git_tree_free(a);
}