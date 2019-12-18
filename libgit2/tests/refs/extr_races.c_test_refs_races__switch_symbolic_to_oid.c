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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_EMODIFIED ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_id ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_set_target (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  other_commit_id ; 
 int /*<<< orphan*/  other_refname ; 
 int /*<<< orphan*/  refname ; 

void test_refs_races__switch_symbolic_to_oid(void)
{
	git_reference *ref, *ref2, *ref3;
	git_oid id, other_id;

	git_oid_fromstr(&id, commit_id);
	git_oid_fromstr(&other_id, other_commit_id);

	/* Removing a symbolic ref when it's currently direct should fail */
	cl_git_pass(git_reference_lookup(&ref, g_repo, "HEAD"));
	cl_git_pass(git_reference_create(&ref2, g_repo, "HEAD", &id, 1, NULL));
	cl_git_fail_with(GIT_EMODIFIED, git_reference_delete(ref));

	git_reference_free(ref);
	git_reference_free(ref2);

	cl_git_pass(git_reference_symbolic_create(&ref, g_repo, "HEAD", refname, 1, NULL));
	git_reference_free(ref);

	/* Updating a symbolic ref when it's currently direct should fail */
	cl_git_pass(git_reference_lookup(&ref, g_repo, "HEAD"));
	cl_git_pass(git_reference_create(&ref2, g_repo, "HEAD", &id, 1, NULL));
	cl_git_fail_with(GIT_EMODIFIED, git_reference_symbolic_set_target(&ref3, ref, other_refname, NULL));

	git_reference_free(ref);
	git_reference_free(ref2);
	git_reference_free(ref3);
}