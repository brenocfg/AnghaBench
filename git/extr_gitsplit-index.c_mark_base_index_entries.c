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
struct index_state {int cache_nr; TYPE_1__** cache; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */

__attribute__((used)) static void mark_base_index_entries(struct index_state *base)
{
	int i;
	/*
	 * To keep track of the shared entries between
	 * istate->base->cache[] and istate->cache[], base entry
	 * position is stored in each base entry. All positions start
	 * from 1 instead of 0, which is reserved to say "this is a new
	 * entry".
	 */
	for (i = 0; i < base->cache_nr; i++)
		base->cache[i]->index = i + 1;
}