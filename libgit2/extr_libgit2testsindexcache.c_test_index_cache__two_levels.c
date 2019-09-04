#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  entry_count; int /*<<< orphan*/  children_count; } ;
typedef  TYPE_1__ git_tree_cache ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_18__ {char* path; int /*<<< orphan*/  id; int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ git_index_entry ;
struct TYPE_19__ {TYPE_1__ const* tree; } ;
typedef  TYPE_3__ git_index ;
typedef  int /*<<< orphan*/  entry ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEMODE_BLOB ; 
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_free (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_read (TYPE_3__*,int) ; 
 int /*<<< orphan*/  git_index_read_tree (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (TYPE_3__*) ; 
 int /*<<< orphan*/  git_index_write_tree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (TYPE_3__**,int /*<<< orphan*/ ) ; 
 TYPE_1__ const* git_tree_cache_get (TYPE_1__ const*,char*) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int,int) ; 

void test_index_cache__two_levels(void)
{
	git_tree *tree;
	git_oid tree_id;
	git_index *index;
	git_index_entry entry;
	const git_tree_cache *tree_cache;

	cl_git_pass(git_repository_index(&index, g_repo));
	cl_git_pass(git_index_clear(index));

	memset(&entry, 0x0, sizeof(entry));
	entry.mode = GIT_FILEMODE_BLOB;
	cl_git_pass(git_oid_fromstr(&entry.id, "a8233120f6ad708f843d861ce2b7228ec4e3dec6"));
	entry.path = "top-level.txt";
	cl_git_pass(git_index_add(index, &entry));

	entry.path = "subdir/file.txt";
	cl_git_pass(git_index_add(index, &entry));

	/* the read-tree fills the tree cache */
	cl_git_pass(git_index_write_tree(&tree_id, index));
	cl_git_pass(git_tree_lookup(&tree, g_repo, &tree_id));
	cl_git_pass(git_index_read_tree(index, tree));
	git_tree_free(tree);
	cl_git_pass(git_index_write(index));

	/* we now must have cache entries for "" and "subdir" */
	cl_assert(index->tree);
	cl_assert(git_tree_cache_get(index->tree, "subdir"));

	cl_git_pass(git_index_read(index, true));
	/* we must still have cache entries for "" and "subdir", since we wrote it out */
	cl_assert(index->tree);
	cl_assert(git_tree_cache_get(index->tree, "subdir"));

	entry.path = "top-level.txt";
	cl_git_pass(git_oid_fromstr(&entry.id, "3697d64be941a53d4ae8f6a271e4e3fa56b022cc"));
	cl_git_pass(git_index_add(index, &entry));

	/* writ out the index after we invalidate the root */
	cl_git_pass(git_index_write(index));
	cl_git_pass(git_index_read(index, true));

	/* the cache for the subtree must still be valid, even if the root isn't */
	cl_assert(index->tree);
	cl_assert_equal_i(-1, index->tree->entry_count);
	cl_assert_equal_i(1, index->tree->children_count);
	tree_cache = git_tree_cache_get(index->tree, "subdir");
	cl_assert(tree_cache);
	cl_assert_equal_i(1, tree_cache->entry_count);

	git_index_free(index);
}