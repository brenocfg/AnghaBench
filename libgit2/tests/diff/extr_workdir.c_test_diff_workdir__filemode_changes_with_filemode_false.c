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
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_4__ {int /*<<< orphan*/  hunks; int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_MODIFIED ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_toggle_filemode (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_diff_workdir__filemode_changes_with_filemode_false(void)
{
	git_diff *diff = NULL;
	diff_expects exp;

	if (!cl_is_chmod_supported())
		return;

	g_repo = cl_git_sandbox_init("issue_592");

	cl_repo_set_bool(g_repo, "core.filemode", false);

	/* test once with no mods */

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, NULL));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(0, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(0, exp.hunks);

	git_diff_free(diff);

	/* chmod file and test again */

	cl_assert(cl_toggle_filemode("issue_592/a.txt"));

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, NULL));

	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(diff,
		diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));

	cl_assert_equal_i(0, exp.files);
	cl_assert_equal_i(0, exp.file_status[GIT_DELTA_MODIFIED]);
	cl_assert_equal_i(0, exp.hunks);

	git_diff_free(diff);

	cl_assert(cl_toggle_filemode("issue_592/a.txt"));
}