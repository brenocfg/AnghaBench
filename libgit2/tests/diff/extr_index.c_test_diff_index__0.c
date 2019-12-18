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
struct TYPE_7__ {int context_lines; int interhunk_lines; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_8__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * resolve_commit_oid_to_tree (int /*<<< orphan*/ ,char const*) ; 

void test_diff_index__0(void)
{
	/* grabbed a couple of commit oids from the history of the attr repo */
	const char *a_commit = "26a125ee1bf"; /* the current HEAD */
	const char *b_commit = "0017bd4ab1ec3"; /* the start */
	git_tree *a = resolve_commit_oid_to_tree(g_repo, a_commit);
	git_tree *b = resolve_commit_oid_to_tree(g_repo, b_commit);
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;

	cl_assert(a);
	cl_assert(b);

	opts.context_lines = 1;
	opts.interhunk_lines = 1;

	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, a, NULL, &opts));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	/* to generate these values:
	 * - cd to tests/resources/status,
	 * - mv .gitted .git
	 * - git diff --name-status --cached 26a125ee1bf
	 * - git diff -U1 --cached 26a125ee1bf
	 * - mv .git .gitted
	 */
	cl_assert_equal_i(8, exp.files);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);

	cl_assert_equal_i(8, exp.hunks);

	cl_assert_equal_i(11, exp.lines);
	cl_assert_equal_i(3, exp.line_ctxt);
	cl_assert_equal_i(6, exp.line_adds);
	cl_assert_equal_i(2, exp.line_dels);

	git_diff_free(diff);
	diff = NULL;
	memset(&exp, 0, sizeof(exp));

	cl_git_pass(git_diff_tree_to_index(&diff, g_repo, b, NULL, &opts));

	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	/* to generate these values:
	 * - cd to tests/resources/status,
	 * - mv .gitted .git
	 * - git diff --name-status --cached 0017bd4ab1ec3
	 * - git diff -U1 --cached 0017bd4ab1ec3
	 * - mv .git .gitted
	 */
	cl_assert_equal_i(12, exp.files);
	cl_assert_equal_i(7, exp.file_status[GIT_DELTA_ADDED]);
	cl_assert_equal_i(2, exp.file_status[GIT_DELTA_DELETED]);
	cl_assert_equal_i(3, exp.file_status[GIT_DELTA_MODIFIED]);

	cl_assert_equal_i(12, exp.hunks);

	cl_assert_equal_i(16, exp.lines);
	cl_assert_equal_i(3, exp.line_ctxt);
	cl_assert_equal_i(11, exp.line_adds);
	cl_assert_equal_i(2, exp.line_dels);

	git_diff_free(diff);
	diff = NULL;

	git_tree_free(a);
	git_tree_free(b);
}