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
typedef  int /*<<< orphan*/  git_treebuilder ;
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_entry_filemode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_treebuilder_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  tree_oid ; 

void test_object_tree_attributes__normalize_attributes_when_creating_a_tree_from_an_existing_one(void)
{
	git_treebuilder *builder;
	git_oid tid, tid2;
	git_tree *tree;
	const git_tree_entry *entry;

	cl_git_pass(git_oid_fromstr(&tid, tree_oid));
	cl_git_pass(git_tree_lookup(&tree, repo, &tid));

	cl_git_pass(git_treebuilder_new(&builder, repo, tree));
	
	entry = git_treebuilder_get(builder, "old_mode.txt");
	cl_assert(entry != NULL);
	cl_assert_equal_i(
		GIT_FILEMODE_BLOB,
		git_tree_entry_filemode(entry));

	cl_git_pass(git_treebuilder_write(&tid2, builder));
	git_treebuilder_free(builder);
	git_tree_free(tree);

	cl_git_pass(git_tree_lookup(&tree, repo, &tid2));
	entry = git_tree_entry_byname(tree, "old_mode.txt");
	cl_assert(entry != NULL);
	cl_assert_equal_i(
		GIT_FILEMODE_BLOB,
		git_tree_entry_filemode(entry));

	git_tree_free(tree);
}