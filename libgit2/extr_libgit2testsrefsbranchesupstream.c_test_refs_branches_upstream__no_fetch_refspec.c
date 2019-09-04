#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_2__ {int /*<<< orphan*/  message; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_branch_set_upstream (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_branch_upstream (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 
 TYPE_1__* git_error_last () ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_add_push (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_create_with_fetchspec (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_config (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void test_refs_branches_upstream__no_fetch_refspec(void)
{
	git_reference *ref, *branch;
	git_repository *repo;
	git_remote *remote;
	git_config *cfg;

	repo = cl_git_sandbox_init("testrepo.git");

	cl_git_pass(git_remote_create_with_fetchspec(&remote, repo, "matching", ".", NULL));
	cl_git_pass(git_remote_add_push(repo, "matching", ":"));

	cl_git_pass(git_reference_lookup(&branch, repo, "refs/heads/test"));
	cl_git_pass(git_reference_create(&ref, repo, "refs/remotes/matching/master", git_reference_target(branch), 1, "fetch"));
	cl_git_fail(git_branch_set_upstream(branch, "matching/master"));
	cl_assert_equal_s("could not determine remote for 'refs/remotes/matching/master'",
			  git_error_last()->message);

	/* we can't set it automatically, so let's test the user setting it by hand */
	cl_git_pass(git_repository_config(&cfg, repo));
	cl_git_pass(git_config_set_string(cfg, "branch.test.remote", "matching"));
	cl_git_pass(git_config_set_string(cfg, "branch.test.merge", "refs/heads/master"));
	/* we still can't find it because there is no rule for that reference */
	cl_git_fail_with(GIT_ENOTFOUND, git_branch_upstream(&ref, branch));

	git_reference_free(ref);
	git_reference_free(branch);
	git_remote_free(remote);

	cl_git_sandbox_cleanup();
}