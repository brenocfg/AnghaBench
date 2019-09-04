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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_rebase_operation ;
typedef  int /*<<< orphan*/  git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message_encoding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_parent_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_rebase_commit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_init (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_id_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_id_old (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  const* git_signature__equal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/ * signature ; 

void test_rebase_merge__commit_with_id(void)
{
	git_rebase *rebase;
	git_oid branch_id, upstream_id;
	git_annotated_commit *branch_head, *upstream_head;
	git_rebase_operation *rebase_operation;
	git_oid commit_id, tree_id, parent_id;
	git_signature *author;
	git_commit *commit;
	git_reflog *reflog;
	const git_reflog_entry *reflog_entry;

	cl_git_pass(git_oid_fromstr(&branch_id, "b146bd7608eac53d9bf9e1a6963543588b555c64"));
	cl_git_pass(git_oid_fromstr(&upstream_id, "efad0b11c47cb2f0220cbd6f5b0f93bb99064b00"));

	cl_git_pass(git_annotated_commit_lookup(&branch_head, repo, &branch_id));
	cl_git_pass(git_annotated_commit_lookup(&upstream_head, repo, &upstream_id));

	cl_git_pass(git_rebase_init(&rebase, repo, branch_head, upstream_head, NULL, NULL));

	cl_git_pass(git_rebase_next(&rebase_operation, rebase));
	cl_git_pass(git_rebase_commit(&commit_id, rebase, NULL, signature,
		NULL, NULL));

	cl_git_pass(git_commit_lookup(&commit, repo, &commit_id));

	git_oid_fromstr(&parent_id, "efad0b11c47cb2f0220cbd6f5b0f93bb99064b00");
	cl_assert_equal_i(1, git_commit_parentcount(commit));
	cl_assert_equal_oid(&parent_id, git_commit_parent_id(commit, 0));

	git_oid_fromstr(&tree_id, "4461379789c777d2a6c1f2ee0e9d6c86731b9992");
	cl_assert_equal_oid(&tree_id, git_commit_tree_id(commit));

	cl_assert_equal_s(NULL, git_commit_message_encoding(commit));
	cl_assert_equal_s("Modification 1 to beef\n", git_commit_message(commit));

	cl_git_pass(git_signature_new(&author,
		"Edward Thomson", "ethomson@edwardthomson.com", 1405621769, 0-(4*60)));
	cl_assert(git_signature__equal(author, git_commit_author(commit)));

	cl_assert(git_signature__equal(signature, git_commit_committer(commit)));

	/* Make sure the reflogs are updated appropriately */
	cl_git_pass(git_reflog_read(&reflog, repo, "HEAD"));
	cl_assert(reflog_entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_oid(&parent_id, git_reflog_entry_id_old(reflog_entry));
	cl_assert_equal_oid(&commit_id, git_reflog_entry_id_new(reflog_entry));
	cl_assert_equal_s("rebase: Modification 1 to beef", git_reflog_entry_message(reflog_entry));

	git_reflog_free(reflog);
	git_signature_free(author);
	git_commit_free(commit);
	git_annotated_commit_free(branch_head);
	git_annotated_commit_free(upstream_head);
	git_rebase_free(rebase);
}