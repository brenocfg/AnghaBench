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
struct TYPE_2__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  features; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  KVM_ARM64_GUEST_HAS_PTRAUTH ; 
 int /*<<< orphan*/  KVM_ARM_VCPU_PTRAUTH_ADDRESS ; 
 int /*<<< orphan*/  KVM_ARM_VCPU_PTRAUTH_GENERIC ; 
 int /*<<< orphan*/  has_vhe () ; 
 int /*<<< orphan*/  system_supports_address_auth () ; 
 int /*<<< orphan*/  system_supports_generic_auth () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_vcpu_enable_ptrauth(struct kvm_vcpu *vcpu)
{
	/* Support ptrauth only if the system supports these capabilities. */
	if (!has_vhe())
		return -EINVAL;

	if (!system_supports_address_auth() ||
	    !system_supports_generic_auth())
		return -EINVAL;
	/*
	 * For now make sure that both address/generic pointer authentication
	 * features are requested by the userspace together.
	 */
	if (!test_bit(KVM_ARM_VCPU_PTRAUTH_ADDRESS, vcpu->arch.features) ||
	    !test_bit(KVM_ARM_VCPU_PTRAUTH_GENERIC, vcpu->arch.features))
		return -EINVAL;

	vcpu->arch.flags |= KVM_ARM64_GUEST_HAS_PTRAUTH;
	return 0;
}