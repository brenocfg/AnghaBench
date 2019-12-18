#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_lapic {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  auto_eoi_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  __apic_update_ppr (struct kvm_lapic*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  apic_clear_irr (int,struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_set_isr (int,struct kvm_lapic*) ; 
 int /*<<< orphan*/  apic_update_ppr (struct kvm_lapic*) ; 
 int kvm_apic_has_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* vcpu_to_synic (struct kvm_vcpu*) ; 

int kvm_get_apic_interrupt(struct kvm_vcpu *vcpu)
{
	int vector = kvm_apic_has_interrupt(vcpu);
	struct kvm_lapic *apic = vcpu->arch.apic;
	u32 ppr;

	if (vector == -1)
		return -1;

	/*
	 * We get here even with APIC virtualization enabled, if doing
	 * nested virtualization and L1 runs with the "acknowledge interrupt
	 * on exit" mode.  Then we cannot inject the interrupt via RVI,
	 * because the process would deliver it through the IDT.
	 */

	apic_clear_irr(vector, apic);
	if (test_bit(vector, vcpu_to_synic(vcpu)->auto_eoi_bitmap)) {
		/*
		 * For auto-EOI interrupts, there might be another pending
		 * interrupt above PPR, so check whether to raise another
		 * KVM_REQ_EVENT.
		 */
		apic_update_ppr(apic);
	} else {
		/*
		 * For normal interrupts, PPR has been raised and there cannot
		 * be a higher-priority pending interrupt---except if there was
		 * a concurrent interrupt injection, but that would have
		 * triggered KVM_REQ_EVENT already.
		 */
		apic_set_isr(vector, apic);
		__apic_update_ppr(apic, &ppr);
	}

	return vector;
}