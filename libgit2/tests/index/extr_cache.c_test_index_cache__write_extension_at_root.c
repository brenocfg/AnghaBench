#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_9__ {TYPE_2__* tree; } ;
typedef  TYPE_1__ git_index ;
struct TYPE_10__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  children_count; int /*<<< orphan*/  entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_entrycount (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_open (TYPE_1__**,char const*) ; 
 int /*<<< orphan*/  git_index_read_tree (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (TYPE_1__*) ; 
 TYPE_2__* git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_unlink (char const*) ; 

void test_index_cache__write_extension_at_root(void)
{
	git_index *index;
	git_tree *tree;
	git_oid id;
	const char *tree_id_str = "45dd856fdd4d89b884c340ba0e047752d9b085d6";
	const char *index_file = "index-tree";

	cl_git_pass(git_index_open(&index, index_file));
	cl_assert(index->tree == NULL);
	cl_git_pass(git_oid_fromstr(&id, tree_id_str));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);

	cl_assert(index->tree);
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_index_open(&index, index_file));
	cl_assert(index->tree);

	cl_assert_equal_i(git_index_entrycount(index), index->tree->entry_count);
	cl_assert_equal_i(0, index->tree->children_count);

	cl_assert(git_oid_equal(&id, &index->tree->oid));

	cl_git_pass(p_unlink(index_file));
	git_index_free(index);
}