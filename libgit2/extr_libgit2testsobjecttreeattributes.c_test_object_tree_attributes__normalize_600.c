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

/* Variables and functions */
 int GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * git_tree_entry_byname (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_entry_filemode (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_entry_filemode_raw (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  repo ; 

void test_object_tree_attributes__normalize_600(void)
{
	git_oid id;
	git_tree *tree;
	const git_tree_entry *entry;

	git_oid_fromstr(&id, "0810fb7818088ff5ac41ee49199b51473b1bd6c7");
	cl_git_pass(git_tree_lookup(&tree, repo, &id));

	entry = git_tree_entry_byname(tree, "ListaTeste.xml");
	cl_assert_equal_i(git_tree_entry_filemode(entry), GIT_FILEMODE_BLOB);
	cl_assert_equal_i(git_tree_entry_filemode_raw(entry), 0100600);

	git_tree_free(tree);
}