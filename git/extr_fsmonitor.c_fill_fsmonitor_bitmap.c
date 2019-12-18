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
struct index_state {unsigned int cache_nr; int /*<<< orphan*/  fsmonitor_dirty; TYPE_1__** cache; } ;
struct TYPE_2__ {int ce_flags; } ;

/* Variables and functions */
 int CE_FSMONITOR_VALID ; 
 int CE_REMOVE ; 
 int /*<<< orphan*/  ewah_new () ; 
 int /*<<< orphan*/  ewah_set (int /*<<< orphan*/ ,unsigned int) ; 

void fill_fsmonitor_bitmap(struct index_state *istate)
{
	unsigned int i, skipped = 0;
	istate->fsmonitor_dirty = ewah_new();
	for (i = 0; i < istate->cache_nr; i++) {
		if (istate->cache[i]->ce_flags & CE_REMOVE)
			skipped++;
		else if (!(istate->cache[i]->ce_flags & CE_FSMONITOR_VALID))
			ewah_set(istate->fsmonitor_dirty, i - skipped);
	}
}