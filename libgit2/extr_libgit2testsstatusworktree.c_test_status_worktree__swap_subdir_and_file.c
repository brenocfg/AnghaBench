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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_IGNORED ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  entry_count3 ; 
 int /*<<< orphan*/  entry_paths3 ; 
 int /*<<< orphan*/  entry_paths3_icase ; 
 int /*<<< orphan*/  entry_statuses3 ; 
 int /*<<< orphan*/  entry_statuses3_icase ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  p_rename (char*,char*) ; 

void test_status_worktree__swap_subdir_and_file(void)
{
	status_entry_counts counts;
	git_repository *repo = cl_git_sandbox_init("status");
	git_index *index;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	bool ignore_case;

	cl_git_pass(git_repository_index(&index, repo));
	ignore_case = (git_index_caps(index) & GIT_INDEX_CAPABILITY_IGNORE_CASE) != 0;
	git_index_free(index);

	/* first alter the contents of the worktree */
	cl_git_pass(p_rename("status/current_file", "status/swap"));
	cl_git_pass(p_rename("status/subdir", "status/current_file"));
	cl_git_pass(p_rename("status/swap", "status/subdir"));

	cl_git_mkfile("status/.HEADER", "dummy");
	cl_git_mkfile("status/42-is-not-prime.sigh", "dummy");
	cl_git_mkfile("status/README.md", "dummy");

	/* now get status */
	memset(&counts, 0x0, sizeof(status_entry_counts));
	counts.expected_entry_count = entry_count3;
	counts.expected_paths = ignore_case ? entry_paths3_icase : entry_paths3;
	counts.expected_statuses = ignore_case ? entry_statuses3_icase : entry_statuses3;

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED |
		GIT_STATUS_OPT_INCLUDE_IGNORED;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts)
	);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}