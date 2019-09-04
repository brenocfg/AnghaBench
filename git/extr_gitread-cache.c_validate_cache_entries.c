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
struct index_state {int cache_nr; TYPE_1__* split_index; int /*<<< orphan*/ * cache; int /*<<< orphan*/  ce_mem_pool; int /*<<< orphan*/  initialized; } ;
struct TYPE_2__ {struct index_state* base; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
 int /*<<< orphan*/  mem_pool_contains (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  should_validate_cache_entries () ; 

void validate_cache_entries(const struct index_state *istate)
{
	int i;

	if (!should_validate_cache_entries() ||!istate || !istate->initialized)
		return;

	for (i = 0; i < istate->cache_nr; i++) {
		if (!istate) {
			BUG("cache entry is not allocated from expected memory pool");
		} else if (!istate->ce_mem_pool ||
			!mem_pool_contains(istate->ce_mem_pool, istate->cache[i])) {
			if (!istate->split_index ||
				!istate->split_index->base ||
				!istate->split_index->base->ce_mem_pool ||
				!mem_pool_contains(istate->split_index->base->ce_mem_pool, istate->cache[i])) {
				BUG("cache entry is not allocated from expected memory pool");
			}
		}
	}

	if (istate->split_index)
		validate_cache_entries(istate->split_index->base);
}