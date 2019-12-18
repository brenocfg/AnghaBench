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
typedef  int /*<<< orphan*/  git_transaction ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/ * g_tx ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_transaction_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_refs_transactions__commit_unlocks_unmodified_ref(void)
{
	git_transaction *second_tx;

	cl_git_pass(git_transaction_new(&second_tx, g_repo));
	cl_git_pass(git_transaction_lock_ref(second_tx, "refs/heads/master"));
	cl_git_pass(git_transaction_commit(second_tx));

	/* a transaction must now be able to get the lock */
	cl_git_pass(git_transaction_lock_ref(g_tx, "refs/heads/master"));

	git_transaction_free(second_tx);
}