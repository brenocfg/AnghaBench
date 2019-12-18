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
struct nds32_pmu {int num_events; } ;

/* Variables and functions */

__attribute__((used)) static inline int nds32_pfm_counter_valid(struct nds32_pmu *cpu_pmu, int idx)
{
	return ((idx >= 0) && (idx < cpu_pmu->num_events));
}