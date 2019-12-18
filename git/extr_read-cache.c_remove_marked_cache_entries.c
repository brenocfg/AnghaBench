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
struct index_state {unsigned int cache_nr; int /*<<< orphan*/  cache_changed; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_REMOVED ; 
 int CE_REMOVE ; 
 int /*<<< orphan*/  cache_tree_invalidate_path (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_name_hash (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  save_or_free_index_entry (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  untracked_cache_remove_from_index (struct index_state*,int /*<<< orphan*/ ) ; 

void remove_marked_cache_entries(struct index_state *istate, int invalidate)
{
	struct cache_entry **ce_array = istate->cache;
	unsigned int i, j;

	for (i = j = 0; i < istate->cache_nr; i++) {
		if (ce_array[i]->ce_flags & CE_REMOVE) {
			if (invalidate) {
				cache_tree_invalidate_path(istate,
							   ce_array[i]->name);
				untracked_cache_remove_from_index(istate,
								  ce_array[i]->name);
			}
			remove_name_hash(istate, ce_array[i]);
			save_or_free_index_entry(istate, ce_array[i]);
		}
		else
			ce_array[j++] = ce_array[i];
	}
	if (j == istate->cache_nr)
		return;
	istate->cache_changed |= CE_ENTRY_REMOVED;
	istate->cache_nr = j;
}