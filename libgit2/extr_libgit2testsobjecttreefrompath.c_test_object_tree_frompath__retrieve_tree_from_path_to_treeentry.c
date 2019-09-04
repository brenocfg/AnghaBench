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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert_tree_from_path (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_bypath (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tree ; 

void test_object_tree_frompath__retrieve_tree_from_path_to_treeentry(void)
{
	git_tree_entry *e;

	assert_tree_from_path(tree, "README", "README");
	assert_tree_from_path(tree, "ab/de/fgh/1.txt", "1.txt");
	assert_tree_from_path(tree, "ab/de/fgh", "fgh");
	assert_tree_from_path(tree, "ab/de/fgh/", "fgh");
	assert_tree_from_path(tree, "ab/de", "de");
	assert_tree_from_path(tree, "ab/", "ab");
	assert_tree_from_path(tree, "ab/de/", "de");

	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "i-do-not-exist.txt"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "README/"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "ab/de/fgh/i-do-not-exist.txt"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "nope/de/fgh/1.txt"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "ab/me-neither/fgh/2.txt"));
	cl_assert_equal_i(GIT_ENOTFOUND, git_tree_entry_bypath(&e, tree, "ab/me-neither/fgh/2.txt/"));
}