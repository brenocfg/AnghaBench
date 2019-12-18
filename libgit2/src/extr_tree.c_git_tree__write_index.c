#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_7__ {int /*<<< orphan*/  tree_pool; TYPE_3__* tree; scalar_t__ ignore_case; } ;
typedef  TYPE_1__ git_index ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_8__ {scalar_t__ entry_count; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INDEX ; 
 int GIT_EUNMERGED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_index__set_ignore_case (TYPE_1__*,int) ; 
 scalar_t__ git_index_has_conflicts (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_cpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_pool_clear (int /*<<< orphan*/ *) ; 
 int git_tree_cache_read_tree (TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 
 int git_tree_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_tree__write_index(
	git_oid *oid, git_index *index, git_repository *repo)
{
	int ret;
	git_tree *tree;
	git_buf shared_buf = GIT_BUF_INIT;
	bool old_ignore_case = false;

	assert(oid && index && repo);

	if (git_index_has_conflicts(index)) {
		git_error_set(GIT_ERROR_INDEX,
			"cannot create a tree from a not fully merged index.");
		return GIT_EUNMERGED;
	}

	if (index->tree != NULL && index->tree->entry_count >= 0) {
		git_oid_cpy(oid, &index->tree->oid);
		return 0;
	}

	/* The tree cache didn't help us; we'll have to write
	 * out a tree. If the index is ignore_case, we must
	 * make it case-sensitive for the duration of the tree-write
	 * operation. */

	if (index->ignore_case) {
		old_ignore_case = true;
		git_index__set_ignore_case(index, false);
	}

	ret = write_tree(oid, repo, index, "", 0, &shared_buf);
	git_buf_dispose(&shared_buf);

	if (old_ignore_case)
		git_index__set_ignore_case(index, true);

	index->tree = NULL;

	if (ret < 0)
		return ret;

	git_pool_clear(&index->tree_pool);

	if ((ret = git_tree_lookup(&tree, repo, oid)) < 0)
		return ret;

	/* Read the tree cache into the index */
	ret = git_tree_cache_read_tree(&index->tree, tree, &index->tree_pool);
	git_tree_free(tree);

	return ret;
}