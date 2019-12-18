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
struct TYPE_2__ {unsigned int sve_max_vl; int /*<<< orphan*/  flags; void* sve_state; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KVM_ARM64_VCPU_SVE_FINALIZED ; 
 int /*<<< orphan*/  SVE_SIG_REGS_SIZE (int /*<<< orphan*/ ) ; 
 unsigned int SVE_VL_ARCH_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 void* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int sve_max_virtualisable_vl ; 
 int /*<<< orphan*/  sve_vl_valid (unsigned int) ; 
 int /*<<< orphan*/  sve_vq_from_vl (unsigned int) ; 

__attribute__((used)) static int kvm_vcpu_finalize_sve(struct kvm_vcpu *vcpu)
{
	void *buf;
	unsigned int vl;

	vl = vcpu->arch.sve_max_vl;

	/*
	 * Resposibility for these properties is shared between
	 * kvm_arm_init_arch_resources(), kvm_vcpu_enable_sve() and
	 * set_sve_vls().  Double-check here just to be sure:
	 */
	if (WARN_ON(!sve_vl_valid(vl) || vl > sve_max_virtualisable_vl ||
		    vl > SVE_VL_ARCH_MAX))
		return -EIO;

	buf = kzalloc(SVE_SIG_REGS_SIZE(sve_vq_from_vl(vl)), GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	vcpu->arch.sve_state = buf;
	vcpu->arch.flags |= KVM_ARM64_VCPU_SVE_FINALIZED;
	return 0;
}