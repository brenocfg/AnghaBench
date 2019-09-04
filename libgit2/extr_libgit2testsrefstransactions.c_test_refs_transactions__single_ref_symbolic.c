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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_tx ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_transaction_set_symbolic_target (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_refs_transactions__single_ref_symbolic(void)
{
	git_reference *ref;

	cl_git_pass(git_transaction_lock_ref(g_tx, "HEAD"));
	cl_git_pass(git_transaction_set_symbolic_target(g_tx, "HEAD", "refs/heads/foo", NULL, NULL));
	cl_git_pass(git_transaction_commit(g_tx));

	cl_git_pass(git_reference_lookup(&ref, g_repo, "HEAD"));

	cl_assert_equal_s("refs/heads/foo", git_reference_symbolic_target(ref));
	git_reference_free(ref);
}