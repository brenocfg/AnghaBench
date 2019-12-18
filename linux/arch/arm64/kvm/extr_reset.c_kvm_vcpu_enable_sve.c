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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  sve_max_vl; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_ARM64_GUEST_HAS_SVE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  has_vhe () ; 
 int /*<<< orphan*/  kvm_sve_max_vl ; 
 int /*<<< orphan*/  system_supports_sve () ; 

__attribute__((used)) static int kvm_vcpu_enable_sve(struct kvm_vcpu *vcpu)
{
	if (!system_supports_sve())
		return -EINVAL;

	/* Verify that KVM startup enforced this when SVE was detected: */
	if (WARN_ON(!has_vhe()))
		return -EINVAL;

	vcpu->arch.sve_max_vl = kvm_sve_max_vl;

	/*
	 * Userspace can still customize the vector lengths by writing
	 * KVM_REG_ARM64_SVE_VLS.  Allocation is deferred until
	 * kvm_arm_vcpu_finalize(), which freezes the configuration.
	 */
	vcpu->arch.flags |= KVM_ARM64_GUEST_HAS_SVE;

	return 0;
}