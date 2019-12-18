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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_actualobject ; 
 int /*<<< orphan*/  g_expectedobject ; 
 int /*<<< orphan*/  g_head_commit ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  g_root_tree ; 
 int /*<<< orphan*/  git_commit_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_entry_id (int /*<<< orphan*/ *) ; 

void test_object_lookupbypath__initialize(void)
{
	git_reference *head;
	git_tree_entry *tree_entry;

	cl_git_pass(git_repository_open(&g_repo, cl_fixture("attr/.gitted")));

	cl_git_pass(git_repository_head(&head, g_repo));
	cl_git_pass(git_reference_peel((git_object**)&g_head_commit, head, GIT_OBJECT_COMMIT));
	cl_git_pass(git_commit_tree(&g_root_tree, g_head_commit));
	cl_git_pass(git_tree_entry_bypath(&tree_entry, g_root_tree, "subdir/subdir_test2.txt"));
	cl_git_pass(git_object_lookup(&g_expectedobject, g_repo, git_tree_entry_id(tree_entry),
				GIT_OBJECT_ANY));

	git_tree_entry_free(tree_entry);
	git_reference_free(head);

	g_actualobject = NULL;
}