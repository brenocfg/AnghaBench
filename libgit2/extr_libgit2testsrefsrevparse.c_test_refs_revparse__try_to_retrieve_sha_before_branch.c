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
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_branch_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_tostr (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  test_object_inrepo (char*,char*,int /*<<< orphan*/ *) ; 

void test_refs_revparse__try_to_retrieve_sha_before_branch(void)
{
	git_repository *repo;
	git_reference *branch;
	git_object *target;
	char sha[GIT_OID_HEXSZ + 1];

	repo = cl_git_sandbox_init("testrepo.git");

	test_object_inrepo("a65fedf39aefe402d3bb6e24df4d4f5fe4547750", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);

	cl_git_pass(git_revparse_single(&target, repo, "HEAD~3"));
	cl_git_pass(git_branch_create(&branch, repo, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", (git_commit *)target, 0));

	git_oid_tostr(sha, GIT_OID_HEXSZ + 1, git_object_id(target));

	test_object_inrepo("a65fedf39aefe402d3bb6e24df4d4f5fe4547750", "a65fedf39aefe402d3bb6e24df4d4f5fe4547750", repo);
	test_object_inrepo("heads/a65fedf39aefe402d3bb6e24df4d4f5fe4547750", sha, repo);

	git_reference_free(branch);
	git_object_free(target);
	cl_git_sandbox_cleanup();
}