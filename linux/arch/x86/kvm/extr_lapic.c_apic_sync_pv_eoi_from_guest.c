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
struct kvm_lapic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int apic_set_eoi (struct kvm_lapic*) ; 
 int /*<<< orphan*/  pv_eoi_clr_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pv_eoi_enabled (struct kvm_vcpu*) ; 
 int pv_eoi_get_pending (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_pv_eoi (struct kvm_lapic*,int) ; 

__attribute__((used)) static void apic_sync_pv_eoi_from_guest(struct kvm_vcpu *vcpu,
					struct kvm_lapic *apic)
{
	bool pending;
	int vector;
	/*
	 * PV EOI state is derived from KVM_APIC_PV_EOI_PENDING in host
	 * and KVM_PV_EOI_ENABLED in guest memory as follows:
	 *
	 * KVM_APIC_PV_EOI_PENDING is unset:
	 * 	-> host disabled PV EOI.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABLED is set:
	 * 	-> host enabled PV EOI, guest did not execute EOI yet.
	 * KVM_APIC_PV_EOI_PENDING is set, KVM_PV_EOI_ENABLED is unset:
	 * 	-> host enabled PV EOI, guest executed EOI.
	 */
	BUG_ON(!pv_eoi_enabled(vcpu));
	pending = pv_eoi_get_pending(vcpu);
	/*
	 * Clear pending bit in any case: it will be set again on vmentry.
	 * While this might not be ideal from performance point of view,
	 * this makes sure pv eoi is only enabled when we know it's safe.
	 */
	pv_eoi_clr_pending(vcpu);
	if (pending)
		return;
	vector = apic_set_eoi(apic);
	trace_kvm_pv_eoi(apic, vector);
}