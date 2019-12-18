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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_BITMAP_MODE_X2APIC ; 
 int /*<<< orphan*/  MSR_BITMAP_MODE_X2APIC_APICV ; 
 int SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE ; 
 scalar_t__ cpu_has_secondary_exec_ctrls () ; 
 scalar_t__ enable_apicv ; 
 scalar_t__ kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 int secondary_exec_controls_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static u8 vmx_msr_bitmap_mode(struct kvm_vcpu *vcpu)
{
	u8 mode = 0;

	if (cpu_has_secondary_exec_ctrls() &&
	    (secondary_exec_controls_get(to_vmx(vcpu)) &
	     SECONDARY_EXEC_VIRTUALIZE_X2APIC_MODE)) {
		mode |= MSR_BITMAP_MODE_X2APIC;
		if (enable_apicv && kvm_vcpu_apicv_active(vcpu))
			mode |= MSR_BITMAP_MODE_X2APIC_APICV;
	}

	return mode;
}