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
typedef  int /*<<< orphan*/  isc_statscounter_t ;
struct TYPE_5__ {int ncounters; scalar_t__* copiedcounters; } ;
typedef  TYPE_1__ isc_stats_t ;
typedef  int /*<<< orphan*/  (* isc_stats_dumper_t ) (int /*<<< orphan*/ ,scalar_t__,void*) ;

/* Variables and functions */
 unsigned int ISC_STATSDUMP_VERBOSE ; 
 int /*<<< orphan*/  ISC_STATS_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_counters (TYPE_1__*) ; 

void
isc_stats_dump(isc_stats_t *stats, isc_stats_dumper_t dump_fn,
	       void *arg, unsigned int options)
{
	int i;

	REQUIRE(ISC_STATS_VALID(stats));

	copy_counters(stats);

	for (i = 0; i < stats->ncounters; i++) {
		if ((options & ISC_STATSDUMP_VERBOSE) == 0 &&
		    stats->copiedcounters[i] == 0)
				continue;
		dump_fn((isc_statscounter_t)i, stats->copiedcounters[i], arg);
	}
}