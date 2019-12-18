#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ncounters; } ;
typedef  TYPE_1__ isc_stats_t ;

/* Variables and functions */
 int /*<<< orphan*/  ISC_STATS_VALID (TYPE_1__*) ; 
 int /*<<< orphan*/  REQUIRE (int /*<<< orphan*/ ) ; 

int
isc_stats_ncounters(isc_stats_t *stats) {
	REQUIRE(ISC_STATS_VALID(stats));

	return (stats->ncounters);
}