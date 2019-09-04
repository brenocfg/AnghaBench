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
typedef  int /*<<< orphan*/  git_remote ;
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_REMOTE ; 
 int /*<<< orphan*/  cl_fixture_cleanup (char*) ; 
 int /*<<< orphan*/  cl_fixture_sandbox (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  push_array ; 

void test_network_remote_local__update_tips_for_new_remote(void) {
	git_repository *src_repo;
	git_repository *dst_repo;
	git_remote *new_remote;
	git_reference* branch;

	/* Copy test repo */
	cl_fixture_sandbox("testrepo.git");
	cl_git_pass(git_repository_open(&src_repo, "testrepo.git"));

	/* Set up an empty bare repo to push into */
	cl_git_pass(git_repository_init(&dst_repo, "./localbare.git", 1));

	/* Push to bare repo */
	cl_git_pass(git_remote_create(&new_remote, src_repo, "bare", "./localbare.git"));
	cl_git_pass(git_remote_push(new_remote, &push_array, NULL));
	/* Make sure remote branch has been created */
	cl_git_pass(git_branch_lookup(&branch, src_repo, "bare/master", GIT_BRANCH_REMOTE));

	git_reference_free(branch);
	git_remote_free(new_remote);
	git_repository_free(dst_repo);
	cl_fixture_cleanup("localbare.git");
	git_repository_free(src_repo);
	cl_fixture_cleanup("testrepo.git");
}