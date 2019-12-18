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
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_ACTIVITY_ACTIVE ; 
 scalar_t__ GUEST_ACTIVITY_HLT ; 
 int /*<<< orphan*/  GUEST_ACTIVITY_STATE ; 
 scalar_t__ kvm_hlt_in_guest (int /*<<< orphan*/ ) ; 
 scalar_t__ vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmx_clear_hlt(struct kvm_vcpu *vcpu)
{
	/*
	 * Ensure that we clear the HLT state in the VMCS.  We don't need to
	 * explicitly skip the instruction because if the HLT state is set,
	 * then the instruction is already executing and RIP has already been
	 * advanced.
	 */
	if (kvm_hlt_in_guest(vcpu->kvm) &&
			vmcs_read32(GUEST_ACTIVITY_STATE) == GUEST_ACTIVITY_HLT)
		vmcs_write32(GUEST_ACTIVITY_STATE, GUEST_ACTIVITY_ACTIVE);
}