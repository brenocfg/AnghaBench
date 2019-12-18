#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  base_t ;
struct TYPE_7__ {int /*<<< orphan*/  decay_muzzy; int /*<<< orphan*/  decay_dirty; } ;
struct TYPE_6__ {int /*<<< orphan*/  create_time; int /*<<< orphan*/ * base; int /*<<< orphan*/ * bins; int /*<<< orphan*/  extent_avail_mtx; int /*<<< orphan*/  extent_avail; int /*<<< orphan*/  extent_grow_mtx; int /*<<< orphan*/  retain_grow_limit; int /*<<< orphan*/  extent_grow_next; TYPE_3__ stats; int /*<<< orphan*/  decay_muzzy; int /*<<< orphan*/  decay_dirty; int /*<<< orphan*/  extents_retained; int /*<<< orphan*/  extents_muzzy; int /*<<< orphan*/  extents_dirty; int /*<<< orphan*/  large_mtx; int /*<<< orphan*/  large; int /*<<< orphan*/  nactive; int /*<<< orphan*/  dss_prec; int /*<<< orphan*/  extent_sn_next; int /*<<< orphan*/  offset_state; int /*<<< orphan*/  prof_accum; int /*<<< orphan*/  tcache_ql_mtx; int /*<<< orphan*/  cache_bin_array_descriptor_ql; int /*<<< orphan*/  tcache_ql; int /*<<< orphan*/ * last_thd; int /*<<< orphan*/ * nthreads; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  CACHELINE ; 
 int /*<<< orphan*/  EXTENT_GROW_MAX_PIND ; 
 int /*<<< orphan*/  HUGEPAGE ; 
 unsigned int NBINS ; 
 int /*<<< orphan*/  WITNESS_RANK_ARENA_LARGE ; 
 int /*<<< orphan*/  WITNESS_RANK_EXTENT_AVAIL ; 
 int /*<<< orphan*/  WITNESS_RANK_EXTENT_GROW ; 
 int /*<<< orphan*/  WITNESS_RANK_TCACHE_QL ; 
 scalar_t__ arena_decay_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_dirty_decay_ms_default_get () ; 
 int /*<<< orphan*/  arena_muzzy_decay_ms_default_get () ; 
 int /*<<< orphan*/  arena_set (unsigned int,TYPE_1__*) ; 
 scalar_t__ arena_stats_init (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  atomic_store_u (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_zu (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * b0get () ; 
 scalar_t__ base_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  base_delete (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * base_new (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int bin_init (int /*<<< orphan*/ *) ; 
 scalar_t__ config_cache_oblivious ; 
 scalar_t__ config_debug ; 
 scalar_t__ config_prof ; 
 scalar_t__ config_stats ; 
 int /*<<< orphan*/  extent_avail_new (int /*<<< orphan*/ *) ; 
 scalar_t__ extent_dss_prec_get () ; 
 int /*<<< orphan*/  extent_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_state_dirty ; 
 int /*<<< orphan*/  extent_state_muzzy ; 
 int /*<<< orphan*/  extent_state_retained ; 
 scalar_t__ extents_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hooks_arena_new_hook () ; 
 scalar_t__ malloc_mutex_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malloc_mutex_rank_exclusive ; 
 int /*<<< orphan*/  nstime_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nstime_update (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  post_reentrancy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pre_reentrancy (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ prof_accum_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ql_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sz_psz2ind (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsdn_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsdn_tsd (int /*<<< orphan*/ *) ; 

arena_t *
arena_new(tsdn_t *tsdn, unsigned ind, extent_hooks_t *extent_hooks) {
	arena_t *arena;
	base_t *base;
	unsigned i;

	if (ind == 0) {
		base = b0get();
	} else {
		base = base_new(tsdn, ind, extent_hooks);
		if (base == NULL) {
			return NULL;
		}
	}

	arena = (arena_t *)base_alloc(tsdn, base, sizeof(arena_t), CACHELINE);
	if (arena == NULL) {
		goto label_error;
	}

	atomic_store_u(&arena->nthreads[0], 0, ATOMIC_RELAXED);
	atomic_store_u(&arena->nthreads[1], 0, ATOMIC_RELAXED);
	arena->last_thd = NULL;

	if (config_stats) {
		if (arena_stats_init(tsdn, &arena->stats)) {
			goto label_error;
		}

		ql_new(&arena->tcache_ql);
		ql_new(&arena->cache_bin_array_descriptor_ql);
		if (malloc_mutex_init(&arena->tcache_ql_mtx, "tcache_ql",
		    WITNESS_RANK_TCACHE_QL, malloc_mutex_rank_exclusive)) {
			goto label_error;
		}
	}

	if (config_prof) {
		if (prof_accum_init(tsdn, &arena->prof_accum)) {
			goto label_error;
		}
	}

	if (config_cache_oblivious) {
		/*
		 * A nondeterministic seed based on the address of arena reduces
		 * the likelihood of lockstep non-uniform cache index
		 * utilization among identical concurrent processes, but at the
		 * cost of test repeatability.  For debug builds, instead use a
		 * deterministic seed.
		 */
		atomic_store_zu(&arena->offset_state, config_debug ? ind :
		    (size_t)(uintptr_t)arena, ATOMIC_RELAXED);
	}

	atomic_store_zu(&arena->extent_sn_next, 0, ATOMIC_RELAXED);

	atomic_store_u(&arena->dss_prec, (unsigned)extent_dss_prec_get(),
	    ATOMIC_RELAXED);

	atomic_store_zu(&arena->nactive, 0, ATOMIC_RELAXED);

	extent_list_init(&arena->large);
	if (malloc_mutex_init(&arena->large_mtx, "arena_large",
	    WITNESS_RANK_ARENA_LARGE, malloc_mutex_rank_exclusive)) {
		goto label_error;
	}

	/*
	 * Delay coalescing for dirty extents despite the disruptive effect on
	 * memory layout for best-fit extent allocation, since cached extents
	 * are likely to be reused soon after deallocation, and the cost of
	 * merging/splitting extents is non-trivial.
	 */
	if (extents_init(tsdn, &arena->extents_dirty, extent_state_dirty,
	    true)) {
		goto label_error;
	}
	/*
	 * Coalesce muzzy extents immediately, because operations on them are in
	 * the critical path much less often than for dirty extents.
	 */
	if (extents_init(tsdn, &arena->extents_muzzy, extent_state_muzzy,
	    false)) {
		goto label_error;
	}
	/*
	 * Coalesce retained extents immediately, in part because they will
	 * never be evicted (and therefore there's no opportunity for delayed
	 * coalescing), but also because operations on retained extents are not
	 * in the critical path.
	 */
	if (extents_init(tsdn, &arena->extents_retained, extent_state_retained,
	    false)) {
		goto label_error;
	}

	if (arena_decay_init(&arena->decay_dirty,
	    arena_dirty_decay_ms_default_get(), &arena->stats.decay_dirty)) {
		goto label_error;
	}
	if (arena_decay_init(&arena->decay_muzzy,
	    arena_muzzy_decay_ms_default_get(), &arena->stats.decay_muzzy)) {
		goto label_error;
	}

	arena->extent_grow_next = sz_psz2ind(HUGEPAGE);
	arena->retain_grow_limit = EXTENT_GROW_MAX_PIND;
	if (malloc_mutex_init(&arena->extent_grow_mtx, "extent_grow",
	    WITNESS_RANK_EXTENT_GROW, malloc_mutex_rank_exclusive)) {
		goto label_error;
	}

	extent_avail_new(&arena->extent_avail);
	if (malloc_mutex_init(&arena->extent_avail_mtx, "extent_avail",
	    WITNESS_RANK_EXTENT_AVAIL, malloc_mutex_rank_exclusive)) {
		goto label_error;
	}

	/* Initialize bins. */
	for (i = 0; i < NBINS; i++) {
		bool err = bin_init(&arena->bins[i]);
		if (err) {
			goto label_error;
		}
	}

	arena->base = base;
	/* Set arena before creating background threads. */
	arena_set(ind, arena);

	nstime_init(&arena->create_time, 0);
	nstime_update(&arena->create_time);

	/* We don't support reentrancy for arena 0 bootstrapping. */
	if (ind != 0) {
		/*
		 * If we're here, then arena 0 already exists, so bootstrapping
		 * is done enough that we should have tsd.
		 */
		assert(!tsdn_null(tsdn));
		pre_reentrancy(tsdn_tsd(tsdn), arena);
		if (hooks_arena_new_hook) {
			hooks_arena_new_hook();
		}
		post_reentrancy(tsdn_tsd(tsdn));
	}

	return arena;
label_error:
	if (ind != 0) {
		base_delete(tsdn, base);
	}
	return NULL;
}