#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  entry_count; int /*<<< orphan*/  children_count; } ;
typedef  TYPE_1__ git_tree_cache ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_16__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_17__ {TYPE_1__ const* tree; } ;
typedef  TYPE_3__ git_index ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_read_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_tree_cache_get (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 

void test_index_cache__read_tree_children(void)
{
	git_index *index;
	git_index_entry entry;
	git_tree *tree;
	const git_tree_cache *cache;
	git_oid tree_id;

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_clear(index));
	cl_assert(index->tree == NULL);


	/* add a bunch of entries at different levels */
	memset(&entry, 0x0, sizeof(git_index_entry));
	entry.path = "top-level";
	entry.mode = GIT_FILEMODE_BLOB;
	git_oid_fromstr(&entry.id, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf");
	cl_git_pass(git_index_add(index, &entry));


	entry.path = "subdir/some-file";
	cl_git_pass(git_index_add(index, &entry));

	entry.path = "subdir/even-deeper/some-file";
	cl_git_pass(git_index_add(index, &entry));

	entry.path = "subdir2/some-file";
	cl_git_pass(git_index_add(index, &entry));

	cl_git_pass(git_index_write_tree(&tree_id, index));
	cl_git_pass(git_index_clear(index));
	cl_assert(index->tree == NULL);

	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);

	cl_assert(index->tree);
	cl_assert_equal_i(2, index->tree->children_count);

	/* override with a slightly different id, also dummy */
	entry.path = "subdir/some-file";
	git_oid_fromstr(&entry.id, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf");
	cl_git_pass(git_index_add(index, &entry));

	cl_assert_equal_i(-1, index->tree->entry_count);

	cache = git_tree_cache_get(index->tree, "subdir");
	cl_assert(cache);
	cl_assert_equal_i(-1, cache->entry_count);

	cache = git_tree_cache_get(index->tree, "subdir/even-deeper");
	cl_assert(cache);
	cl_assert_equal_i(1, cache->entry_count);

	cache = git_tree_cache_get(index->tree, "subdir2");
	cl_assert(cache);
	cl_assert_equal_i(1, cache->entry_count);

	git_index_free(index);
}