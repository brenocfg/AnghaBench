#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {char** strings; int count; } ;
struct TYPE_10__ {TYPE_1__ pathspec; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_11__ {int /*<<< orphan*/  line_dels; int /*<<< orphan*/  line_adds; int /*<<< orphan*/  line_ctxt; int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_MODIFIED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_foreach_via_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__eof_newline_changes(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;
	char *pathspec = "current_file";
	int use_iterator;

	g_repo = cl_git_sandbox_init("status");

	opts.pathspec.strings = &pathspec;
	opts.pathspec.count   = 1;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(0, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(0, exp.hunks);
		cl_assert_equal_i(0, exp.lines);
		cl_assert_equal_i(0, exp.line_ctxt);
		cl_assert_equal_i(0, exp.line_adds);
		cl_assert_equal_i(0, exp.line_dels);
	}

	git_diff_free(diff);

	cl_git_append2file("status/current_file", "\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(1, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.hunks);
		cl_assert_equal_i(2, exp.lines);
		cl_assert_equal_i(1, exp.line_ctxt);
		cl_assert_equal_i(1, exp.line_adds);
		cl_assert_equal_i(0, exp.line_dels);
	}

	git_diff_free(diff);

	cl_git_rewritefile("status/current_file", "current_file");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
		else
			cl_git_pass(git_diff_foreach(
				diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

		cl_assert_equal_i(1, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.hunks);
		cl_assert_equal_i(3, exp.lines);
		cl_assert_equal_i(0, exp.line_ctxt);
		cl_assert_equal_i(1, exp.line_adds);
		cl_assert_equal_i(2, exp.line_dels);
	}

	git_diff_free(diff);
}