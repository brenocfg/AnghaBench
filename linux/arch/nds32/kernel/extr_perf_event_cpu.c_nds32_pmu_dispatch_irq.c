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
typedef  scalar_t__ u64 ;
struct nds32_pmu {int (* handle_irq ) (int,void*) ;} ;
typedef  int irqreturn_t ;

/* Variables and functions */
 scalar_t__ local_clock () ; 
 int /*<<< orphan*/  perf_sample_event_took (scalar_t__) ; 
 int stub1 (int,void*) ; 

__attribute__((used)) static irqreturn_t nds32_pmu_dispatch_irq(int irq, void *dev)
{
	struct nds32_pmu *nds32_pmu = (struct nds32_pmu *)dev;
	int ret;
	u64 start_clock, finish_clock;

	start_clock = local_clock();
	ret = nds32_pmu->handle_irq(irq, dev);
	finish_clock = local_clock();

	perf_sample_event_took(finish_clock - start_clock);
	return ret;
}