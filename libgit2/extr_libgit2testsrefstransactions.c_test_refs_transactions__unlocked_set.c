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
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_tx ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_transaction_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_transaction_lock_ref (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_transaction_set_target (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_refs_transactions__unlocked_set(void)
{
	git_oid id;

	cl_git_pass(git_transaction_lock_ref(g_tx, "refs/heads/master"));
	git_oid_fromstr(&id, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750");
	cl_git_fail_with(GIT_ENOTFOUND, git_transaction_set_target(g_tx, "refs/heads/foo", &id, NULL, NULL));
	cl_git_pass(git_transaction_commit(g_tx));
}