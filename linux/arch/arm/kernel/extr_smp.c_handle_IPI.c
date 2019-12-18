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
struct pt_regs {int dummy; } ;

/* Variables and functions */
#define  IPI_CALL_FUNC 135 
#define  IPI_COMPLETION 134 
#define  IPI_CPU_BACKTRACE 133 
#define  IPI_CPU_STOP 132 
#define  IPI_IRQ_WORK 131 
#define  IPI_RESCHEDULE 130 
#define  IPI_TIMER 129 
#define  IPI_WAKEUP 128 
 unsigned int NR_IPI ; 
 int /*<<< orphan*/  __inc_irq_stat (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  ipi_complete (unsigned int) ; 
 int /*<<< orphan*/  ipi_cpu_stop (unsigned int) ; 
 int /*<<< orphan*/ * ipi_irqs ; 
 int /*<<< orphan*/ * ipi_types ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  irq_work_run () ; 
 int /*<<< orphan*/  nmi_cpu_backtrace (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_crit (char*,unsigned int,int) ; 
 int /*<<< orphan*/  printk_nmi_enter () ; 
 int /*<<< orphan*/  printk_nmi_exit () ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  tick_receive_broadcast () ; 
 int /*<<< orphan*/  trace_ipi_entry_rcuidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ipi_exit_rcuidle (int /*<<< orphan*/ ) ; 

void handle_IPI(int ipinr, struct pt_regs *regs)
{
	unsigned int cpu = smp_processor_id();
	struct pt_regs *old_regs = set_irq_regs(regs);

	if ((unsigned)ipinr < NR_IPI) {
		trace_ipi_entry_rcuidle(ipi_types[ipinr]);
		__inc_irq_stat(cpu, ipi_irqs[ipinr]);
	}

	switch (ipinr) {
	case IPI_WAKEUP:
		break;

#ifdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	case IPI_TIMER:
		irq_enter();
		tick_receive_broadcast();
		irq_exit();
		break;
#endif

	case IPI_RESCHEDULE:
		scheduler_ipi();
		break;

	case IPI_CALL_FUNC:
		irq_enter();
		generic_smp_call_function_interrupt();
		irq_exit();
		break;

	case IPI_CPU_STOP:
		irq_enter();
		ipi_cpu_stop(cpu);
		irq_exit();
		break;

#ifdef CONFIG_IRQ_WORK
	case IPI_IRQ_WORK:
		irq_enter();
		irq_work_run();
		irq_exit();
		break;
#endif

	case IPI_COMPLETION:
		irq_enter();
		ipi_complete(cpu);
		irq_exit();
		break;

	case IPI_CPU_BACKTRACE:
		printk_nmi_enter();
		irq_enter();
		nmi_cpu_backtrace(regs);
		irq_exit();
		printk_nmi_exit();
		break;

	default:
		pr_crit("CPU%u: Unknown IPI message 0x%x\n",
		        cpu, ipinr);
		break;
	}

	if ((unsigned)ipinr < NR_IPI)
		trace_ipi_exit_rcuidle(ipi_types[ipinr]);
	set_irq_regs(old_regs);
}