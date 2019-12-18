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
struct index_state {int version; int /*<<< orphan*/  cache_nr; int /*<<< orphan*/  ce_mem_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  estimate_cache_size (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  estimate_cache_size_from_compressed (int /*<<< orphan*/ ) ; 
 unsigned long load_cache_entry_block (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mem_pool_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long load_all_cache_entries(struct index_state *istate,
			const char *mmap, size_t mmap_size, unsigned long src_offset)
{
	unsigned long consumed;

	if (istate->version == 4) {
		mem_pool_init(&istate->ce_mem_pool,
				estimate_cache_size_from_compressed(istate->cache_nr));
	} else {
		mem_pool_init(&istate->ce_mem_pool,
				estimate_cache_size(mmap_size, istate->cache_nr));
	}

	consumed = load_cache_entry_block(istate, istate->ce_mem_pool,
					0, istate->cache_nr, mmap, src_offset, NULL);
	return consumed;
}