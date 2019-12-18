#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_10__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_11__ {int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_IGNORED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_foreach_via_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
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

void test_diff_workdir__to_tree(void)
{
	/* grabbed a couple of commit oids from the history of the attr repo */
	const char *a_commit = "26a125ee1bf"; /* the current HEAD */
	const char *b_commit = "0017bd4ab1ec3"; /* the start */
	git_tree *a, *b;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_diff *diff2 = NULL;
	diff_expects exp;
	int use_iterator;

	g_repo = cl_git_sandbox_init("status");

	a = resolve_commit_oid_to_tree(g_repo, a_commit);
	b = resolve_commit_oid_to_tree(g_repo, b_commit);

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	/* You can't really generate the equivalent of git_diff_tree_to_workdir()
	 * using C git.  It really wants to interpose the index into the diff.
	 *
	 * To validate the following results with command line git, I ran the
	 * following:
	 * - git ls-tree 26a125
	 * - find . ! -path ./.git/\* -a -type f | git hash-object --stdin-paths
	 * The results are documented at the bottom of this file in the
	 * long comment entitled "PREPARATION OF TEST DATA".
	 */
	cl_git_pass(git_diff_tree_to_workdir(&diff, g_repo, a, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(14, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(5, exp.file_status[GIT_DELTA_UNTRACKED]);
	}

	/* Since there is no git diff equivalent, let's just assume that the
	 * text diffs produced by git_diff_foreach are accurate here.  We will
	 * do more apples-to-apples test comparison below.
	 */

	git_diff_free(diff);
	diff = NULL;
	memset(&exp, 0, sizeof(exp));

	/* This is a compatible emulation of "git diff <sha>" which looks like
	 * a workdir to tree diff (even though it is not really).  This is what
	 * you would get from "git diff --name-status 26a125ee1bf"
	 */
	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, a, NULL, &opts));
	cl_git_pass(git_diff_index_to_workdir(&diff2, g_repo, NULL, &opts));
	cl_git_pass(git_diff_merge(diff, diff2));
	git_diff_free(diff2);

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(15, exp.files);
		cl_assert_equal_i(2, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(5, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(3, exp.file_status[GIT_DELTA_UNTRACKED]);

		cl_assert_equal_i(11, exp.hunks);

		cl_assert_equal_i(17, exp.lines);
		cl_assert_equal_i(4, exp.line_ctxt);
		cl_assert_equal_i(8, exp.line_adds);
		cl_assert_equal_i(5, exp.line_dels);
	}

	git_diff_free(diff);
	diff = NULL;
	memset(&exp, 0, sizeof(exp));

	/* Again, emulating "git diff <sha>" for testing purposes using
	 * "git diff --name-status 0017bd4ab1ec3" instead.
	 */
	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, b, NULL, &opts));
	cl_git_pass(git_diff_index_to_workdir(&diff2, g_repo, NULL, &opts));
	cl_git_pass(git_diff_merge(diff, diff2));
	git_diff_free(diff2);

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(16, exp.files);
		cl_assert_equal_i(5, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(3, exp.file_status[GIT_DELTA_UNTRACKED]);

		cl_assert_equal_i(12, exp.hunks);

		cl_assert_equal_i(19, exp.lines);
		cl_assert_equal_i(3, exp.line_ctxt);
		cl_assert_equal_i(12, exp.line_adds);
		cl_assert_equal_i(4, exp.line_dels);
	}

	git_diff_free(diff);

	/* Let's try that once more with a reversed diff */

	opts.flags |= GIT_DIFF_REVERSE;

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, b, NULL, &opts));
	cl_git_pass(git_diff_index_to_workdir(&diff2, g_repo, NULL, &opts));
	cl_git_pass(git_diff_merge(diff, diff2));
	git_diff_free(diff2);

	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(16, exp.files);
	cl_assert_equal_i(5, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(4, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_UNTRACKED]);

	cl_assert_equal_i(12, exp.hunks);

	cl_assert_equal_i(19, exp.lines);
	cl_assert_equal_i(3, exp.line_ctxt);
	cl_assert_equal_i(12, exp.line_dels);
	cl_assert_equal_i(4, exp.line_adds);

	git_diff_free(diff);

	/* all done now */

	git_tree_free(a);
	git_tree_free(b);
}