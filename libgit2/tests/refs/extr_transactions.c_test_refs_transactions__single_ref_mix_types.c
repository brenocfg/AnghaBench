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
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_tx ; 
 int /*<<< orphan*/  git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_transaction_set_symbolic_target (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_set_target (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_refs_transactions__single_ref_mix_types(void)
{
	git_reference *ref;
	git_oid id;

	git_oid_fromstr(&id, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");

	cl_git_pass(git_transaction_lock_ref(g_tx, "refs/heads/master"));
	cl_git_pass(git_transaction_lock_ref(g_tx, "HEAD"));
	cl_git_pass(git_transaction_set_symbolic_target(g_tx, "refs/heads/master", "refs/heads/foo", NULL, NULL));
	cl_git_pass(git_transaction_set_target(g_tx, "HEAD", &id, NULL, NULL));
	cl_git_pass(git_transaction_commit(g_tx));

	cl_git_pass(git_reference_lookup(&ref, g_repo, "refs/heads/master"));
	cl_assert_equal_s("refs/heads/foo", git_reference_symbolic_target(ref));
	git_reference_free(ref);

	cl_git_pass(git_reference_lookup(&ref, g_repo, "HEAD"));
	cl_assert(!git_oid_cmp(&id, git_reference_target(ref)));
	git_reference_free(ref);
}