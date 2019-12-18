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
struct index_state {int name_hash_initialized; int cache_nr; int /*<<< orphan*/ * cache; int /*<<< orphan*/  dir_hash; int /*<<< orphan*/  name_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_entry_cmp ; 
 int /*<<< orphan*/  dir_entry_cmp ; 
 int /*<<< orphan*/  hash_index_entry (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_disable_item_counting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_enable_item_counting (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hashmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ lookup_lazy_params (struct index_state*) ; 
 int /*<<< orphan*/  threaded_lazy_init_name_hash (struct index_state*) ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_performance_leave (char*) ; 

__attribute__((used)) static void lazy_init_name_hash(struct index_state *istate)
{

	if (istate->name_hash_initialized)
		return;
	trace_performance_enter();
	hashmap_init(&istate->name_hash, cache_entry_cmp, NULL, istate->cache_nr);
	hashmap_init(&istate->dir_hash, dir_entry_cmp, NULL, istate->cache_nr);

	if (lookup_lazy_params(istate)) {
		/*
		 * Disable item counting and automatic rehashing because
		 * we do per-chain (mod n) locking rather than whole hashmap
		 * locking and we need to prevent the table-size from changing
		 * and bucket items from being redistributed.
		 */
		hashmap_disable_item_counting(&istate->dir_hash);
		threaded_lazy_init_name_hash(istate);
		hashmap_enable_item_counting(&istate->dir_hash);
	} else {
		int nr;
		for (nr = 0; nr < istate->cache_nr; nr++)
			hash_index_entry(istate, istate->cache[nr]);
	}

	istate->name_hash_initialized = 1;
	trace_performance_leave("initialize name hash");
}