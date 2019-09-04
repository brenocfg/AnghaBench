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
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_7__ {int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  exp ;
struct TYPE_8__ {int /*<<< orphan*/ * file_status; int /*<<< orphan*/  files; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 size_t GIT_DELTA_IGNORED ; 
 size_t GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_binary_cb ; 
 int /*<<< orphan*/  diff_file_cb ; 
 int /*<<< orphan*/  diff_hunk_cb ; 
 int /*<<< orphan*/  diff_line_cb ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void test_diff_submodules__skips_empty_includes_used(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp;

	/* A side effect of of Git's handling of untracked directories and
	 * auto-ignoring of ".git" entries is that a newly initialized Git
	 * repo inside another repo will be skipped by diff, but one that
	 * actually has a commit it in will show as an untracked directory.
	 * Let's make sure that works.
	 */

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(0, exp.files);
	git_diff_free(diff);

	{
		git_repository *r2;
		cl_git_pass(git_repository_init(&r2, "empty_standard_repo/subrepo", 0));
		git_repository_free(r2);
	}

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(1, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_IGNORED]);
	git_diff_free(diff);

	cl_git_mkfile("empty_standard_repo/subrepo/README.txt", "hello\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));
	memset(&exp, 0, sizeof(exp));
	cl_git_pass(git_diff_foreach(
		diff, diff_file_cb, diff_binary_cb, diff_hunk_cb, diff_line_cb, &exp));
	cl_assert_equal_i(1, exp.files);
	cl_assert_equal_i(1, exp.file_status[GIT_DELTA_UNTRACKED]);
	git_diff_free(diff);
}