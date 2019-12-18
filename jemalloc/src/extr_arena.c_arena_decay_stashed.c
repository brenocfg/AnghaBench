#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  extent_t ;
typedef  int /*<<< orphan*/  extent_list_t ;
typedef  int /*<<< orphan*/  extent_hooks_t ;
typedef  int /*<<< orphan*/  eset_t ;
struct TYPE_18__ {int /*<<< orphan*/  mapped; } ;
struct TYPE_16__ {TYPE_7__ stats; int /*<<< orphan*/  eset_muzzy; } ;
typedef  TYPE_2__ arena_t ;
struct TYPE_17__ {TYPE_1__* stats; } ;
typedef  TYPE_3__ arena_decay_t ;
struct TYPE_15__ {int /*<<< orphan*/  purged; int /*<<< orphan*/  nmadvise; int /*<<< orphan*/  npurge; } ;

/* Variables and functions */
 int /*<<< orphan*/  JEMALLOC_FALLTHROUGH ; 
 size_t LG_PAGE ; 
 int /*<<< orphan*/  arena_background_thread_inactivity_check (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  arena_muzzy_decay_ms_get (TYPE_2__*) ; 
 int /*<<< orphan*/  arena_stats_add_u64 (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  arena_stats_lock (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  arena_stats_sub_zu (int /*<<< orphan*/ *,TYPE_7__*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  arena_stats_unlock (int /*<<< orphan*/ *,TYPE_7__*) ; 
 scalar_t__ config_stats ; 
 int eset_state_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_dalloc_wrapper (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * extent_list_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_list_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  extent_purge_lazy_wrapper (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 size_t extent_size_get (int /*<<< orphan*/ *) ; 
#define  extent_state_active 131 
#define  extent_state_dirty 130 
#define  extent_state_muzzy 129 
#define  extent_state_retained 128 
 int /*<<< orphan*/  extents_dalloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  not_reached () ; 

__attribute__((used)) static size_t
arena_decay_stashed(tsdn_t *tsdn, arena_t *arena,
    extent_hooks_t **r_extent_hooks, arena_decay_t *decay, eset_t *eset,
    bool all, extent_list_t *decay_extents, bool is_background_thread) {
	size_t nmadvise, nunmapped;
	size_t npurged;

	if (config_stats) {
		nmadvise = 0;
		nunmapped = 0;
	}
	npurged = 0;

	ssize_t muzzy_decay_ms = arena_muzzy_decay_ms_get(arena);
	for (extent_t *extent = extent_list_first(decay_extents); extent !=
	    NULL; extent = extent_list_first(decay_extents)) {
		if (config_stats) {
			nmadvise++;
		}
		size_t npages = extent_size_get(extent) >> LG_PAGE;
		npurged += npages;
		extent_list_remove(decay_extents, extent);
		switch (eset_state_get(eset)) {
		case extent_state_active:
			not_reached();
		case extent_state_dirty:
			if (!all && muzzy_decay_ms != 0 &&
			    !extent_purge_lazy_wrapper(tsdn, arena,
			    r_extent_hooks, extent, 0,
			    extent_size_get(extent))) {
				extents_dalloc(tsdn, arena, r_extent_hooks,
				    &arena->eset_muzzy, extent);
				arena_background_thread_inactivity_check(tsdn,
				    arena, is_background_thread);
				break;
			}
			JEMALLOC_FALLTHROUGH;
		case extent_state_muzzy:
			extent_dalloc_wrapper(tsdn, arena, r_extent_hooks,
			    extent);
			if (config_stats) {
				nunmapped += npages;
			}
			break;
		case extent_state_retained:
		default:
			not_reached();
		}
	}

	if (config_stats) {
		arena_stats_lock(tsdn, &arena->stats);
		arena_stats_add_u64(tsdn, &arena->stats, &decay->stats->npurge,
		    1);
		arena_stats_add_u64(tsdn, &arena->stats,
		    &decay->stats->nmadvise, nmadvise);
		arena_stats_add_u64(tsdn, &arena->stats, &decay->stats->purged,
		    npurged);
		arena_stats_sub_zu(tsdn, &arena->stats, &arena->stats.mapped,
		    nunmapped << LG_PAGE);
		arena_stats_unlock(tsdn, &arena->stats);
	}

	return npurged;
}