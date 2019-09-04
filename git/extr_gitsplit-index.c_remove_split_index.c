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
struct index_state {int /*<<< orphan*/  cache_changed; TYPE_2__* split_index; int /*<<< orphan*/  ce_mem_pool; } ;
struct TYPE_4__ {TYPE_1__* base; } ;
struct TYPE_3__ {scalar_t__ cache_nr; int /*<<< orphan*/  ce_mem_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOMETHING_CHANGED ; 
 int /*<<< orphan*/  discard_split_index (struct index_state*) ; 
 int /*<<< orphan*/  mem_pool_combine (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void remove_split_index(struct index_state *istate)
{
	if (istate->split_index) {
		if (istate->split_index->base) {
			/*
			 * When removing the split index, we need to move
			 * ownership of the mem_pool associated with the
			 * base index to the main index. There may be cache entries
			 * allocated from the base's memory pool that are shared with
			 * the_index.cache[].
			 */
			mem_pool_combine(istate->ce_mem_pool,
					 istate->split_index->base->ce_mem_pool);

			/*
			 * The split index no longer owns the mem_pool backing
			 * its cache array. As we are discarding this index,
			 * mark the index as having no cache entries, so it
			 * will not attempt to clean up the cache entries or
			 * validate them.
			 */
			istate->split_index->base->cache_nr = 0;
		}

		/*
		 * We can discard the split index because its
		 * memory pool has been incorporated into the
		 * memory pool associated with the the_index.
		 */
		discard_split_index(istate);

		istate->cache_changed |= SOMETHING_CHANGED;
	}
}