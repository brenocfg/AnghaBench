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
typedef  int /*<<< orphan*/  u64 ;
struct kvm_vcpu {int dummy; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARM64_HAS_RAS_EXTN ; 
 int ARM_EXCEPTION_CODE (int) ; 
 int ARM_EXCEPTION_EL1_SERROR ; 
 scalar_t__ ARM_SERROR_PENDING (int) ; 
 int /*<<< orphan*/  disr_to_esr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_handle_guest_serror (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_vabt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_get_disr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_get_hsr (struct kvm_vcpu*) ; 
 scalar_t__ this_cpu_has_cap (int /*<<< orphan*/ ) ; 

void handle_exit_early(struct kvm_vcpu *vcpu, struct kvm_run *run,
		       int exception_index)
{
	if (ARM_SERROR_PENDING(exception_index)) {
		if (this_cpu_has_cap(ARM64_HAS_RAS_EXTN)) {
			u64 disr = kvm_vcpu_get_disr(vcpu);

			kvm_handle_guest_serror(vcpu, disr_to_esr(disr));
		} else {
			kvm_inject_vabt(vcpu);
		}

		return;
	}

	exception_index = ARM_EXCEPTION_CODE(exception_index);

	if (exception_index == ARM_EXCEPTION_EL1_SERROR)
		kvm_handle_guest_serror(vcpu, kvm_vcpu_get_hsr(vcpu));
}