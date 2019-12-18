#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_12__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_13__ {TYPE_4__* tree; } ;
typedef  TYPE_2__ git_index ;
struct TYPE_14__ {int /*<<< orphan*/  entry_count; int /*<<< orphan*/  children_count; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_4__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (TYPE_2__*,TYPE_1__*) ; 
 int git_index_entrycount (TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_new (TYPE_2__**) ; 
 int /*<<< orphan*/  git_index_read_tree (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* git_oid_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 

void test_index_cache__read_tree_no_children(void)
{
	git_index *index;
	git_index_entry entry;
	git_tree *tree;
	git_oid id;

	cl_git_pass(git_index_new(&index));
	cl_assert(index->tree == NULL);
	cl_git_pass(git_oid_fromstr(&id, "45dd856fdd4d89b884c340ba0e047752d9b085d6"));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);

	cl_assert(index->tree);
	cl_assert(git_oid_equal(&id, &index->tree->oid));
	cl_assert_equal_i(0, index->tree->children_count);
	cl_assert_equal_i(git_index_entrycount(index), index->tree->entry_count);

	memset(&entry, 0x0, sizeof(git_index_entry));
	entry.path = "new.txt";
	entry.mode = GIT_FILEMODE_BLOB;
	git_oid_fromstr(&entry.id, "d4bcc68acd4410bf836a39f20afb2c2ece09584e");

	cl_git_pass(git_index_add(index, &entry));
	cl_assert_equal_i(-1, index->tree->entry_count);

	git_index_free(index);
}