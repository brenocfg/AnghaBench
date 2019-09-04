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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  GIT_REFERENCE_DIRECT ; 
 int /*<<< orphan*/  GIT_REPOSITORY_STATE_NONE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int git_rebase_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_rebase_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_rebase_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int git_reference_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_id_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int git_repository_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 

void test_rebase_merge__finish_with_ids(void)
{
	git_rebase *rebase;
	git_reference *head_ref;
	git_oid branch_id, upstream_id;
	git_annotated_commit *branch_head, *upstream_head;
	git_rebase_operation *rebase_operation;
	git_oid commit_id;
	git_reflog *reflog;
	const git_reflog_entry *reflog_entry;
	int error;

	cl_git_pass(git_oid_fromstr(&branch_id, "d616d97082eb7bb2dc6f180a7cca940993b7a56f"));
	cl_git_pass(git_oid_fromstr(&upstream_id, "f87d14a4a236582a0278a916340a793714256864"));

	cl_git_pass(git_annotated_commit_lookup(&branch_head, repo, &branch_id));
	cl_git_pass(git_annotated_commit_lookup(&upstream_head, repo, &upstream_id));

	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, upstream_head, NULL, NULL));

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));

	cl_git_fail(error = git_rebase_next(&rebase_operation, rebase));
	cl_assert_equal_i(GIT_ITEROVER, error);

	cl_git_pass(git_rebase_finish(rebase, signature));

	cl_assert_equal_i(GIT_REPOSITORY_STATE_NONE, git_repository_state(repo));

	cl_git_pass(git_reference_lookup(&head_ref, repo, "HEAD"));
	cl_assert_equal_i(GIT_REFERENCE_DIRECT, git_reference_type(head_ref));
	cl_assert_equal_oid(&commit_id, git_reference_target(head_ref));

	/* reflogs are not updated as if we were operating on proper
	 * branches.  check that the last reflog entry is the rebase.
	 */
	cl_git_pass(git_reflog_read(&reflog, repo, "HEAD"));
	cl_assert(reflog_entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_oid(&commit_id, git_reflog_entry_id_new(reflog_entry));
	cl_assert_equal_s("rebase: Modification 3 to gravy", git_reflog_entry_message(reflog_entry));
	git_reflog_free(reflog);

	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(upstream_head);
	git_reference_free(head_ref);
	git_rebase_free(rebase);
}