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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_run {void* exit_reason; } ;

/* Variables and functions */
 int ARM_EXCEPTION_CODE (int) ; 
#define  ARM_EXCEPTION_EL1_SERROR 132 
#define  ARM_EXCEPTION_HYP_GONE 131 
#define  ARM_EXCEPTION_IL 130 
#define  ARM_EXCEPTION_IRQ 129 
#define  ARM_EXCEPTION_TRAP 128 
 scalar_t__ ARM_SERROR_PENDING (int) ; 
 int EINVAL ; 
 scalar_t__ ESR_ELx_EC (int /*<<< orphan*/ ) ; 
 scalar_t__ ESR_ELx_EC_HVC32 ; 
 scalar_t__ ESR_ELx_EC_HVC64 ; 
 scalar_t__ ESR_ELx_EC_SMC32 ; 
 scalar_t__ ESR_ELx_EC_SMC64 ; 
 void* KVM_EXIT_FAIL_ENTRY ; 
 void* KVM_EXIT_INTERNAL_ERROR ; 
 int handle_trap_exceptions (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  kvm_pr_unimpl (char*,int) ; 
 int /*<<< orphan*/  kvm_vcpu_get_hsr (struct kvm_vcpu*) ; 
 scalar_t__ kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

int handle_exit(struct kvm_vcpu *vcpu, struct kvm_run *run,
		       int exception_index)
{
	if (ARM_SERROR_PENDING(exception_index)) {
		u8 hsr_ec = ESR_ELx_EC(kvm_vcpu_get_hsr(vcpu));

		/*
		 * HVC/SMC already have an adjusted PC, which we need
		 * to correct in order to return to after having
		 * injected the SError.
		 */
		if (hsr_ec == ESR_ELx_EC_HVC32 || hsr_ec == ESR_ELx_EC_HVC64 ||
		    hsr_ec == ESR_ELx_EC_SMC32 || hsr_ec == ESR_ELx_EC_SMC64) {
			u32 adj =  kvm_vcpu_trap_il_is32bit(vcpu) ? 4 : 2;
			*vcpu_pc(vcpu) -= adj;
		}

		return 1;
	}

	exception_index = ARM_EXCEPTION_CODE(exception_index);

	switch (exception_index) {
	case ARM_EXCEPTION_IRQ:
		return 1;
	case ARM_EXCEPTION_EL1_SERROR:
		return 1;
	case ARM_EXCEPTION_TRAP:
		return handle_trap_exceptions(vcpu, run);
	case ARM_EXCEPTION_HYP_GONE:
		/*
		 * EL2 has been reset to the hyp-stub. This happens when a guest
		 * is pre-empted by kvm_reboot()'s shutdown call.
		 */
		run->exit_reason = KVM_EXIT_FAIL_ENTRY;
		return 0;
	case ARM_EXCEPTION_IL:
		/*
		 * We attempted an illegal exception return.  Guest state must
		 * have been corrupted somehow.  Give up.
		 */
		run->exit_reason = KVM_EXIT_FAIL_ENTRY;
		return -EINVAL;
	default:
		kvm_pr_unimpl("Unsupported exception type: %d",
			      exception_index);
		run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		return 0;
	}
}