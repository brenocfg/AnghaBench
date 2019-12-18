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
struct treewalk_skip_data {char* skip; char* stop; int /*<<< orphan*/  dirs; int /*<<< orphan*/  files; } ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_TREEWALK_PRE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_walk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct treewalk_skip_data*) ; 
 int /*<<< orphan*/  memset (struct treewalk_skip_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  treewalk_skip_de_cb ; 

void test_object_tree_walk__2(void)
{
	git_oid id;
	git_tree *tree;
	struct treewalk_skip_data data;

	/* look up a deep tree */
	git_oid_fromstr(&id, "ae90f12eea699729ed24555e40b9fd669da12a12");
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));

	memset(&data, 0, sizeof(data));
	data.skip = "de";

	cl_assert_equal_i(0, git_tree_walk(
		tree, GIT_TREEWALK_PRE, treewalk_skip_de_cb, &data));
	cl_assert_equal_i(5, data.files);
	cl_assert_equal_i(3, data.dirs);

	memset(&data, 0, sizeof(data));
	data.stop = "3.txt";

	cl_assert_equal_i(-1, git_tree_walk(
		tree, GIT_TREEWALK_PRE, treewalk_skip_de_cb, &data));
	cl_assert_equal_i(3, data.files);
	cl_assert_equal_i(2, data.dirs);

	memset(&data, 0, sizeof(data));
	data.skip = "new.txt";

	cl_assert_equal_i(0, git_tree_walk(
		tree, GIT_TREEWALK_PRE, treewalk_skip_de_cb, &data));
	cl_assert_equal_i(7, data.files);
	cl_assert_equal_i(4, data.dirs);

	memset(&data, 0, sizeof(data));
	data.stop = "new.txt";

	cl_assert_equal_i(-1, git_tree_walk(
		tree, GIT_TREEWALK_PRE, treewalk_skip_de_cb, &data));
	cl_assert_equal_i(7, data.files);
	cl_assert_equal_i(4, data.dirs);

	git_tree_free(tree);
}