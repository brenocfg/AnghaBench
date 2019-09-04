#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_7__ {int /*<<< orphan*/  name; int /*<<< orphan*/  email; } ;
typedef  TYPE_1__ git_signature ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_8__ {int /*<<< orphan*/  name; int /*<<< orphan*/  email; } ;

/* Variables and functions */
 scalar_t__ GIT_REFERENCE_SYMBOLIC ; 
 int /*<<< orphan*/  branch ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  committer_email ; 
 int /*<<< orphan*/  committer_name ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/ * git__strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create_v (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ ) ; 
 scalar_t__ git_commit_parentcount (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_target (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reference_target (int /*<<< orphan*/ ) ; 
 scalar_t__ git_reference_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* git_reflog_entry_committer (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_signature_new (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/ * head_old ; 
 int /*<<< orphan*/  root_commit_message ; 
 int /*<<< orphan*/  root_reflog_message ; 
 int /*<<< orphan*/  tree_id_str ; 

void test_commit_write__root(void)
{
	git_oid tree_id, commit_id;
	const git_oid *branch_oid;
	git_signature *author, *committer;
	const char *branch_name = "refs/heads/root-commit-branch";
	git_tree *tree;
	git_reflog *log;
	const git_reflog_entry *entry;

	git_oid_fromstr(&tree_id, tree_id_str);
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));

	/* create signatures */
	cl_git_pass(git_signature_new(&committer, committer_name, committer_email, 123456789, 60));
	cl_git_pass(git_signature_new(&author, committer_name, committer_email, 987654321, 90));

	/* First we need to update HEAD so it points to our non-existant branch */
	cl_git_pass(git_reference_lookup(&head, g_repo, "HEAD"));
	cl_assert(git_reference_type(head) == GIT_REFERENCE_SYMBOLIC);
	head_old = git__strdup(git_reference_symbolic_target(head));
	cl_assert(head_old != NULL);
	git_reference_free(head);

	cl_git_pass(git_reference_symbolic_create(&head, g_repo, "HEAD", branch_name, 1, NULL));

	cl_git_pass(git_commit_create_v(
		&commit_id, /* out id */
		g_repo,
		"HEAD",
		author,
		committer,
		NULL,
		root_commit_message,
		tree,
		0));

	git_object_free((git_object *)tree);
	git_signature_free(author);

	/*
	 * The fact that creating a commit works has already been
	 * tested. Here we just make sure it's our commit and that it was
	 * written as a root commit.
	 */
	cl_git_pass(git_commit_lookup(&commit, g_repo, &commit_id));
	cl_assert(git_commit_parentcount(commit) == 0);
	cl_git_pass(git_reference_lookup(&branch, g_repo, branch_name));
	branch_oid = git_reference_target(branch);
	cl_assert_equal_oid(branch_oid, &commit_id);
	cl_assert_equal_s(root_commit_message, git_commit_message(commit));

	cl_git_pass(git_reflog_read(&log, g_repo, branch_name));
	cl_assert_equal_i(1, git_reflog_entrycount(log));
	entry = git_reflog_entry_byindex(log, 0);
	cl_assert_equal_s(committer->email, git_reflog_entry_committer(entry)->email);
	cl_assert_equal_s(committer->name, git_reflog_entry_committer(entry)->name);
	cl_assert_equal_s(root_reflog_message, git_reflog_entry_message(entry));

	git_signature_free(committer);
	git_reflog_free(log);
}