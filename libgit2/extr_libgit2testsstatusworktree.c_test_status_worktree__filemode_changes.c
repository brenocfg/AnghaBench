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
struct TYPE_7__ {int expected_entry_count; scalar_t__* expected_statuses; int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  entry_count; int /*<<< orphan*/  expected_paths; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_8__ {int flags; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  counts ;

/* Variables and functions */
 scalar_t__ GIT_STATUS_CURRENT ; 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_IGNORED ; 
 int GIT_STATUS_OPT_INCLUDE_UNMODIFIED ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 scalar_t__ GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 scalar_t__ cl_is_chmod_supported () ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int filemode_count ; 
 int /*<<< orphan*/  filemode_paths ; 
 scalar_t__* filemode_statuses ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void test_status_worktree__filemode_changes(void)
{
	git_repository *repo = cl_git_sandbox_init("filemodes");
	status_entry_counts counts;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;

	/* overwrite stored filemode with platform appropriate value */
	if (cl_is_chmod_supported())
		cl_repo_set_bool(repo, "core.filemode", true);
	else {
		int i;

		cl_repo_set_bool(repo, "core.filemode", false);

		/* won't trust filesystem mode diffs, so these will appear unchanged */
		for (i = 0; i < filemode_count; ++i)
			if (filemode_statuses[i] == GIT_STATUS_WT_MODIFIED)
				filemode_statuses[i] = GIT_STATUS_CURRENT;
	}

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_INCLUDE_IGNORED |
		GIT_STATUS_OPT_INCLUDE_UNMODIFIED;

	memset(&counts, 0, sizeof(counts));
	counts.expected_entry_count = filemode_count;
	counts.expected_paths = filemode_paths;
	counts.expected_statuses = filemode_statuses;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}