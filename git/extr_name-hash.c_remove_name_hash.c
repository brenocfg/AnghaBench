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
struct index_state {int /*<<< orphan*/  name_hash; int /*<<< orphan*/  name_hash_initialized; } ;
struct cache_entry {int ce_flags; int /*<<< orphan*/  ent; } ;

/* Variables and functions */
 int CE_HASHED ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cache_entry*) ; 
 scalar_t__ ignore_case ; 
 int /*<<< orphan*/  remove_dir_entry (struct index_state*,struct cache_entry*) ; 

void remove_name_hash(struct index_state *istate, struct cache_entry *ce)
{
	if (!istate->name_hash_initialized || !(ce->ce_flags & CE_HASHED))
		return;
	ce->ce_flags &= ~CE_HASHED;
	hashmap_remove(&istate->name_hash, &ce->ent, ce);

	if (ignore_case)
		remove_dir_entry(istate, ce);
}