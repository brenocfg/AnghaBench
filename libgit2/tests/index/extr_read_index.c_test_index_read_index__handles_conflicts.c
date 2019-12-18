#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_5__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index_conflict_iterator ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  add_conflicts (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_conflict_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_conflict_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_conflict_next (TYPE_1__ const**,TYPE_1__ const**,TYPE_1__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_index_read_index (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_index_read_index__handles_conflicts(void)
{
	git_oid tree_id;
	git_tree *tree;
	git_index *index, *new_index;
	git_index_conflict_iterator *conflict_iterator;
	const git_index_entry *ancestor, *ours, *theirs;

	cl_git_pass(git_oid_fromstr(&tree_id, "ae90f12eea699729ed24555e40b9fd669da12a12"));
	cl_git_pass(git_tree_lookup(&tree, _repo, &tree_id));
	cl_git_pass(git_index_new(&index));
	cl_git_pass(git_index_new(&new_index));
	cl_git_pass(git_index_read_tree(index, tree));
	cl_git_pass(git_index_read_tree(new_index, tree));

	/* put some conflicts in only the old side, these should be removed */
	add_conflicts(index, "orig_side-1.txt");
	add_conflicts(index, "orig_side-2.txt");

	/* put some conflicts in both indexes, these should be unchanged */
	add_conflicts(index, "both_sides-1.txt");
	add_conflicts(new_index,  "both_sides-1.txt");
	add_conflicts(index, "both_sides-2.txt");
	add_conflicts(new_index,  "both_sides-2.txt");

	/* put some conflicts in the new index, these should be added */
	add_conflicts(new_index, "new_side-1.txt");
	add_conflicts(new_index, "new_side-2.txt");

	cl_git_pass(git_index_read_index(index, new_index));
	cl_git_pass(git_index_conflict_iterator_new(&conflict_iterator, index));

	cl_git_pass(git_index_conflict_next(
		&ancestor, &ours, &theirs, conflict_iterator));
	cl_assert_equal_s("both_sides-1.txt", ancestor->path);
	cl_assert_equal_s("both_sides-1.txt", ours->path);
	cl_assert_equal_s("both_sides-1.txt", theirs->path);

	cl_git_pass(git_index_conflict_next(
		&ancestor, &ours, &theirs, conflict_iterator));
	cl_assert_equal_s("both_sides-2.txt", ancestor->path);
	cl_assert_equal_s("both_sides-2.txt", ours->path);
	cl_assert_equal_s("both_sides-2.txt", theirs->path);

	cl_git_pass(git_index_conflict_next(
		&ancestor, &ours, &theirs, conflict_iterator));
	cl_assert_equal_s("new_side-1.txt", ancestor->path);
	cl_assert_equal_s("new_side-1.txt", ours->path);
	cl_assert_equal_s("new_side-1.txt", theirs->path);

	cl_git_pass(git_index_conflict_next(
		&ancestor, &ours, &theirs, conflict_iterator));
	cl_assert_equal_s("new_side-2.txt", ancestor->path);
	cl_assert_equal_s("new_side-2.txt", ours->path);
	cl_assert_equal_s("new_side-2.txt", theirs->path);


	cl_git_fail_with(GIT_ITEROVER, git_index_conflict_next(
		&ancestor, &ours, &theirs, conflict_iterator));

	git_index_conflict_iterator_free(conflict_iterator);

	git_tree_free(tree);
	git_index_free(new_index);
	git_index_free(index);
}