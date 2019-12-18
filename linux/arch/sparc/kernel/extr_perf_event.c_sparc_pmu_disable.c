#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct pmu {int dummy; } ;
struct cpu_hw_events {int* pcr; scalar_t__ n_added; scalar_t__ enabled; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* write_pcr ) (int,int) ;} ;
struct TYPE_3__ {int num_pcrs; int user_bit; int priv_bit; int hv_bit; int irq_bit; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 TYPE_2__* pcr_ops ; 
 TYPE_1__* sparc_pmu ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sparc_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	int i;

	if (!cpuc->enabled)
		return;

	cpuc->enabled = 0;
	cpuc->n_added = 0;

	for (i = 0; i < sparc_pmu->num_pcrs; i++) {
		u64 val = cpuc->pcr[i];

		val &= ~(sparc_pmu->user_bit | sparc_pmu->priv_bit |
			 sparc_pmu->hv_bit | sparc_pmu->irq_bit);
		cpuc->pcr[i] = val;
		pcr_ops->write_pcr(i, cpuc->pcr[i]);
	}
}