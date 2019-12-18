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
typedef  int u8 ;
struct TYPE_2__ {unsigned long* msr_bitmap; } ;
struct vcpu_vmx {int msr_bitmap_mode; TYPE_1__ vmcs01; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int MSR_BITMAP_MODE_X2APIC ; 
 int MSR_BITMAP_MODE_X2APIC_APICV ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int vmx_msr_bitmap_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_update_msr_bitmap_x2apic (unsigned long*,int) ; 

void vmx_update_msr_bitmap(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long *msr_bitmap = vmx->vmcs01.msr_bitmap;
	u8 mode = vmx_msr_bitmap_mode(vcpu);
	u8 changed = mode ^ vmx->msr_bitmap_mode;

	if (!changed)
		return;

	if (changed & (MSR_BITMAP_MODE_X2APIC | MSR_BITMAP_MODE_X2APIC_APICV))
		vmx_update_msr_bitmap_x2apic(msr_bitmap, mode);

	vmx->msr_bitmap_mode = mode;
}