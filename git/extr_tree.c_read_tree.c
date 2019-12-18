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
struct tree {int dummy; } ;
struct repository {int dummy; } ;
struct pathspec {int dummy; } ;
struct index_state {int cache_nr; struct cache_entry** cache; int /*<<< orphan*/  cache_tree; } ;
struct cache_entry {int dummy; } ;
typedef  scalar_t__ read_tree_fn_t ;

/* Variables and functions */
 int /*<<< orphan*/  QSORT (struct cache_entry**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_tree_free (int /*<<< orphan*/ *) ; 
 int ce_stage (struct cache_entry const*) ; 
 int /*<<< orphan*/  cmp_cache_name_compare ; 
 scalar_t__ read_one_entry ; 
 scalar_t__ read_one_entry_quick ; 
 int read_tree_recursive (struct repository*,struct tree*,char*,int /*<<< orphan*/ ,int,struct pathspec*,scalar_t__,struct index_state*) ; 

int read_tree(struct repository *r, struct tree *tree, int stage,
	      struct pathspec *match, struct index_state *istate)
{
	read_tree_fn_t fn = NULL;
	int i, err;

	/*
	 * Currently the only existing callers of this function all
	 * call it with stage=1 and after making sure there is nothing
	 * at that stage; we could always use read_one_entry_quick().
	 *
	 * But when we decide to straighten out git-read-tree not to
	 * use unpack_trees() in some cases, this will probably start
	 * to matter.
	 */

	/*
	 * See if we have cache entry at the stage.  If so,
	 * do it the original slow way, otherwise, append and then
	 * sort at the end.
	 */
	for (i = 0; !fn && i < istate->cache_nr; i++) {
		const struct cache_entry *ce = istate->cache[i];
		if (ce_stage(ce) == stage)
			fn = read_one_entry;
	}

	if (!fn)
		fn = read_one_entry_quick;
	err = read_tree_recursive(r, tree, "", 0, stage, match, fn, istate);
	if (fn == read_one_entry || err)
		return err;

	/*
	 * Sort the cache entry -- we need to nuke the cache tree, though.
	 */
	cache_tree_free(&istate->cache_tree);
	QSORT(istate->cache, istate->cache_nr, cmp_cache_name_compare);
	return 0;
}