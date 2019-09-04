#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int flags_extended; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_ENTRY_UPTODATE ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_read_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree_to (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_uptodate_files () ; 

void test_index_racy__read_tree_clears_uptodate_bit(void)
{
	git_index *index;
	git_tree *tree;
	const git_index_entry *entry;
	git_oid id;

	setup_uptodate_files();

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_write_tree_to(&id, index, g_repo));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_index_read_tree(index, tree));

	/* ensure that no files are uptodate */
	cl_assert((entry = git_index_get_bypath(index, "A", 0)));
	cl_assert_equal_i(0, (entry->flags_extended & GIT_INDEX_ENTRY_UPTODATE));

	cl_assert((entry = git_index_get_bypath(index, "B", 0)));
	cl_assert_equal_i(0, (entry->flags_extended & GIT_INDEX_ENTRY_UPTODATE));

	cl_assert((entry = git_index_get_bypath(index, "C", 0)));
	cl_assert_equal_i(0, (entry->flags_extended & GIT_INDEX_ENTRY_UPTODATE));

	git_tree_free(tree);
	git_index_free(index);
}