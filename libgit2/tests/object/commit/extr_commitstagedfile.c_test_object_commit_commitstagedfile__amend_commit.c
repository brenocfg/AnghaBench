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
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert_commit_is_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert_commit_tree_has_n_entries (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_commit_from_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_commit_amend (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_object_commit_commitstagedfile__amend_commit(void)
{
	git_index *index;
	git_oid old_oid, new_oid, tree_oid;
	git_commit *old_commit, *new_commit;
	git_tree *tree;

	/* make a commit */

	cl_git_mkfile("treebuilder/myfile", "This is a file\n");
	cl_git_pass(git_repository_index(&index, repo));
	cl_git_pass(git_index_add_bypath(index, "myfile"));
	cl_repo_commit_from_index(&old_oid, repo, NULL, 0, "first commit");

	cl_git_pass(git_commit_lookup(&old_commit, repo, &old_oid));

	cl_assert_equal_i(0, git_commit_parentcount(old_commit));
	assert_commit_tree_has_n_entries(old_commit, 1);
	assert_commit_is_head(old_commit);

	/* let's amend the message of the HEAD commit */

	cl_git_pass(git_commit_amend(
		&new_oid, old_commit, "HEAD", NULL, NULL, NULL, "Initial commit", NULL));

	/* fail because the commit isn't the tip of the branch anymore */
	cl_git_fail(git_commit_amend(
		&new_oid, old_commit, "HEAD", NULL, NULL, NULL, "Initial commit", NULL));

	cl_git_pass(git_commit_lookup(&new_commit, repo, &new_oid));

	cl_assert_equal_i(0, git_commit_parentcount(new_commit));
	assert_commit_tree_has_n_entries(new_commit, 1);
	assert_commit_is_head(new_commit);

	git_commit_free(old_commit);

	old_commit = new_commit;

	/* let's amend the tree of that last commit */

	cl_git_mkfile("treebuilder/anotherfile", "This is another file\n");
	cl_git_pass(git_index_add_bypath(index, "anotherfile"));
	cl_git_pass(git_index_write_tree(&tree_oid, index));
	cl_git_pass(git_tree_lookup(&tree, repo, &tree_oid));
	cl_assert_equal_i(2, git_tree_entrycount(tree));

	/* fail to amend on a ref which does not exist */
	cl_git_fail_with(GIT_ENOTFOUND, git_commit_amend(
		&new_oid, old_commit, "refs/heads/nope", NULL, NULL, NULL, "Initial commit", tree));

	cl_git_pass(git_commit_amend(
		&new_oid, old_commit, "HEAD", NULL, NULL, NULL, "Initial commit", tree));
	git_tree_free(tree);

	cl_git_pass(git_commit_lookup(&new_commit, repo, &new_oid));

	cl_assert_equal_i(0, git_commit_parentcount(new_commit));
	assert_commit_tree_has_n_entries(new_commit, 2);
	assert_commit_is_head(new_commit);

	/* cleanup */

	git_commit_free(old_commit);
	git_commit_free(new_commit);
	git_index_free(index);
}