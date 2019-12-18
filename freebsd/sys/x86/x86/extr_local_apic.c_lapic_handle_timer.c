#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct trapframe {int dummy; } ;
struct thread {int /*<<< orphan*/  td_intr_nesting_level; struct trapframe* td_intr_frame; } ;
struct lapic {int /*<<< orphan*/ * la_timer_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  et_arg; int /*<<< orphan*/  (* et_event_cb ) (TYPE_1__*,int /*<<< orphan*/ ) ;scalar_t__ et_active; } ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (size_t,int /*<<< orphan*/ *) ; 
 size_t PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apic_id ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  hlt_cpus_mask ; 
 int /*<<< orphan*/  lapic_eoi () ; 
 TYPE_1__ lapic_et ; 
 struct lapic* lapics ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 

void
lapic_handle_timer(struct trapframe *frame)
{
	struct lapic *la;
	struct trapframe *oldframe;
	struct thread *td;

	/* Send EOI first thing. */
	lapic_eoi();

#if defined(SMP) && !defined(SCHED_ULE)
	/*
	 * Don't do any accounting for the disabled HTT cores, since it
	 * will provide misleading numbers for the userland.
	 *
	 * No locking is necessary here, since even if we lose the race
	 * when hlt_cpus_mask changes it is not a big deal, really.
	 *
	 * Don't do that for ULE, since ULE doesn't consider hlt_cpus_mask
	 * and unlike other schedulers it actually schedules threads to
	 * those CPUs.
	 */
	if (CPU_ISSET(PCPU_GET(cpuid), &hlt_cpus_mask))
		return;
#endif

	/* Look up our local APIC structure for the tick counters. */
	la = &lapics[PCPU_GET(apic_id)];
	(*la->la_timer_count)++;
	critical_enter();
	if (lapic_et.et_active) {
		td = curthread;
		td->td_intr_nesting_level++;
		oldframe = td->td_intr_frame;
		td->td_intr_frame = frame;
		lapic_et.et_event_cb(&lapic_et, lapic_et.et_arg);
		td->td_intr_frame = oldframe;
		td->td_intr_nesting_level--;
	}
	critical_exit();
}