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
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_fetch (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_remote_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_remote_set_url (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void test_fetchhead_nonetwork__fetch_into_repo_with_symrefs(void)
{
	git_repository *repo;
	git_remote *remote;
	git_reference *symref;

	repo = cl_git_sandbox_init("empty_standard_repo");

	/*
	 * Testing for a specific constellation where the repository has at
	 * least one symbolic reference in its refdb.
	 */
	cl_git_pass(git_reference_symbolic_create(&symref, repo, "refs/heads/symref", "refs/heads/master", 0, NULL));

	cl_git_pass(git_remote_set_url(repo, "origin", cl_fixture("testrepo.git")));
	cl_git_pass(git_remote_lookup(&remote, repo, "origin"));
	cl_git_pass(git_remote_fetch(remote, NULL, NULL, NULL));

	git_remote_free(remote);
	git_reference_free(symref);
	cl_git_sandbox_cleanup();
}