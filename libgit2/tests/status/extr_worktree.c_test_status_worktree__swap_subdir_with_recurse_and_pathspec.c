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
struct TYPE_7__ {int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  entry_count; int /*<<< orphan*/  expected_entry_count; int /*<<< orphan*/  expected_statuses; int /*<<< orphan*/  expected_paths; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  entry_count4 ; 
 int /*<<< orphan*/  entry_paths4 ; 
 int /*<<< orphan*/  entry_statuses4 ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_status_worktree__swap_subdir_with_recurse_and_pathspec(void)
{
	status_entry_counts counts;
	git_repository *repo = cl_git_sandbox_init("status");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;

	/* first alter the contents of the worktree */
	cl_git_pass(p_rename("status/current_file", "status/swap"));
	cl_git_pass(p_rename("status/subdir", "status/current_file"));
	cl_git_pass(p_rename("status/swap", "status/subdir"));
	cl_git_mkfile("status/.new_file", "dummy");
	cl_git_pass(git_futils_mkdir_r("status/zzz_new_dir", 0777));
	cl_git_mkfile("status/zzz_new_dir/new_file", "dummy");
	cl_git_mkfile("status/zzz_new_file", "dummy");

	/* now get status */
	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = entry_count4;
	counts.expected_paths = entry_paths4;
	counts.expected_statuses = entry_statuses4;

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;
	/* TODO: set pathspec to "current_file" eventually */

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}