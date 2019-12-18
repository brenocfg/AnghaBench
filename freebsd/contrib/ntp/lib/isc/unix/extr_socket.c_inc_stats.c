#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int isc_statscounter_t ;
typedef  int /*<<< orphan*/  isc_stats_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  isc_stats_increment (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void
inc_stats(isc_stats_t *stats, isc_statscounter_t counterid) {
	REQUIRE(counterid != -1);

	if (stats != NULL)
		isc_stats_increment(stats, counterid);
}