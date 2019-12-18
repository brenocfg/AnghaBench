#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
struct TYPE_9__ {int time; int offset; } ;
struct TYPE_10__ {TYPE_1__ when; int /*<<< orphan*/  email; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_signature ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * commit ; 
 int /*<<< orphan*/  commit_message ; 
 int /*<<< orphan*/  committer_email ; 
 int /*<<< orphan*/  committer_name ; 
 int /*<<< orphan*/  g_repo ; 
 TYPE_2__* git_commit_author (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_commit_committer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_create_v (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_signature_new (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parent_id_str ; 
 int /*<<< orphan*/  tree_id_str ; 

void test_commit_write__from_memory(void)
{
   git_oid tree_id, parent_id, commit_id;
   git_signature *author, *committer;
   const git_signature *author1, *committer1;
   git_commit *parent;
   git_tree *tree;

   git_oid_fromstr(&tree_id, tree_id_str);
   cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));

   git_oid_fromstr(&parent_id, parent_id_str);
   cl_git_pass(git_commit_lookup(&parent, g_repo, &parent_id));

   /* create signatures */
   cl_git_pass(git_signature_new(&committer, committer_name, committer_email, 123456789, 60));
   cl_git_pass(git_signature_new(&author, committer_name, committer_email, 987654321, 90));

   cl_git_pass(git_commit_create_v(
      &commit_id, /* out id */
      g_repo,
      NULL, /* do not update the HEAD */
      author,
      committer,
      NULL,
      commit_message,
      tree,
      1, parent));

   git_object_free((git_object *)parent);
   git_object_free((git_object *)tree);

   git_signature_free(committer);
   git_signature_free(author);

   cl_git_pass(git_commit_lookup(&commit, g_repo, &commit_id));

   /* Check attributes were set correctly */
   author1 = git_commit_author(commit);
   cl_assert(author1 != NULL);
   cl_assert_equal_s(committer_name, author1->name);
   cl_assert_equal_s(committer_email, author1->email);
   cl_assert(author1->when.time == 987654321);
   cl_assert(author1->when.offset == 90);

   committer1 = git_commit_committer(commit);
   cl_assert(committer1 != NULL);
   cl_assert_equal_s(committer_name, committer1->name);
   cl_assert_equal_s(committer_email, committer1->email);
   cl_assert(committer1->when.time == 123456789);
   cl_assert(committer1->when.offset == 60);

   cl_assert_equal_s(commit_message, git_commit_message(commit));
}