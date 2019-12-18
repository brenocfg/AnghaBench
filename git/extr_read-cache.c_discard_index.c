#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ nsec; scalar_t__ sec; } ;
struct index_state {int /*<<< orphan*/ * ce_mem_pool; int /*<<< orphan*/ * untracked; scalar_t__ cache_alloc; int /*<<< orphan*/  cache; scalar_t__ fsmonitor_has_run_once; scalar_t__ initialized; int /*<<< orphan*/  cache_tree; TYPE_1__ timestamp; scalar_t__ cache_changed; scalar_t__ cache_nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_AND_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cache_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_split_index (struct index_state*) ; 
 int /*<<< orphan*/  free_name_hash (struct index_state*) ; 
 int /*<<< orphan*/  free_untracked_cache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_pool_discard (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resolve_undo_clear_index (struct index_state*) ; 
 int /*<<< orphan*/  should_validate_cache_entries () ; 
 int /*<<< orphan*/  validate_cache_entries (struct index_state*) ; 

int discard_index(struct index_state *istate)
{
	/*
	 * Cache entries in istate->cache[] should have been allocated
	 * from the memory pool associated with this index, or from an
	 * associated split_index. There is no need to free individual
	 * cache entries. validate_cache_entries can detect when this
	 * assertion does not hold.
	 */
	validate_cache_entries(istate);

	resolve_undo_clear_index(istate);
	istate->cache_nr = 0;
	istate->cache_changed = 0;
	istate->timestamp.sec = 0;
	istate->timestamp.nsec = 0;
	free_name_hash(istate);
	cache_tree_free(&(istate->cache_tree));
	istate->initialized = 0;
	istate->fsmonitor_has_run_once = 0;
	FREE_AND_NULL(istate->cache);
	istate->cache_alloc = 0;
	discard_split_index(istate);
	free_untracked_cache(istate->untracked);
	istate->untracked = NULL;

	if (istate->ce_mem_pool) {
		mem_pool_discard(istate->ce_mem_pool, should_validate_cache_entries());
		istate->ce_mem_pool = NULL;
	}

	return 0;
}