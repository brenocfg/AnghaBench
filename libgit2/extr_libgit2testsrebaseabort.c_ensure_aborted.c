#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_status_list ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_5__ {int /*<<< orphan*/ * ref_name; } ;
typedef  TYPE_1__ git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_REPOSITORY_STATE_NONE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_id (TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 char* git_reference_symbolic_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_id_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_id_old (int /*<<< orphan*/  const*) ; 
 char* git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_repository_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_list_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_status_list_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void ensure_aborted(
	git_annotated_commit *branch,
	git_annotated_commit *onto)
{
	git_reference *head_ref, *branch_ref = NULL;
	git_status_list *statuslist;
	git_reflog *reflog;
	const git_reflog_entry *reflog_entry;

	cl_assert_equal_i(GIT_REPOSITORY_STATE_NONE, git_repository_state(repo));

	/* Make sure the refs are updated appropriately */
	cl_git_pass(git_reference_lookup(&head_ref, repo, "HEAD"));

	if (branch->ref_name == NULL)
		cl_assert_equal_oid(git_annotated_commit_id(branch), git_reference_target(head_ref));
	else {
		cl_assert_equal_s("refs/heads/beef", git_reference_symbolic_target(head_ref));
		cl_git_pass(git_reference_lookup(&branch_ref, repo, git_reference_symbolic_target(head_ref)));
		cl_assert_equal_oid(git_annotated_commit_id(branch), git_reference_target(branch_ref));
	}

	git_status_list_new(&statuslist, repo, NULL);
	cl_assert_equal_i(0, git_status_list_entrycount(statuslist));
	git_status_list_free(statuslist);

	/* Make sure the reflogs are updated appropriately */
	cl_git_pass(git_reflog_read(&reflog, repo, "HEAD"));

	cl_assert(reflog_entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_oid(git_annotated_commit_id(onto), git_reflog_entry_id_old(reflog_entry));
	cl_assert_equal_oid(git_annotated_commit_id(branch), git_reflog_entry_id_new(reflog_entry));
	cl_assert_equal_s("rebase: aborting", git_reflog_entry_message(reflog_entry));

	git_reflog_free(reflog);
	git_reference_free(head_ref);
	git_reference_free(branch_ref);
}