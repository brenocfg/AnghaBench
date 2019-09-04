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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  committer_email ; 
 int /*<<< orphan*/  committer_name ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_commit_create_buffer (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_id_str ; 
 int /*<<< orphan*/  root_commit_message ; 
 int /*<<< orphan*/  tree_id_str ; 

void test_commit_write__into_buf(void)
{
	git_oid tree_id;
	git_signature *author, *committer;
	git_tree *tree;
	git_commit *parent;
	git_oid parent_id;
	git_buf commit = GIT_BUF_INIT;

	git_oid_fromstr(&tree_id, tree_id_str);
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));

	/* create signatures */
	cl_git_pass(git_signature_new(&committer, committer_name, committer_email, 123456789, 60));
	cl_git_pass(git_signature_new(&author, committer_name, committer_email, 987654321, 90));

	git_oid_fromstr(&parent_id, parent_id_str);
	cl_git_pass(git_commit_lookup(&parent, g_repo, &parent_id));

	cl_git_pass(git_commit_create_buffer(&commit, g_repo, author, committer,
					     NULL, root_commit_message, tree, 1, (const git_commit **) &parent));

	cl_assert_equal_s(commit.ptr,
			  "tree 1810dff58d8a660512d4832e740f692884338ccd\n\
parent 8496071c1b46c854b31185ea97743be6a8774479\n\
author Vicent Marti <vicent@github.com> 987654321 +0130\n\
committer Vicent Marti <vicent@github.com> 123456789 +0100\n\
\n\
This is a root commit\n\
   This is a root commit and should be the only one in this branch\n\
");

	git_buf_dispose(&commit);
	git_tree_free(tree);
	git_commit_free(parent);
	git_signature_free(author);
	git_signature_free(committer);
}