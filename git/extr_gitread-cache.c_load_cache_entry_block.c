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
struct ondisk_cache_entry {int dummy; } ;
struct mem_pool {int dummy; } ;
struct index_state {int /*<<< orphan*/  version; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 struct cache_entry* create_from_disk (struct mem_pool*,int /*<<< orphan*/ ,struct ondisk_cache_entry*,unsigned long*,struct cache_entry const*) ; 
 int /*<<< orphan*/  set_index_entry (struct index_state*,int,struct cache_entry*) ; 

__attribute__((used)) static unsigned long load_cache_entry_block(struct index_state *istate,
			struct mem_pool *ce_mem_pool, int offset, int nr, const char *mmap,
			unsigned long start_offset, const struct cache_entry *previous_ce)
{
	int i;
	unsigned long src_offset = start_offset;

	for (i = offset; i < offset + nr; i++) {
		struct ondisk_cache_entry *disk_ce;
		struct cache_entry *ce;
		unsigned long consumed;

		disk_ce = (struct ondisk_cache_entry *)(mmap + src_offset);
		ce = create_from_disk(ce_mem_pool, istate->version, disk_ce, &consumed, previous_ce);
		set_index_entry(istate, i, ce);

		src_offset += consumed;
		previous_ce = ce;
	}
	return src_offset - start_offset;
}