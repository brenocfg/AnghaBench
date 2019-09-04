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
struct index_state {int /*<<< orphan*/  cache_changed; struct cache_entry** cache; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_ENTRY_CHANGED ; 
 int /*<<< orphan*/  CE_HASHED ; 
 int /*<<< orphan*/  CE_UPDATE_IN_BASE ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 
 int /*<<< orphan*/  mark_fsmonitor_invalid (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  remove_name_hash (struct index_state*,struct cache_entry*) ; 
 int /*<<< orphan*/  replace_index_entry_in_base (struct index_state*,struct cache_entry*,struct cache_entry*) ; 
 int /*<<< orphan*/  set_index_entry (struct index_state*,int,struct cache_entry*) ; 

__attribute__((used)) static void replace_index_entry(struct index_state *istate, int nr, struct cache_entry *ce)
{
	struct cache_entry *old = istate->cache[nr];

	replace_index_entry_in_base(istate, old, ce);
	remove_name_hash(istate, old);
	discard_cache_entry(old);
	ce->ce_flags &= ~CE_HASHED;
	set_index_entry(istate, nr, ce);
	ce->ce_flags |= CE_UPDATE_IN_BASE;
	mark_fsmonitor_invalid(istate, ce);
	istate->cache_changed |= CE_ENTRY_CHANGED;
}