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
struct TYPE_7__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  show; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_OPT_DEFAULTS ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_WORKDIR_ONLY ; 
 unsigned int const GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cb_status__normal ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 char* longname ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

void test_status_worktree__long_filenames(void)
{
	char path[260*4+1];
	const char *expected_paths[] = {path};
	const unsigned int expected_statuses[] = {GIT_STATUS_WT_NEW};

	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	status_entry_counts counts = {0};

	/* Create directory with amazingly long filename */
	sprintf(path, "empty_standard_repo/%s", longname);
	cl_git_pass(git_futils_mkdir_r(path, 0777));
	sprintf(path, "empty_standard_repo/%s/foo", longname);
	cl_git_mkfile(path, "dummy");

	sprintf(path, "%s/foo", longname);
	counts.expected_entry_count = 1;
	counts.expected_paths = expected_paths;
	counts.expected_statuses = expected_statuses;

	opts.show = GIT_STATUS_SHOW_WORKDIR_ONLY;
	opts.flags = GIT_STATUS_OPT_DEFAULTS;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__normal, &counts) );
	cl_assert_equal_i(counts.expected_entry_count, counts.entry_count);
	cl_assert_equal_i(0, counts.wrong_status_flags_count);
	cl_assert_equal_i(0, counts.wrong_sorted_path);
}