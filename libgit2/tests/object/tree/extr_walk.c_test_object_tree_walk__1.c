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
 int /*<<< orphan*/  GIT_TREEWALK_POST ; 
 int /*<<< orphan*/  GIT_TREEWALK_PRE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int git_tree_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  tree_oid ; 
 int /*<<< orphan*/  treewalk_stop_cb ; 
 int /*<<< orphan*/  treewalk_stop_immediately_cb ; 

void test_object_tree_walk__1(void)
{
	git_oid id;
	git_tree *tree;
	int ct;

	git_oid_fromstr(&id, tree_oid);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));

	ct = 0;
	cl_assert_equal_i(
		-123, git_tree_walk(tree, GIT_TREEWALK_PRE, treewalk_stop_cb, &ct));
	cl_assert_equal_i(2, ct);

	ct = 0;
	cl_assert_equal_i(
		-123, git_tree_walk(tree, GIT_TREEWALK_POST, treewalk_stop_cb, &ct));
	cl_assert_equal_i(2, ct);

	cl_assert_equal_i(
		-100, git_tree_walk(
			tree, GIT_TREEWALK_PRE, treewalk_stop_immediately_cb, NULL));

	cl_assert_equal_i(
		-100, git_tree_walk(
			tree, GIT_TREEWALK_POST, treewalk_stop_immediately_cb, NULL));

	git_tree_free(tree);
}