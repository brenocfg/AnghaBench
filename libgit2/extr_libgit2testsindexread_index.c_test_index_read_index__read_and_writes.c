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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  _index ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_index_read_index__read_and_writes(void)
{
	git_oid tree_id, new_tree_id;
	git_tree *tree;
	git_index *tree_index, *new_index;

	cl_git_pass(git_oid_fromstr(&tree_id, "ae90f12eea699729ed24555e40b9fd669da12a12"));
	cl_git_pass(git_tree_lookup(&tree, _repo, &tree_id));
	cl_git_pass(git_index_new(&tree_index));
	cl_git_pass(git_index_read_tree(tree_index, tree));
	cl_git_pass(git_index_read_index(_index, tree_index));
	cl_git_pass(git_index_write(_index));

	cl_git_pass(git_index_open(&new_index, git_index_path(_index)));
	cl_git_pass(git_index_write_tree_to(&new_tree_id, new_index, _repo));

	cl_assert_equal_oid(&tree_id, &new_tree_id);

	git_tree_free(tree);
	git_index_free(tree_index);
	git_index_free(new_index);
}