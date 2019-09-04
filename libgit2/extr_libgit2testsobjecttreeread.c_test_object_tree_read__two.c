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
typedef  int /*<<< orphan*/  git_tree_entry ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_fail (scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_entry_name (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_to_object (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int git_tree_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tree_oid ; 

void test_object_tree_read__two(void)
{
	/* read a tree from the repository */
	git_oid id;
	git_tree *tree;
	const git_tree_entry *entry;
	git_object *obj;

	git_oid_fromstr(&id, tree_oid);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));

	cl_assert(git_tree_entrycount(tree) == 3);

	/* GH-86: git_object_lookup() should also check the type if the object comes from the cache */
	cl_assert(git_object_lookup(&obj, g_repo, &id, GIT_OBJECT_TREE) == 0);
	cl_assert(obj != NULL);
	git_object_free(obj);
	obj = NULL;
	cl_git_fail(git_object_lookup(&obj, g_repo, &id, GIT_OBJECT_BLOB));
	cl_assert(obj == NULL);

	entry = git_tree_entry_byname(tree, "README");
	cl_assert(entry != NULL);

	cl_assert_equal_s(git_tree_entry_name(entry), "README");

	cl_git_pass(git_tree_entry_to_object(&obj, g_repo, entry));
	cl_assert(obj != NULL);

	git_object_free(obj);
	git_tree_free(tree);
}