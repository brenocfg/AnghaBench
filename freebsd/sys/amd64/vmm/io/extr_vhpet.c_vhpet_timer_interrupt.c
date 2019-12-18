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
struct vhpet {int isr; int /*<<< orphan*/  vm; TYPE_1__* timer; } ;
struct TYPE_2__ {int msireg; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  lapic_intr_msi (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ vhpet_timer_edge_trig (struct vhpet*,int) ; 
 int /*<<< orphan*/  vhpet_timer_interrupt_enabled (struct vhpet*,int) ; 
 int vhpet_timer_ioapic_pin (struct vhpet*,int) ; 
 scalar_t__ vhpet_timer_msi_enabled (struct vhpet*,int) ; 
 int /*<<< orphan*/  vioapic_assert_irq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vioapic_pulse_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vhpet_timer_interrupt(struct vhpet *vhpet, int n)
{
	int pin;

	/* If interrupts are not enabled for this timer then just return. */
	if (!vhpet_timer_interrupt_enabled(vhpet, n))
		return;

	/*
	 * If a level triggered interrupt is already asserted then just return.
	 */
	if ((vhpet->isr & (1 << n)) != 0) {
		VM_CTR1(vhpet->vm, "hpet t%d intr is already asserted", n);
		return;
	}

	if (vhpet_timer_msi_enabled(vhpet, n)) {
		lapic_intr_msi(vhpet->vm, vhpet->timer[n].msireg >> 32,
		    vhpet->timer[n].msireg & 0xffffffff);
		return;
	}	

	pin = vhpet_timer_ioapic_pin(vhpet, n);
	if (pin == 0) {
		VM_CTR1(vhpet->vm, "hpet t%d intr is not routed to ioapic", n);
		return;
	}

	if (vhpet_timer_edge_trig(vhpet, n)) {
		vioapic_pulse_irq(vhpet->vm, pin);
	} else {
		vhpet->isr |= 1 << n;
		vioapic_assert_irq(vhpet->vm, pin);
	}
}