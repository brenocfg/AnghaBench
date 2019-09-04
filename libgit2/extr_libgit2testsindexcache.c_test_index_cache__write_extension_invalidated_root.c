#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_14__ {char* path; int /*<<< orphan*/  mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
struct TYPE_15__ {TYPE_4__* tree; } ;
typedef  TYPE_2__ git_index ;
struct TYPE_17__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {int /*<<< orphan*/  oid; int /*<<< orphan*/  children_count; int /*<<< orphan*/  entry_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_4__*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_2__*) ; 
 TYPE_8__* git_index_get_byindex (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_open (TYPE_2__**,char const*) ; 
 int /*<<< orphan*/  git_index_read_tree (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (TYPE_2__*) ; 
 TYPE_4__* git_oid_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  p_unlink (char const*) ; 

void test_index_cache__write_extension_invalidated_root(void)
{
	git_index *index;
	git_tree *tree;
	git_oid id;
	const char *tree_id_str = "45dd856fdd4d89b884c340ba0e047752d9b085d6";
	const char *index_file = "index-tree-invalidated";
	git_index_entry entry;

	cl_git_pass(git_index_open(&index, index_file));
	cl_assert(index->tree == NULL);
	cl_git_pass(git_oid_fromstr(&id, tree_id_str));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &id));
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);

	cl_assert(index->tree);

	memset(&entry, 0x0, sizeof(git_index_entry));
	git_oid_cpy(&entry.id, &git_index_get_byindex(index, 0)->id);
	entry.mode = GIT_FILEMODE_BLOB;
	entry.path = "some-new-file.txt";

	cl_git_pass(git_index_add(index, &entry));

	cl_assert_equal_i(-1, index->tree->entry_count);

	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_index_open(&index, index_file));
	cl_assert(index->tree);

	cl_assert_equal_i(-1, index->tree->entry_count);
	cl_assert_equal_i(0, index->tree->children_count);

	cl_assert(git_oid_cmp(&id, &index->tree->oid));

	cl_git_pass(p_unlink(index_file));
	git_index_free(index);
}