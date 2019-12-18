#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DELTA_UNTRACKED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_DIFF_SHOW_UNTRACKED_CONTENT ; 
 int O_CREAT ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_git_write2file (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_diff_get_delta (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_num_deltas (int /*<<< orphan*/ *) ; 

void test_diff_workdir__untracked_with_bom(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	const git_diff_delta *delta;

	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	cl_git_write2file("empty_standard_repo/bom.txt",
		"\xFF\xFE\x31\x00\x32\x00\x33\x00\x34\x00", 10, O_WRONLY|O_CREAT, 0664);

	opts.flags =
		GIT_DIFF_INCLUDE_UNTRACKED | GIT_DIFF_SHOW_UNTRACKED_CONTENT;

	cl_git_pass(git_diff_index_to_workdir(&diff, g_repo, NULL, &opts));

	cl_assert_equal_i(1, git_diff_num_deltas(diff));
	cl_assert((delta = git_diff_get_delta(diff, 0)) != NULL);
	cl_assert_equal_i(GIT_DELTA_UNTRACKED, delta->status);

	/* not known at this point
	 * cl_assert((delta->flags & GIT_DIFF_FLAG_BINARY) != 0);
	 */

	git_diff_free(diff);
}