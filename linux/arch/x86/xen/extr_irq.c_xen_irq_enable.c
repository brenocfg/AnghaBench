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
struct vcpu_info {int /*<<< orphan*/  evtchn_upcall_pending; scalar_t__ evtchn_upcall_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 struct vcpu_info* this_cpu_read (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_force_evtchn_callback () ; 
 int /*<<< orphan*/  xen_vcpu ; 

void xen_irq_enable(void)
{
	struct vcpu_info *vcpu;

	/*
	 * We may be preempted as soon as vcpu->evtchn_upcall_mask is
	 * cleared, so disable preemption to ensure we check for
	 * events on the VCPU we are still running on.
	 */
	preempt_disable();

	vcpu = this_cpu_read(xen_vcpu);
	vcpu->evtchn_upcall_mask = 0;

	/* Doesn't matter if we get preempted here, because any
	   pending event will get dealt with anyway. */

	barrier(); /* unmask then check (avoid races) */
	if (unlikely(vcpu->evtchn_upcall_pending))
		xen_force_evtchn_callback();

	preempt_enable();
}