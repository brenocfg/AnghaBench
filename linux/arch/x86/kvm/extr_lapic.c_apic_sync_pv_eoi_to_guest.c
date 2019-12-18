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
struct kvm_vcpu {int dummy; } ;
struct kvm_lapic {int highest_isr_cache; int /*<<< orphan*/  vcpu; scalar_t__ irr_pending; } ;

/* Variables and functions */
 scalar_t__ kvm_ioapic_handles_vector (struct kvm_lapic*,int) ; 
 int /*<<< orphan*/  pv_eoi_enabled (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pv_eoi_set_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apic_sync_pv_eoi_to_guest(struct kvm_vcpu *vcpu,
					struct kvm_lapic *apic)
{
	if (!pv_eoi_enabled(vcpu) ||
	    /* IRR set or many bits in ISR: could be nested. */
	    apic->irr_pending ||
	    /* Cache not set: could be safe but we don't bother. */
	    apic->highest_isr_cache == -1 ||
	    /* Need EOI to update ioapic. */
	    kvm_ioapic_handles_vector(apic, apic->highest_isr_cache)) {
		/*
		 * PV EOI was disabled by apic_sync_pv_eoi_from_guest
		 * so we need not do anything here.
		 */
		return;
	}

	pv_eoi_set_pending(apic->vcpu);
}