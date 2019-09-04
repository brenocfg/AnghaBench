#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_branch_upstream_remote (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_delete_entry (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_refs_branches_upstream__upstream_remote_empty_value(void)
{
	git_repository *repository;
	git_config *cfg;
	git_buf buf = GIT_BUF_INIT;

	repository = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_repository_config(&cfg, repository));
	cl_git_pass(git_config_set_string(cfg, "branch.master.remote", ""));
	cl_git_fail_with(GIT_ENOTFOUND, git_branch_upstream_remote(&buf, repository, "refs/heads/master"));

	cl_git_pass(git_config_delete_entry(cfg, "branch.master.remote"));
	cl_git_fail_with(GIT_ENOTFOUND, git_branch_upstream_remote(&buf, repository, "refs/heads/master"));
	cl_git_sandbox_cleanup();
}