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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int IPI_IRQ_OFFSET ; 
 unsigned int SMP_ASK_C0COUNT ; 
 unsigned int SMP_CALL_FUNCTION ; 
 unsigned int SMP_RESCHEDULE_YOURSELF ; 
 int /*<<< orphan*/  __wbflush () ; 
 unsigned int* core0_c0count ; 
 size_t cpu_logical_map (int) ; 
 int /*<<< orphan*/  do_IRQ (int) ; 
 int ffs (unsigned int) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/ * ipi_clear0_regs ; 
 int /*<<< orphan*/ * ipi_status0_regs ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 unsigned int loongson3_ipi_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  loongson3_ipi_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_cpu_ids ; 
 unsigned int read_c0_count () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 int smp_processor_id () ; 

void loongson3_ipi_interrupt(struct pt_regs *regs)
{
	int i, cpu = smp_processor_id();
	unsigned int action, c0count, irqs;

	/* Load the ipi register to figure out what we're supposed to do */
	action = loongson3_ipi_read32(ipi_status0_regs[cpu_logical_map(cpu)]);
	irqs = action >> IPI_IRQ_OFFSET;

	/* Clear the ipi register to clear the interrupt */
	loongson3_ipi_write32((u32)action, ipi_clear0_regs[cpu_logical_map(cpu)]);

	if (action & SMP_RESCHEDULE_YOURSELF)
		scheduler_ipi();

	if (action & SMP_CALL_FUNCTION) {
		irq_enter();
		generic_smp_call_function_interrupt();
		irq_exit();
	}

	if (action & SMP_ASK_C0COUNT) {
		BUG_ON(cpu != 0);
		c0count = read_c0_count();
		c0count = c0count ? c0count : 1;
		for (i = 1; i < nr_cpu_ids; i++)
			core0_c0count[i] = c0count;
		__wbflush(); /* Let others see the result ASAP */
	}

	if (irqs) {
		int irq;
		while ((irq = ffs(irqs))) {
			do_IRQ(irq-1);
			irqs &= ~(1<<(irq-1));
		}
	}
}