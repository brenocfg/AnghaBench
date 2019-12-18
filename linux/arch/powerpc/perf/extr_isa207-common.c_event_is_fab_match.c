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
typedef  int u64 ;

/* Variables and functions */

__attribute__((used)) static inline bool event_is_fab_match(u64 event)
{
	/* Only check pmc, unit and pmcxsel, ignore the edge bit (0) */
	event &= 0xff0fe;

	/* PM_MRK_FAB_RSP_MATCH & PM_MRK_FAB_RSP_MATCH_CYC */
	return (event == 0x30056 || event == 0x4f052);
}