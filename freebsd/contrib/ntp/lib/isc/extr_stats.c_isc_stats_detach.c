#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ references; int ncounters; int /*<<< orphan*/  mctx; int /*<<< orphan*/  counterlock; int /*<<< orphan*/  lock; int /*<<< orphan*/  counters; int /*<<< orphan*/  copiedcounters; } ;
typedef  TYPE_1__ isc_stats_t ;
typedef  int /*<<< orphan*/  isc_stat_t ;

/* Variables and functions */
 int /*<<< orphan*/  DESTROYLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ ISC_STATS_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isc_mem_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  isc_mem_putanddetach (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  isc_rwlock_destroy (int /*<<< orphan*/ *) ; 

void
isc_stats_detach(isc_stats_t **statsp) {
	isc_stats_t *stats;

	REQUIRE(statsp != NULL && ISC_STATS_VALID(*statsp));

	stats = *statsp;
	*statsp = NULL;

	LOCK(&stats->lock);
	stats->references--;
	UNLOCK(&stats->lock);

	if (stats->references == 0) {
		isc_mem_put(stats->mctx, stats->copiedcounters,
			    sizeof(isc_stat_t) * stats->ncounters);
		isc_mem_put(stats->mctx, stats->counters,
			    sizeof(isc_stat_t) * stats->ncounters);
		DESTROYLOCK(&stats->lock);
#ifdef ISC_RWLOCK_USEATOMIC
		isc_rwlock_destroy(&stats->counterlock);
#endif
		isc_mem_putanddetach(&stats->mctx, stats, sizeof(*stats));
	}
}