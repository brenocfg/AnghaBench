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
 int /*<<< orphan*/  CONFIG_KEXEC_CORE ; 
#define  IPI_CALL_FUNC 134 
#define  IPI_CPU_CRASH_STOP 133 
#define  IPI_CPU_STOP 132 
#define  IPI_IRQ_WORK 131 
#define  IPI_RESCHEDULE 130 
#define  IPI_TIMER 129 
#define  IPI_WAKEUP 128 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int NR_IPI ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,unsigned int) ; 
 int /*<<< orphan*/  __inc_irq_stat (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_parking_protocol_valid (unsigned int) ; 
 int /*<<< orphan*/  generic_smp_call_function_interrupt () ; 
 int /*<<< orphan*/  ipi_cpu_crash_stop (unsigned int,struct pt_regs*) ; 
 int /*<<< orphan*/ * ipi_irqs ; 
 int /*<<< orphan*/ * ipi_types ; 
 int /*<<< orphan*/  irq_enter () ; 
 int /*<<< orphan*/  irq_exit () ; 
 int /*<<< orphan*/  irq_work_run () ; 
 int /*<<< orphan*/  local_cpu_stop () ; 
 int /*<<< orphan*/  pr_crit (char*,unsigned int,int) ; 
 int /*<<< orphan*/  scheduler_ipi () ; 
 struct pt_regs* set_irq_regs (struct pt_regs*) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  tick_receive_broadcast () ; 
 int /*<<< orphan*/  trace_ipi_entry_rcuidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_ipi_exit_rcuidle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unreachable () ; 

void handle_IPI(int ipinr, struct pt_regs *regs)
{
	unsigned int cpu = smp_processor_id();
	struct pt_regs *old_regs = set_irq_regs(regs);

	if ((unsigned)ipinr < NR_IPI) {
		trace_ipi_entry_rcuidle(ipi_types[ipinr]);
		__inc_irq_stat(cpu, ipi_irqs[ipinr]);
	}

	switch (ipinr) {
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
		local_cpu_stop();
		irq_exit();
		break;

	case IPI_CPU_CRASH_STOP:
		if (IS_ENABLED(CONFIG_KEXEC_CORE)) {
			irq_enter();
			ipi_cpu_crash_stop(cpu, regs);

			unreachable();
		}
		break;

#ifdef CONFIG_GENERIC_CLOCKEVENTS_BROADCAST
	case IPI_TIMER:
		irq_enter();
		tick_receive_broadcast();
		irq_exit();
		break;
#endif

#ifdef CONFIG_IRQ_WORK
	case IPI_IRQ_WORK:
		irq_enter();
		irq_work_run();
		irq_exit();
		break;
#endif

#ifdef CONFIG_ARM64_ACPI_PARKING_PROTOCOL
	case IPI_WAKEUP:
		WARN_ONCE(!acpi_parking_protocol_valid(cpu),
			  "CPU%u: Wake-up IPI outside the ACPI parking protocol\n",
			  cpu);
		break;
#endif

	default:
		pr_crit("CPU%u: Unknown IPI message 0x%x\n", cpu, ipinr);
		break;
	}

	if ((unsigned)ipinr < NR_IPI)
		trace_ipi_exit_rcuidle(ipi_types[ipinr]);
	set_irq_regs(old_regs);
}