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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 

void test_refs_revparse__issue_994(void)
{
	git_repository *repo;
	git_reference *head, *with_at;
	git_object *target;
	
	repo = cl_git_sandbox_init("testrepo.git");

	cl_assert_equal_i(GIT_ENOTFOUND,
		git_revparse_single(&target, repo, "origin/bim_with_3d@11296"));

	cl_assert_equal_i(GIT_ENOTFOUND,
		git_revparse_single(&target, repo, "refs/remotes/origin/bim_with_3d@11296"));


	cl_git_pass(git_repository_head(&head, repo));
	cl_git_pass(git_reference_create(
		&with_at,
		repo,
		"refs/remotes/origin/bim_with_3d@11296",
		git_reference_target(head),
		0,
		NULL));

	cl_git_pass(git_revparse_single(&target, repo, "origin/bim_with_3d@11296"));
	git_object_free(target);

	cl_git_pass(git_revparse_single(&target, repo, "refs/remotes/origin/bim_with_3d@11296"));
	git_object_free(target);

	git_reference_free(with_at);
	git_reference_free(head);
	cl_git_sandbox_cleanup();
}