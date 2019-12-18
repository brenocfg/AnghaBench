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
typedef  unsigned int irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  do_IPI ; 
 int /*<<< orphan*/  enable_percpu_irq (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipi_dev ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  panic (char*,unsigned int) ; 
 int* per_cpu_ptr (int /*<<< orphan*/ *,int) ; 
 int request_percpu_irq (unsigned int,int /*<<< orphan*/ ,char*,int*) ; 

int smp_ipi_irq_setup(int cpu, irq_hw_number_t hwirq)
{
	int *dev = per_cpu_ptr(&ipi_dev, cpu);
	unsigned int virq = irq_find_mapping(NULL, hwirq);

	if (!virq)
		panic("Cannot find virq for root domain and hwirq=%lu", hwirq);

	/* Boot cpu calls request, all call enable */
	if (!cpu) {
		int rc;

		rc = request_percpu_irq(virq, do_IPI, "IPI Interrupt", dev);
		if (rc)
			panic("Percpu IRQ request failed for %u\n", virq);
	}

	enable_percpu_irq(virq, 0);

	return 0;
}