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
 int /*<<< orphan*/  MIPS_IRQ_MBOX0 ; 
 int /*<<< orphan*/  MIPS_IRQ_MBOX1 ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  paravirt_function_interrupt ; 
 int /*<<< orphan*/  paravirt_reched_interrupt ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void paravirt_prepare_cpus(unsigned int max_cpus)
{
	if (request_irq(MIPS_IRQ_MBOX0, paravirt_reched_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "Scheduler",
			paravirt_reched_interrupt)) {
		panic("Cannot request_irq for SchedulerIPI");
	}
	if (request_irq(MIPS_IRQ_MBOX1, paravirt_function_interrupt,
			IRQF_PERCPU | IRQF_NO_THREAD, "SMP-Call",
			paravirt_function_interrupt)) {
		panic("Cannot request_irq for SMP-Call");
	}
}