#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  eset_muzzy; int /*<<< orphan*/  eset_dirty; int /*<<< orphan*/  nactive; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  arena_dirty_decay_ms_get (TYPE_1__*) ; 
 size_t arena_dss_prec_get (TYPE_1__*) ; 
 int /*<<< orphan*/  arena_muzzy_decay_ms_get (TYPE_1__*) ; 
 scalar_t__ arena_nthreads_get (TYPE_1__*,int) ; 
 scalar_t__ atomic_load_zu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char** dss_prec_names ; 
 scalar_t__ eset_npages_get (int /*<<< orphan*/ *) ; 

void
arena_basic_stats_merge(tsdn_t *tsdn, arena_t *arena, unsigned *nthreads,
    const char **dss, ssize_t *dirty_decay_ms, ssize_t *muzzy_decay_ms,
    size_t *nactive, size_t *ndirty, size_t *nmuzzy) {
	*nthreads += arena_nthreads_get(arena, false);
	*dss = dss_prec_names[arena_dss_prec_get(arena)];
	*dirty_decay_ms = arena_dirty_decay_ms_get(arena);
	*muzzy_decay_ms = arena_muzzy_decay_ms_get(arena);
	*nactive += atomic_load_zu(&arena->nactive, ATOMIC_RELAXED);
	*ndirty += eset_npages_get(&arena->eset_dirty);
	*nmuzzy += eset_npages_get(&arena->eset_muzzy);
}