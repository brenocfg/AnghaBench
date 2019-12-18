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
struct TYPE_4__ {int /*<<< orphan*/  shadow_root_level; int /*<<< orphan*/  inject_page_fault; int /*<<< orphan*/  get_pdptr; int /*<<< orphan*/  get_cr3; int /*<<< orphan*/  set_cr3; } ;
struct TYPE_3__ {int /*<<< orphan*/  nested_mmu; int /*<<< orphan*/ * walk_mmu; TYPE_2__* mmu; TYPE_2__ guest_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_npt_level (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_shadow_mmu (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  mmu_is_nested (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  nested_svm_get_tdp_cr3 ; 
 int /*<<< orphan*/  nested_svm_get_tdp_pdptr ; 
 int /*<<< orphan*/  nested_svm_inject_npf_exit ; 
 int /*<<< orphan*/  nested_svm_set_tdp_cr3 ; 
 int /*<<< orphan*/  reset_shadow_zero_bits_mask (struct kvm_vcpu*,TYPE_2__*) ; 

__attribute__((used)) static void nested_svm_init_mmu_context(struct kvm_vcpu *vcpu)
{
	WARN_ON(mmu_is_nested(vcpu));

	vcpu->arch.mmu = &vcpu->arch.guest_mmu;
	kvm_init_shadow_mmu(vcpu);
	vcpu->arch.mmu->set_cr3           = nested_svm_set_tdp_cr3;
	vcpu->arch.mmu->get_cr3           = nested_svm_get_tdp_cr3;
	vcpu->arch.mmu->get_pdptr         = nested_svm_get_tdp_pdptr;
	vcpu->arch.mmu->inject_page_fault = nested_svm_inject_npf_exit;
	vcpu->arch.mmu->shadow_root_level = get_npt_level(vcpu);
	reset_shadow_zero_bits_mask(vcpu, vcpu->arch.mmu);
	vcpu->arch.walk_mmu              = &vcpu->arch.nested_mmu;
}