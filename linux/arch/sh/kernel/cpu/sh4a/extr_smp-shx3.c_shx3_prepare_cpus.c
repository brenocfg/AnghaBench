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
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  IRQF_PERCPU ; 
 int SMP_MSG_NR ; 
 int /*<<< orphan*/  ipi_interrupt_handler ; 
 int /*<<< orphan*/  request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  set_cpu_present (int,int) ; 

__attribute__((used)) static void shx3_prepare_cpus(unsigned int max_cpus)
{
	int i;

	BUILD_BUG_ON(SMP_MSG_NR >= 8);

	for (i = 0; i < SMP_MSG_NR; i++)
		request_irq(104 + i, ipi_interrupt_handler,
			    IRQF_PERCPU, "IPI", (void *)(long)i);

	for (i = 0; i < max_cpus; i++)
		set_cpu_present(i, true);
}