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

/* Variables and functions */
 int IRQF_NO_THREAD ; 
 int IRQF_PERCPU ; 
 scalar_t__ OCTEON_IRQ_MBOX0 ; 
 int /*<<< orphan*/  octeon_78xx_call_function_interrupt ; 
 int /*<<< orphan*/  octeon_78xx_icache_flush_interrupt ; 
 int /*<<< orphan*/  octeon_78xx_reched_interrupt ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ request_irq (scalar_t__,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void octeon_78xx_prepare_cpus(unsigned int max_cpus)
{
	if (request_irq(OCTEON_IRQ_MBOX0 + 0,
			octeon_78xx_reched_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "Scheduler",
			octeon_78xx_reched_interrupt)) {
		panic("Cannot request_irq for SchedulerIPI");
	}
	if (request_irq(OCTEON_IRQ_MBOX0 + 1,
			octeon_78xx_call_function_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-Call",
			octeon_78xx_call_function_interrupt)) {
		panic("Cannot request_irq for SMP-Call");
	}
	if (request_irq(OCTEON_IRQ_MBOX0 + 2,
			octeon_78xx_icache_flush_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "ICache-Flush",
			octeon_78xx_icache_flush_interrupt)) {
		panic("Cannot request_irq for ICache-Flush");
	}
}