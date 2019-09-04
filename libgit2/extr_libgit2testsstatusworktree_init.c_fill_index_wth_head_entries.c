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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fill_index_wth_head_entries(git_repository *repo, git_index *index)
{
	git_oid oid;
	git_commit *commit;
	git_tree *tree;

	cl_git_pass(git_reference_name_to_id(&oid, repo, "HEAD"));
	cl_git_pass(git_commit_lookup(&commit, repo, &oid));
	cl_git_pass(git_commit_tree(&tree, commit));

	cl_git_pass(git_index_read_tree(index, tree));
	cl_git_pass(git_index_write(index));

	git_tree_free(tree);
	git_commit_free(commit);
}