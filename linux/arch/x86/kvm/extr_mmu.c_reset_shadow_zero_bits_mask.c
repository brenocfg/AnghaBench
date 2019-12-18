#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rsvd_bits_validate {int /*<<< orphan*/ ** rsvd_bits_mask; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_3__ {scalar_t__ smep_andnot_wp; } ;
struct TYPE_4__ {TYPE_1__ base; } ;
struct kvm_mmu {int shadow_root_level; struct rsvd_bits_validate shadow_zero_check; TYPE_2__ mmu_role; scalar_t__ nx; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_GBPAGES ; 
 int /*<<< orphan*/  __reset_rsvds_bits_mask (struct kvm_vcpu*,struct rsvd_bits_validate*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_pse (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  shadow_me_mask ; 
 int /*<<< orphan*/  shadow_phys_bits ; 

void
reset_shadow_zero_bits_mask(struct kvm_vcpu *vcpu, struct kvm_mmu *context)
{
	bool uses_nx = context->nx ||
		context->mmu_role.base.smep_andnot_wp;
	struct rsvd_bits_validate *shadow_zero_check;
	int i;

	/*
	 * Passing "true" to the last argument is okay; it adds a check
	 * on bit 8 of the SPTEs which KVM doesn't use anyway.
	 */
	shadow_zero_check = &context->shadow_zero_check;
	__reset_rsvds_bits_mask(vcpu, shadow_zero_check,
				shadow_phys_bits,
				context->shadow_root_level, uses_nx,
				guest_cpuid_has(vcpu, X86_FEATURE_GBPAGES),
				is_pse(vcpu), true);

	if (!shadow_me_mask)
		return;

	for (i = context->shadow_root_level; --i >= 0;) {
		shadow_zero_check->rsvd_bits_mask[0][i] &= ~shadow_me_mask;
		shadow_zero_check->rsvd_bits_mask[1][i] &= ~shadow_me_mask;
	}

}