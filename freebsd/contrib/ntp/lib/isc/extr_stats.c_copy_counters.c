#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int isc_uint64_t ;
struct TYPE_4__ {int ncounters; int* copiedcounters; int /*<<< orphan*/  counterlock; TYPE_2__* counters; } ;
typedef  TYPE_1__ isc_stats_t ;
typedef  int /*<<< orphan*/  isc_stat_t ;
struct TYPE_5__ {int lo; scalar_t__ hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  isc_rwlock_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_rwlock_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isc_rwlocktype_write ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_2__*,int) ; 

__attribute__((used)) static void
copy_counters(isc_stats_t *stats) {
	int i;

#ifdef ISC_RWLOCK_USEATOMIC
	/*
	 * We use a "write" lock before "reading" the statistics counters as
	 * an exclusive lock.
	 */
	isc_rwlock_lock(&stats->counterlock, isc_rwlocktype_write);
#endif

#if ISC_STATS_USEMULTIFIELDS
	for (i = 0; i < stats->ncounters; i++) {
		stats->copiedcounters[i] =
				(isc_uint64_t)(stats->counters[i].hi) << 32 |
				stats->counters[i].lo;
	}
#else
	UNUSED(i);
	memcpy(stats->copiedcounters, stats->counters,
	       stats->ncounters * sizeof(isc_stat_t));
#endif

#ifdef ISC_RWLOCK_USEATOMIC
	isc_rwlock_unlock(&stats->counterlock, isc_rwlocktype_write);
#endif
}