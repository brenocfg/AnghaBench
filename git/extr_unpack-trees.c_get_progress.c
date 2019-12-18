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
struct index_state {unsigned int cache_nr; struct cache_entry** cache; } ;
struct unpack_trees_options {int /*<<< orphan*/  verbose_update; int /*<<< orphan*/  update; struct index_state result; } ;
struct progress {int dummy; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_UPDATE ; 
 int CE_WT_REMOVE ; 
 int /*<<< orphan*/  _ (char*) ; 
 struct progress* start_delayed_progress (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static struct progress *get_progress(struct unpack_trees_options *o)
{
	unsigned cnt = 0, total = 0;
	struct index_state *index = &o->result;

	if (!o->update || !o->verbose_update)
		return NULL;

	for (; cnt < index->cache_nr; cnt++) {
		const struct cache_entry *ce = index->cache[cnt];
		if (ce->ce_flags & (CE_UPDATE | CE_WT_REMOVE))
			total++;
	}

	return start_delayed_progress(_("Updating files"), total);
}