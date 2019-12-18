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
typedef  int u32 ;
struct TYPE_2__ {int change_vmcs01_virtual_apic_mode; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
#define  LAPIC_MODE_DISABLED 131 
#define  LAPIC_MODE_INVALID 130 
#define  LAPIC_MODE_X2APIC 129 
#define  LAPIC_MODE_XAPIC 128 
 int SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES ; 
 int SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 scalar_t__ cpu_has_vmx_virtualize_x2apic_mode () ; 
 scalar_t__ flexpriority_enabled ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int kvm_get_apic_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  lapic_in_kernel (struct kvm_vcpu*) ; 
 int secondary_exec_controls_get (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  secondary_exec_controls_set (struct vcpu_vmx*,int) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_flush_tlb (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vmx_update_msr_bitmap (struct kvm_vcpu*) ; 

void vmx_set_virtual_apic_mode(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	u32 sec_exec_control;

	if (!lapic_in_kernel(vcpu))
		return;

	if (!flexpriority_enabled &&
	    !cpu_has_vmx_virtualize_x2apic_mode())
		return;

	/* Postpone execution until vmcs01 is the current VMCS. */
	if (is_guest_mode(vcpu)) {
		vmx->nested.change_vmcs01_virtual_apic_mode = true;
		return;
	}

	sec_exec_control = secondary_exec_controls_get(vmx);
	sec_exec_control &= ~(SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES |
			      SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE);

	switch (kvm_get_apic_mode(vcpu)) {
	case LAPIC_MODE_INVALID:
		WARN_ONCE(true, "Invalid local APIC state");
	case LAPIC_MODE_DISABLED:
		break;
	case LAPIC_MODE_XAPIC:
		if (flexpriority_enabled) {
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_APIC_ACCESSES;
			vmx_flush_tlb(vcpu, true);
		}
		break;
	case LAPIC_MODE_X2APIC:
		if (cpu_has_vmx_virtualize_x2apic_mode())
			sec_exec_control |=
				SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE;
		break;
	}
	secondary_exec_controls_set(vmx, sec_exec_control);

	vmx_update_msr_bitmap(vcpu);
}