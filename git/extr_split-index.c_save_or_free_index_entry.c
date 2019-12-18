#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct index_state {TYPE_2__* split_index; } ;
struct cache_entry {int index; int /*<<< orphan*/  ce_flags; } ;
struct TYPE_4__ {TYPE_1__* base; } ;
struct TYPE_3__ {int cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  CE_REMOVE ; 
 int /*<<< orphan*/  discard_cache_entry (struct cache_entry*) ; 

void save_or_free_index_entry(struct index_state *istate, struct cache_entry *ce)
{
	if (ce->index &&
	    istate->split_index &&
	    istate->split_index->base &&
	    ce->index <= istate->split_index->base->cache_nr &&
	    ce == istate->split_index->base->cache[ce->index - 1])
		ce->ce_flags |= CE_REMOVE;
	else
		discard_cache_entry(ce);
}