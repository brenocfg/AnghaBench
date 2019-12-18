#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dbsr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  BOOKE_INTERRUPT_CRITICAL 135 
#define  BOOKE_INTERRUPT_DEBUG 134 
#define  BOOKE_INTERRUPT_DECREMENTER 133 
#define  BOOKE_INTERRUPT_DOORBELL 132 
#define  BOOKE_INTERRUPT_EXTERNAL 131 
#define  BOOKE_INTERRUPT_MACHINE_CHECK 130 
#define  BOOKE_INTERRUPT_PERFORMANCE_MONITOR 129 
#define  BOOKE_INTERRUPT_WATCHDOG 128 
 int /*<<< orphan*/  SPRN_DBSR ; 
 int /*<<< orphan*/  WatchdogException (struct pt_regs*) ; 
 int /*<<< orphan*/  do_IRQ (struct pt_regs*) ; 
 int /*<<< orphan*/  doorbell_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  kvmppc_clear_dbsr () ; 
 int /*<<< orphan*/  kvmppc_fill_pt_regs (struct pt_regs*) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  performance_monitor_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  timer_interrupt (struct pt_regs*) ; 
 int /*<<< orphan*/  unknown_exception (struct pt_regs*) ; 

__attribute__((used)) static void kvmppc_restart_interrupt(struct kvm_vcpu *vcpu,
				     unsigned int exit_nr)
{
	struct pt_regs regs;

	switch (exit_nr) {
	case BOOKE_INTERRUPT_EXTERNAL:
		kvmppc_fill_pt_regs(&regs);
		do_IRQ(&regs);
		break;
	case BOOKE_INTERRUPT_DECREMENTER:
		kvmppc_fill_pt_regs(&regs);
		timer_interrupt(&regs);
		break;
#if defined(CONFIG_PPC_DOORBELL)
	case BOOKE_INTERRUPT_DOORBELL:
		kvmppc_fill_pt_regs(&regs);
		doorbell_exception(&regs);
		break;
#endif
	case BOOKE_INTERRUPT_MACHINE_CHECK:
		/* FIXME */
		break;
	case BOOKE_INTERRUPT_PERFORMANCE_MONITOR:
		kvmppc_fill_pt_regs(&regs);
		performance_monitor_exception(&regs);
		break;
	case BOOKE_INTERRUPT_WATCHDOG:
		kvmppc_fill_pt_regs(&regs);
#ifdef CONFIG_BOOKE_WDT
		WatchdogException(&regs);
#else
		unknown_exception(&regs);
#endif
		break;
	case BOOKE_INTERRUPT_CRITICAL:
		kvmppc_fill_pt_regs(&regs);
		unknown_exception(&regs);
		break;
	case BOOKE_INTERRUPT_DEBUG:
		/* Save DBSR before preemption is enabled */
		vcpu->arch.dbsr = mfspr(SPRN_DBSR);
		kvmppc_clear_dbsr();
		break;
	}
}