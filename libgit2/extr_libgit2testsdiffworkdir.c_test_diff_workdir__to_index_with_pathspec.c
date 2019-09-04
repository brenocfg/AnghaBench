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
struct TYPE_10__ {int context_lines; int interhunk_lines; int flags; TYPE_1__ pathspec; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_11__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_3__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_ADDED ; 
 size_t GIT_DELTA_DELETED ; 
 size_t GIT_DELTA_IGNORED ; 
 size_t GIT_DELTA_MODIFIED ; 
 size_t GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_foreach_via_iterator (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__to_index_with_pathspec(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;
	char *pathspec = NULL;
	int use_iterator;

	g_repo = cl_git_sandbox_init("status");

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;
	opts.pathspec.strings = &pathspec;
	opts.pathspec.count   = 1;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, NULL, NULL, NULL, &exp));
		else
			cl_git_pass(git_diff_foreach(diff, diff_file_cb, NULL, NULL, NULL, &exp));

		cl_assert_equal_i(13, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(4, exp.file_status[GIT_DELTA_UNTRACKED]);
	}

	git_diff_free(diff);

	pathspec = "modified_file";

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, NULL, NULL, NULL, &exp));
		else
			cl_git_pass(git_diff_foreach(diff, diff_file_cb, NULL, NULL, NULL, &exp));

		cl_assert_equal_i(1, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_UNTRACKED]);
	}

	git_diff_free(diff);

	pathspec = "subdir";

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, NULL, NULL, NULL, &exp));
		else
			cl_git_pass(git_diff_foreach(diff, diff_file_cb, NULL, NULL, NULL, &exp));

		cl_assert_equal_i(3, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNTRACKED]);
	}

	git_diff_free(diff);

	pathspec = "*_deleted";

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	for (use_iterator = 0; use_iterator <= 1; use_iterator++) {
		memset(&exp, 0, sizeof(exp));

		if (use_iterator)
			cl_git_pass(diff_foreach_via_iterator(
				diff, diff_file_cb, NULL, NULL, NULL, &exp));
		else
			cl_git_pass(git_diff_foreach(diff, diff_file_cb, NULL, NULL, NULL, &exp));

		cl_assert_equal_i(2, exp.files);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_ADDED]);
		cl_assert_equal_i(2, exp.file_status[GIT_DELTA_DELETED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_MODIFIED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_IGNORED]);
		cl_assert_equal_i(0, exp.file_status[GIT_DELTA_UNTRACKED]);
	}

	git_diff_free(diff);
}