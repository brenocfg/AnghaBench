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
struct TYPE_6__ {int expected_entry_count; char const** expected_paths; unsigned int const* expected_statuses; int /*<<< orphan*/  wrong_sorted_path; int /*<<< orphan*/  wrong_status_flags_count; int /*<<< orphan*/  entry_count; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ status_entry_counts ;
struct TYPE_7__ {int flags; int /*<<< orphan*/  show; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DEFAULTS ; 
 int GIT_STATUS_OPT_INCLUDE_UNREADABLE ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_WORKDIR_ONLY ; 
 unsigned int const GIT_STATUS_WT_UNREADABLE ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_skip () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  p_chmod (char*,int) ; 

void test_status_worktree__unreadable(void)
{
#ifndef GIT_WIN32
	const char *expected_paths[] = { "no_permission/foo" };
	const unsigned int expected_statuses[] = {GIT_STATUS_WT_UNREADABLE};

	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts = {0};

	if (geteuid() == 0)
		cl_skip();

	/* Create directory with no read permission */
	cl_git_pass(git_futils_mkdir_r("empty_standard_repo/no_permission", 0777));
	cl_git_mkfile("empty_standard_repo/no_permission/foo", "dummy");
	p_chmod("empty_standard_repo/no_permission", 0644);

	counts.expected_entry_count = 1;
	counts.expected_paths = expected_paths;
	counts.expected_statuses = expected_statuses;

	opts.show = GIT_STATUS_SHOW_WORKDIR_ONLY;
	opts.flags = GIT_STATUS_OPT_DEFAULTS | GIT_STATUS_OPT_INCLUDE_UNREADABLE;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts) );

	/* Restore permissions so we can cleanup :) */
	p_chmod("empty_standard_repo/no_permission", 0777);

	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
#else
	cl_skip();
#endif
}