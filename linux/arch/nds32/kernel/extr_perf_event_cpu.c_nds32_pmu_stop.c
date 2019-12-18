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
struct pmu_hw_events {int /*<<< orphan*/  pmu_lock; } ;
struct nds32_pmu {struct pmu_hw_events* (* get_hw_events ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NDS32_SR_PFM_CTL ; 
 unsigned int* PFM_CTL_EN ; 
 unsigned int* PFM_CTL_OVF ; 
 unsigned int __nds32__mfsr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __nds32__mtsr_isb (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct pmu_hw_events* stub1 () ; 

__attribute__((used)) static void nds32_pmu_stop(struct nds32_pmu *cpu_pmu)
{
	unsigned long flags;
	unsigned int val;
	struct pmu_hw_events *events = cpu_pmu->get_hw_events();

	raw_spin_lock_irqsave(&events->pmu_lock, flags);

	/* Disable all counters , NDS PFM has 3 counters */
	val = __nds32__mfsr(NDS32_SR_PFM_CTL);
	val &= ~(PFM_CTL_EN[0] | PFM_CTL_EN[1] | PFM_CTL_EN[2]);
	val &= ~(PFM_CTL_OVF[0] | PFM_CTL_OVF[1] | PFM_CTL_OVF[2]);
	__nds32__mtsr_isb(val, NDS32_SR_PFM_CTL);

	raw_spin_unlock_irqrestore(&events->pmu_lock, flags);
}