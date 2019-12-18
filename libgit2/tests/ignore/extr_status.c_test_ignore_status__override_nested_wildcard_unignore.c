#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; int /*<<< orphan*/  show; } ;
typedef  TYPE_3__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_11__ {int /*<<< orphan*/  status; TYPE_2__* index_to_workdir; } ;
typedef  TYPE_4__ git_status_entry ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_1__ old_file; } ;

/* Variables and functions */
 TYPE_3__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_futils_mkdir_r (char*,int) ; 
 TYPE_4__* git_status_byindex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*) ; 

void test_ignore_status__override_nested_wildcard_unignore(void)
{
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_status_list *statuslist;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	const git_status_entry *status;

	cl_git_pass(git_futils_mkdir_r("empty_standard_repo/dir", 0777));
	cl_git_pass(git_futils_mkdir_r("empty_standard_repo/dir/subdir", 0777));
	cl_git_mkfile("empty_standard_repo/.gitignore", "a.test\n");
	cl_git_mkfile("empty_standard_repo/dir/.gitignore", "!*.test\n");
	cl_git_mkfile("empty_standard_repo/dir/subdir/.gitignore", "a.test\n");
	cl_git_mkfile("empty_standard_repo/dir/a.test", "pong");
	cl_git_mkfile("empty_standard_repo/dir/subdir/a.test", "pong");

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED | GIT_STATUS_OPT_RECURSE_UNTRACKED_DIRS;

	cl_git_pass(git_status_list_new(&statuslist, repo, &opts));
	cl_assert_equal_sz(4, git_status_list_entrycount(statuslist));

	status = git_status_byindex(statuslist, 0);
	cl_assert(status != NULL);
	cl_assert_equal_s(".gitignore", status->index_to_workdir->old_file.path);
	cl_assert_equal_i(GIT_STATUS_WT_NEW, status->status);

	status = git_status_byindex(statuslist, 1);
	cl_assert(status != NULL);
	cl_assert_equal_s("dir/.gitignore", status->index_to_workdir->old_file.path);
	cl_assert_equal_i(GIT_STATUS_WT_NEW, status->status);

	status = git_status_byindex(statuslist, 2);
	cl_assert(status != NULL);
	cl_assert_equal_s("dir/a.test", status->index_to_workdir->old_file.path);
	cl_assert_equal_i(GIT_STATUS_WT_NEW, status->status);

	status = git_status_byindex(statuslist, 3);
	cl_assert(status != NULL);
	cl_assert_equal_s("dir/subdir/.gitignore", status->index_to_workdir->old_file.path);
	cl_assert_equal_i(GIT_STATUS_WT_NEW, status->status);

	git_status_list_free(statuslist);
}