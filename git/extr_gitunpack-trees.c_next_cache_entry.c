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
struct unpack_trees_options {int cache_bottom; struct index_state* src_index; } ;
struct index_state {int cache_nr; struct cache_entry** cache; } ;
struct cache_entry {int ce_flags; } ;

/* Variables and functions */
 int CE_UNPACKED ; 

__attribute__((used)) static struct cache_entry *next_cache_entry(struct unpack_trees_options *o)
{
	const struct index_state *index = o->src_index;
	int pos = o->cache_bottom;

	while (pos < index->cache_nr) {
		struct cache_entry *ce = index->cache[pos];
		if (!(ce->ce_flags & CE_UNPACKED))
			return ce;
		pos++;
	}
	return NULL;
}