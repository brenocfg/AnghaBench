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
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_actualobject ; 
 int /*<<< orphan*/  g_expectedobject ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_root_tree ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_lookup_bypath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_object_lookupbypath__from_subdir_tree(void)
{
	git_tree_entry *entry = NULL;
	git_tree *tree = NULL;

	cl_git_pass(git_tree_entry_bypath(&entry, g_root_tree, "subdir"));
	cl_git_pass(git_tree_lookup(&tree, g_repo, git_tree_entry_id(entry)));

	cl_git_pass(git_object_lookup_bypath(&g_actualobject, (git_object*)tree,
				"subdir_test2.txt", GIT_OBJECT_BLOB));
	cl_assert_equal_oid(git_object_id(g_expectedobject),
				git_object_id(g_actualobject));

	git_tree_entry_free(entry);
	git_tree_free(tree);
}