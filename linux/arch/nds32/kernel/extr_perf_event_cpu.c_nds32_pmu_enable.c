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
struct pmu_hw_events {int /*<<< orphan*/  used_mask; } ;
struct pmu {int dummy; } ;
struct nds32_pmu {int /*<<< orphan*/  (* start ) (struct nds32_pmu*) ;int /*<<< orphan*/  num_events; struct pmu_hw_events* (* get_hw_events ) () ;} ;

/* Variables and functions */
 int bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pmu_hw_events* stub1 () ; 
 int /*<<< orphan*/  stub2 (struct nds32_pmu*) ; 
 struct nds32_pmu* to_nds32_pmu (struct pmu*) ; 

__attribute__((used)) static void nds32_pmu_enable(struct pmu *pmu)
{
	struct nds32_pmu *nds32_pmu = to_nds32_pmu(pmu);
	struct pmu_hw_events *hw_events = nds32_pmu->get_hw_events();
	int enabled = bitmap_weight(hw_events->used_mask,
				    nds32_pmu->num_events);

	if (enabled)
		nds32_pmu->start(nds32_pmu);
}