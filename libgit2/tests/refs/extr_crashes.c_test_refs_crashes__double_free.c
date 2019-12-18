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

/* Variables and functions */
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_cleanup () ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_refs_crashes__double_free(void)
{
	git_repository *repo;
	git_reference *ref, *ref2;
	const char *REFNAME = "refs/heads/xxx";

	repo = cl_git_sandbox_init("testrepo.git");
	cl_git_pass(git_reference_symbolic_create(&ref, repo, REFNAME, "refs/heads/master", 0, NULL));
	cl_git_pass(git_reference_lookup(&ref2, repo, REFNAME));
	cl_git_pass(git_reference_delete(ref));
	git_reference_free(ref);
	git_reference_free(ref2);

	/* reference is gone from disk, so reloading it will fail */
	cl_git_fail(git_reference_lookup(&ref2, repo, REFNAME));

	cl_git_sandbox_cleanup();
}