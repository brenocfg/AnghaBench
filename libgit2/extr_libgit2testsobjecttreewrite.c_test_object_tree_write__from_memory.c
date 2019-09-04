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
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  blob_oid ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  first_tree ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_treebuilder_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_treebuilder_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  second_tree ; 

void test_object_tree_write__from_memory(void)
{
	/* write a tree from a memory */
	git_treebuilder *builder;
	git_tree *tree;
	git_oid id, bid, rid, id2;

	git_oid_fromstr(&id, first_tree);
	git_oid_fromstr(&id2, second_tree);
	git_oid_fromstr(&bid, blob_oid);

	/* create a second tree from first tree using `git_treebuilder_insert`
	 * on REPOSITORY_FOLDER.
	 */
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_treebuilder_new(&builder, g_repo, tree));

	cl_git_fail(git_treebuilder_insert(NULL, builder, "",
		&bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "/",
		&bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, ".git",
		&bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "..",
		&bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, ".",
		&bid, GIT_FILEMODE_BLOB));
	cl_git_fail(git_treebuilder_insert(NULL, builder, "folder/new.txt",
		&bid, GIT_FILEMODE_BLOB));

	cl_git_pass(git_treebuilder_insert(
		NULL, builder, "new.txt", &bid, GIT_FILEMODE_BLOB));

	cl_git_pass(git_treebuilder_write(&rid, builder));

	cl_assert(git_oid_cmp(&rid, &id2) == 0);

	git_treebuilder_free(builder);
	git_tree_free(tree);
}