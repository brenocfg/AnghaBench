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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_tx ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_transaction_set_target (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_refs_transactions__single_create(void)
{
	git_reference *ref;
	const char *name = "refs/heads/new-branch";
	git_oid id;

	cl_git_fail_with(GIT_ENOTFOUND, git_reference_lookup(&ref, g_repo, name));

	cl_git_pass(git_transaction_lock_ref(g_tx, name));

	git_oid_fromstr(&id, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	cl_git_pass(git_transaction_set_target(g_tx, name, &id, NULL, NULL));
	cl_git_pass(git_transaction_commit(g_tx));

	cl_git_pass(git_reference_lookup(&ref, g_repo, name));
	cl_assert(!git_oid_cmp(&id, git_reference_target(ref)));
	git_reference_free(ref);
}