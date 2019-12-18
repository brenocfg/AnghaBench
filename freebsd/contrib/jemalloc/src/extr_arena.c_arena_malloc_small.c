#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_9__ {int /*<<< orphan*/  curregs; int /*<<< orphan*/  nrequests; int /*<<< orphan*/  nmalloc; } ;
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_1__ stats; int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_2__ bin_t ;
struct TYPE_11__ {TYPE_2__* bins; } ;
typedef  TYPE_3__ arena_t ;

/* Variables and functions */
 size_t NBINS ; 
 int /*<<< orphan*/  arena_alloc_junk_small (void*,int /*<<< orphan*/ *,int) ; 
 void* arena_bin_malloc_hard (int /*<<< orphan*/ *,TYPE_3__*,TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ arena_prof_accum (int /*<<< orphan*/ *,TYPE_3__*,size_t) ; 
 void* arena_slab_reg_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bin_infos ; 
 scalar_t__ config_fill ; 
 scalar_t__ config_prof ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  opt_junk_alloc ; 
 int /*<<< orphan*/  opt_zero ; 
 int /*<<< orphan*/  prof_idump (int /*<<< orphan*/ *) ; 
 size_t sz_index2size (size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
arena_malloc_small(tsdn_t *tsdn, arena_t *arena, szind_t binind, bool zero) {
	void *ret;
	bin_t *bin;
	size_t usize;
	extent_t *slab;

	assert(binind < NBINS);
	bin = &arena->bins[binind];
	usize = sz_index2size(binind);

	malloc_mutex_lock(tsdn, &bin->lock);
	if ((slab = bin->slabcur) != NULL && extent_nfree_get(slab) > 0) {
		ret = arena_slab_reg_alloc(slab, &bin_infos[binind]);
	} else {
		ret = arena_bin_malloc_hard(tsdn, arena, bin, binind);
	}

	if (ret == NULL) {
		malloc_mutex_unlock(tsdn, &bin->lock);
		return NULL;
	}

	if (config_stats) {
		bin->stats.nmalloc++;
		bin->stats.nrequests++;
		bin->stats.curregs++;
	}
	malloc_mutex_unlock(tsdn, &bin->lock);
	if (config_prof && arena_prof_accum(tsdn, arena, usize)) {
		prof_idump(tsdn);
	}

	if (!zero) {
		if (config_fill) {
			if (unlikely(opt_junk_alloc)) {
				arena_alloc_junk_small(ret,
				    &bin_infos[binind], false);
			} else if (unlikely(opt_zero)) {
				memset(ret, 0, usize);
			}
		}
	} else {
		if (config_fill && unlikely(opt_junk_alloc)) {
			arena_alloc_junk_small(ret, &bin_infos[binind],
			    true);
		}
		memset(ret, 0, usize);
	}

	arena_decay_tick(tsdn, arena);
	return ret;
}