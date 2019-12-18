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
struct perf_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOFTWARE_EVENT_MASK ; 
 int /*<<< orphan*/  nds32_pfm_perf_cache_map ; 
 int /*<<< orphan*/  nds32_pfm_perf_map ; 
 int nds32_pmu_map_event (struct perf_event*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nds32_spav3_map_event(struct perf_event *event)
{
	return nds32_pmu_map_event(event, &nds32_pfm_perf_map,
				&nds32_pfm_perf_cache_map, SOFTWARE_EVENT_MASK);
}