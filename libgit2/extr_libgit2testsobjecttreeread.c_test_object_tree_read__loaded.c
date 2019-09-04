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

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byindex (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_oid ; 

void test_object_tree_read__loaded(void)
{
	/* acces randomly the entries on a loaded tree */
	git_oid id;
	git_tree *tree;

	git_oid_fromstr(&id, tree_oid);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));

	cl_assert(git_tree_entry_byname(tree, "README") != NULL);
	cl_assert(git_tree_entry_byname(tree, "NOTEXISTS") == NULL);
	cl_assert(git_tree_entry_byname(tree, "") == NULL);
	cl_assert(git_tree_entry_byindex(tree, 0) != NULL);
	cl_assert(git_tree_entry_byindex(tree, 2) != NULL);
	cl_assert(git_tree_entry_byindex(tree, 3) == NULL);
	cl_assert(git_tree_entry_byindex(tree, (unsigned int)-1) == NULL);

	git_tree_free(tree);
}