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
struct unpack_trees_options {size_t cache_bottom; TYPE_1__* src_index; } ;
struct cache_entry {int ce_flags; } ;
struct TYPE_2__ {size_t cache_nr; struct cache_entry** cache; } ;

/* Variables and functions */
 int CE_UNPACKED ; 

__attribute__((used)) static void mark_ce_used(struct cache_entry *ce, struct unpack_trees_options *o)
{
	ce->ce_flags |= CE_UNPACKED;

	if (o->cache_bottom < o->src_index->cache_nr &&
	    o->src_index->cache[o->cache_bottom] == ce) {
		int bottom = o->cache_bottom;
		while (bottom < o->src_index->cache_nr &&
		       o->src_index->cache[bottom]->ce_flags & CE_UNPACKED)
			bottom++;
		o->cache_bottom = bottom;
	}
}