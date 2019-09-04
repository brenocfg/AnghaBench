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
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_tx ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_transaction_remove (int /*<<< orphan*/ ,char*) ; 

void test_refs_transactions__single_ref_delete(void)
{
	git_reference *ref;

	cl_git_pass(git_transaction_lock_ref(g_tx, "refs/heads/master"));
	cl_git_pass(git_transaction_remove(g_tx, "refs/heads/master"));
	cl_git_pass(git_transaction_commit(g_tx));

	cl_git_fail_with(GIT_ENOTFOUND, git_reference_lookup(&ref, g_repo, "refs/heads/master"));
}