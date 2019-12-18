#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_7__ {size_t curslabs; size_t curregs; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  slabs_nonfull; int /*<<< orphan*/ * slabcur; TYPE_2__ stats; } ;
typedef  TYPE_3__ bin_t ;
struct TYPE_9__ {TYPE_1__* bins; } ;
typedef  TYPE_4__ arena_t ;
struct TYPE_10__ {size_t nregs; } ;
struct TYPE_6__ {TYPE_3__* bin_shards; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/ * arenas ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ atomic_load_p (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* bin_infos ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/ * extent_addr_get (int /*<<< orphan*/ *) ; 
 size_t extent_arena_ind_get (int /*<<< orphan*/  const*) ; 
 unsigned int extent_binshard_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * extent_heap_first (int /*<<< orphan*/ *) ; 
 size_t extent_nfree_get (int /*<<< orphan*/  const*) ; 
 size_t extent_size_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  extent_slab_get (int /*<<< orphan*/  const*) ; 
 size_t extent_szind_get (int /*<<< orphan*/  const*) ; 
 size_t extent_usize_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * iealloc (int /*<<< orphan*/ *,void const*) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

void
extent_util_stats_verbose_get(tsdn_t *tsdn, const void *ptr,
    size_t *nfree, size_t *nregs, size_t *size,
    size_t *bin_nfree, size_t *bin_nregs, void **slabcur_addr) {
	assert(ptr != NULL && nfree != NULL && nregs != NULL && size != NULL
	    && bin_nfree != NULL && bin_nregs != NULL && slabcur_addr != NULL);

	const extent_t *extent = iealloc(tsdn, ptr);
	if (unlikely(extent == NULL)) {
		*nfree = *nregs = *size = *bin_nfree = *bin_nregs = 0;
		*slabcur_addr = NULL;
		return;
	}

	*size = extent_size_get(extent);
	if (!extent_slab_get(extent)) {
		*nfree = *bin_nfree = *bin_nregs = 0;
		*nregs = 1;
		*slabcur_addr = NULL;
		return;
	}

	*nfree = extent_nfree_get(extent);
	const szind_t szind = extent_szind_get(extent);
	*nregs = bin_infos[szind].nregs;
	assert(*nfree <= *nregs);
	assert(*nfree * extent_usize_get(extent) <= *size);

	const arena_t *arena = (arena_t *)atomic_load_p(
	    &arenas[extent_arena_ind_get(extent)], ATOMIC_RELAXED);
	assert(arena != NULL);
	const unsigned binshard = extent_binshard_get(extent);
	bin_t *bin = &arena->bins[szind].bin_shards[binshard];

	malloc_mutex_lock(tsdn, &bin->lock);
	if (config_stats) {
		*bin_nregs = *nregs * bin->stats.curslabs;
		assert(*bin_nregs >= bin->stats.curregs);
		*bin_nfree = *bin_nregs - bin->stats.curregs;
	} else {
		*bin_nfree = *bin_nregs = 0;
	}
	extent_t *slab;
	if (bin->slabcur != NULL) {
		slab = bin->slabcur;
	} else {
		slab = extent_heap_first(&bin->slabs_nonfull);
	}
	*slabcur_addr = slab != NULL ? extent_addr_get(slab) : NULL;
	malloc_mutex_unlock(tsdn, &bin->lock);
}