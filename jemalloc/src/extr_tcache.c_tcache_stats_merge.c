#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  tcache_t ;
struct TYPE_12__ {scalar_t__ nrequests; } ;
struct TYPE_13__ {TYPE_2__ tstats; } ;
typedef  TYPE_3__ cache_bin_t ;
struct TYPE_11__ {int /*<<< orphan*/  nrequests; } ;
struct TYPE_14__ {int /*<<< orphan*/  lock; TYPE_1__ stats; } ;
typedef  TYPE_4__ bin_t ;
struct TYPE_15__ {int /*<<< orphan*/  stats; } ;
typedef  TYPE_5__ arena_t ;

/* Variables and functions */
 unsigned int SC_NBINS ; 
 TYPE_4__* arena_bin_choose_lock (int /*<<< orphan*/ *,TYPE_5__*,unsigned int,unsigned int*) ; 
 int /*<<< orphan*/  arena_stats_large_flush_nrequests_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_stats ; 
 int /*<<< orphan*/  malloc_mutex_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int nhbins ; 
 TYPE_3__* tcache_large_bin_get (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_3__* tcache_small_bin_get (int /*<<< orphan*/ *,unsigned int) ; 

void
tcache_stats_merge(tsdn_t *tsdn, tcache_t *tcache, arena_t *arena) {
	unsigned i;

	cassert(config_stats);

	/* Merge and reset tcache stats. */
	for (i = 0; i < SC_NBINS; i++) {
		cache_bin_t *tbin = tcache_small_bin_get(tcache, i);
		unsigned binshard;
		bin_t *bin = arena_bin_choose_lock(tsdn, arena, i, &binshard);
		bin->stats.nrequests += tbin->tstats.nrequests;
		malloc_mutex_unlock(tsdn, &bin->lock);
		tbin->tstats.nrequests = 0;
	}

	for (; i < nhbins; i++) {
		cache_bin_t *tbin = tcache_large_bin_get(tcache, i);
		arena_stats_large_flush_nrequests_add(tsdn, &arena->stats, i,
		    tbin->tstats.nrequests);
		tbin->tstats.nrequests = 0;
	}
}