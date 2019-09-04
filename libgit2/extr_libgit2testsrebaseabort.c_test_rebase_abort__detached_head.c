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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_STATE_REBASE_MERGE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  test_abort (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void test_rebase_abort__detached_head(void)
{
	git_rebase *rebase;
	git_oid branch_id, onto_id;
	git_signature *signature;
	git_annotated_commit *branch_head, *onto_head;

	git_oid_fromstr(&branch_id, "b146bd7608eac53d9bf9e1a6963543588b555c64");
    git_oid_fromstr(&onto_id, "efad0b11c47cb2f0220cbd6f5b0f93bb99064b00");

	cl_git_pass(git_annotated_commit_lookup(&branch_head, repo, &branch_id));
	cl_git_pass(git_annotated_commit_lookup(&onto_head, repo, &onto_id));

	cl_git_pass(git_signature_new(&signature, "Rebaser", "rebaser@example.com", 1404157834, -400));

	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, NULL, onto_head, NULL));
	cl_assert_equal_i(GIT_REPOSITORY_STATE_REBASE_MERGE, git_repository_state(repo));

	test_abort(branch_head, onto_head);

	git_signature_free(signature);

	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(onto_head);

	git_rebase_free(rebase);
}