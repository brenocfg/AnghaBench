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
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_10__ {int /*<<< orphan*/ * baseline; int /*<<< orphan*/  show; } ;
typedef  TYPE_3__ git_status_options ;
typedef  int /*<<< orphan*/  git_status_list ;
struct TYPE_11__ {int /*<<< orphan*/  status; TYPE_2__* index_to_workdir; } ;
typedef  TYPE_4__ git_status_entry ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {TYPE_1__ old_file; } ;

/* Variables and functions */
 int GIT_STATUS_INDEX_NEW ; 
 TYPE_3__ GIT_STATUS_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_STATUS_SHOW_INDEX_AND_WORKDIR ; 
 int GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_repository_head_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 TYPE_4__* git_status_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stage_and_commit (int /*<<< orphan*/ *,char*) ; 

void test_status_worktree__at_head_parent(void)
{
	git_repository *repo = cl_git_sandbox_init("empty_standard_repo");
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	git_status_list *statuslist;
	git_tree *parent_tree;
	const git_status_entry *status;

	cl_git_mkfile("empty_standard_repo/file1", "ping");
	stage_and_commit(repo, "file1");

	cl_git_pass(git_repository_head_tree(&parent_tree, repo));

	cl_git_mkfile("empty_standard_repo/file2", "pong");
	stage_and_commit(repo, "file2");

	cl_git_rewritefile("empty_standard_repo/file2", "pyng");

	opts.show = GIT_STATUS_SHOW_INDEX_AND_WORKDIR;
	opts.baseline = parent_tree;
	cl_git_pass(git_status_list_new(&statuslist, repo, &opts));

	cl_assert_equal_sz(1, git_status_list_entrycount(statuslist));
	status = git_status_byindex(statuslist, 0);
	cl_assert(status != NULL);
	cl_assert_equal_s("file2", status->index_to_workdir->old_file.path);
	cl_assert_equal_i(GIT_STATUS_WT_MODIFIED | GIT_STATUS_INDEX_NEW, status->status);

	git_tree_free(parent_tree);
	git_status_list_free(statuslist);
}