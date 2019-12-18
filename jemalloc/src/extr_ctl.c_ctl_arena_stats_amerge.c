#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tsdn_t ;
struct TYPE_6__ {int /*<<< orphan*/  pmuzzy; int /*<<< orphan*/  pdirty; int /*<<< orphan*/  pactive; int /*<<< orphan*/  muzzy_decay_ms; int /*<<< orphan*/  dirty_decay_ms; int /*<<< orphan*/  dss; int /*<<< orphan*/  nthreads; TYPE_1__* astats; } ;
typedef  TYPE_2__ ctl_arena_t ;
typedef  int /*<<< orphan*/  arena_t ;
struct TYPE_7__ {int curregs; scalar_t__ nflushes; scalar_t__ nfills; scalar_t__ nrequests; scalar_t__ ndalloc; scalar_t__ nmalloc; } ;
struct TYPE_5__ {int allocated_small; TYPE_4__* bstats; int /*<<< orphan*/  nflushes_small; int /*<<< orphan*/  nfills_small; int /*<<< orphan*/  nrequests_small; int /*<<< orphan*/  ndalloc_small; int /*<<< orphan*/  nmalloc_small; int /*<<< orphan*/  estats; int /*<<< orphan*/  lstats; int /*<<< orphan*/  astats; } ;

/* Variables and functions */
 unsigned int SC_NBINS ; 
 int /*<<< orphan*/  arena_basic_stats_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arena_stats_merge (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ config_stats ; 
 int sz_index2size (unsigned int) ; 

__attribute__((used)) static void
ctl_arena_stats_amerge(tsdn_t *tsdn, ctl_arena_t *ctl_arena, arena_t *arena) {
	unsigned i;

	if (config_stats) {
		arena_stats_merge(tsdn, arena, &ctl_arena->nthreads,
		    &ctl_arena->dss, &ctl_arena->dirty_decay_ms,
		    &ctl_arena->muzzy_decay_ms, &ctl_arena->pactive,
		    &ctl_arena->pdirty, &ctl_arena->pmuzzy,
		    &ctl_arena->astats->astats, ctl_arena->astats->bstats,
		    ctl_arena->astats->lstats, ctl_arena->astats->estats);

		for (i = 0; i < SC_NBINS; i++) {
			ctl_arena->astats->allocated_small +=
			    ctl_arena->astats->bstats[i].curregs *
			    sz_index2size(i);
			ctl_arena->astats->nmalloc_small +=
			    ctl_arena->astats->bstats[i].nmalloc;
			ctl_arena->astats->ndalloc_small +=
			    ctl_arena->astats->bstats[i].ndalloc;
			ctl_arena->astats->nrequests_small +=
			    ctl_arena->astats->bstats[i].nrequests;
			ctl_arena->astats->nfills_small +=
			    ctl_arena->astats->bstats[i].nfills;
			ctl_arena->astats->nflushes_small +=
			    ctl_arena->astats->bstats[i].nflushes;
		}
	} else {
		arena_basic_stats_merge(tsdn, arena, &ctl_arena->nthreads,
		    &ctl_arena->dss, &ctl_arena->dirty_decay_ms,
		    &ctl_arena->muzzy_decay_ms, &ctl_arena->pactive,
		    &ctl_arena->pdirty, &ctl_arena->pmuzzy);
	}
}