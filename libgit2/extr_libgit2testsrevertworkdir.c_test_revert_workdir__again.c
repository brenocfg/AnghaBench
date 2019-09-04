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
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revert (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_new (int /*<<< orphan*/ **,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  merge_test_index (int /*<<< orphan*/ ,struct merge_index_entry*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void test_revert_workdir__again(void)
{
	git_reference *head_ref;
	git_commit *orig_head;
	git_tree *reverted_tree;
	git_oid reverted_tree_oid, reverted_commit_oid;
	git_signature *signature;

	struct merge_index_entry merge_index_entries[] = {
		{ 0100644, "7731926a337c4eaba1e2187d90ebfa0a93659382", 0, "file1.txt" },
		{ 0100644, "0ab09ea6d4c3634bdf6c221626d8b6f7dd890767", 0, "file2.txt" },
		{ 0100644, "f4e107c230d08a60fb419d19869f1f282b272d9c", 0, "file3.txt" },
		{ 0100644, "0f5bfcf58c558d865da6be0281d7795993646cee", 0, "file6.txt" },
	};

	cl_git_pass(git_repository_head(&head_ref, repo));
	cl_git_pass(git_reference_peel((git_object **)&orig_head, head_ref, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(repo, (git_object *)orig_head, GIT_RESET_HARD, NULL));

	cl_git_pass(git_revert(repo, orig_head, NULL));

	cl_assert(merge_test_index(repo_index, merge_index_entries, 4));

	cl_git_pass(git_index_write_tree(&reverted_tree_oid, repo_index));
	cl_git_pass(git_tree_lookup(&reverted_tree, repo, &reverted_tree_oid));

	cl_git_pass(git_signature_new(&signature, "Reverter", "reverter@example.org", time(NULL), 0));
	cl_git_pass(git_commit_create(&reverted_commit_oid, repo, "HEAD", signature, signature, NULL, "Reverted!", reverted_tree, 1, (const git_commit **)&orig_head));

	cl_git_pass(git_revert(repo, orig_head, NULL));
	cl_assert(merge_test_index(repo_index, merge_index_entries, 4));

	git_signature_free(signature);
	git_tree_free(reverted_tree);
	git_commit_free(orig_head);
	git_reference_free(head_ref);
}