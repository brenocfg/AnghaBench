#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  size_t szind_t ;
typedef  int /*<<< orphan*/  extent_t ;
struct TYPE_5__ {int /*<<< orphan*/  curregs; int /*<<< orphan*/  nrequests; int /*<<< orphan*/  nmalloc; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ stats; int /*<<< orphan*/ * slabcur; } ;
typedef  TYPE_2__ bin_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 size_t SC_NBINS ; 
 int /*<<< orphan*/  arena_alloc_junk_small (void*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__* arena_bin_choose_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t,unsigned int*) ; 
 void* arena_bin_malloc_hard (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_2__*,size_t,unsigned int) ; 
 int /*<<< orphan*/  arena_decay_tick (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* arena_slab_reg_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * bin_infos ; 
 scalar_t__ config_fill ; 
 scalar_t__ config_stats ; 
 scalar_t__ extent_nfree_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  opt_junk_alloc ; 
 int /*<<< orphan*/  opt_zero ; 
 size_t sz_index2size (size_t) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *
arena_malloc_small(tsdn_t *tsdn, arena_t *arena, szind_t binind, bool zero) {
	void *ret;
	bin_t *bin;
	size_t usize;
	extent_t *slab;

	assert(binind < SC_NBINS);
	usize = sz_index2size(binind);
	unsigned binshard;
	bin = arena_bin_choose_lock(tsdn, arena, binind, &binshard);

	if ((slab = bin->slabcur) != NULL && extent_nfree_get(slab) > 0) {
		ret = arena_slab_reg_alloc(slab, &bin_infos[binind]);
	} else {
		ret = arena_bin_malloc_hard(tsdn, arena, bin, binind, binshard);
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