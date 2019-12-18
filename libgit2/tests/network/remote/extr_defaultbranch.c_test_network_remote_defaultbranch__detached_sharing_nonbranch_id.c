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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_DIRECTION_FETCH ; 
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_remote ; 
 int /*<<< orphan*/  g_repo_a ; 
 int /*<<< orphan*/  git_clone (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_remove (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_remote_connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_default_branch (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_detach_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 

void test_network_remote_defaultbranch__detached_sharing_nonbranch_id(void)
{
	git_oid id, id_cloned;
	git_reference *ref;
	git_buf buf = GIT_BUF_INIT;
	git_repository *cloned_repo;

	cl_git_pass(git_reference_name_to_id(&id, g_repo_a, "HEAD"));
	cl_git_pass(git_repository_detach_head(g_repo_a));
	cl_git_pass(git_reference_remove(g_repo_a, "refs/heads/master"));
	cl_git_pass(git_reference_remove(g_repo_a, "refs/heads/not-good"));
	cl_git_pass(git_reference_create(&ref, g_repo_a, "refs/foo/bar", &id, 1, NULL));
	git_reference_free(ref);

	cl_git_pass(git_remote_connect(g_remote, GIT_DIRECTION_FETCH, NULL, NULL, NULL));
	cl_git_fail_with(GIT_ENOTFOUND, git_remote_default_branch(&buf, g_remote));

	cl_git_pass(git_clone(&cloned_repo, git_repository_path(g_repo_a), "./local-detached", NULL));

	cl_assert(git_repository_head_detached(cloned_repo));
	cl_git_pass(git_reference_name_to_id(&id_cloned, g_repo_a, "HEAD"));
	cl_assert(git_oid_equal(&id, &id_cloned));

	git_repository_free(cloned_repo);
}