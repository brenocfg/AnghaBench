#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  word; } ;
union kvm_mmu_role {scalar_t__ as_u64; TYPE_2__ base; } ;
struct TYPE_5__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_7__ {scalar_t__ as_u64; } ;
struct kvm_mmu {TYPE_3__ mmu_role; } ;
struct TYPE_8__ {int /*<<< orphan*/  word; } ;

/* Variables and functions */
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 union kvm_mmu_role kvm_calc_shadow_mmu_root_page_role (struct kvm_vcpu*,int) ; 
 TYPE_4__ mmu_base_role_mask ; 
 int /*<<< orphan*/  nonpaging_init_context (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  paging32E_init_context (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  paging32_init_context (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  paging64_init_context (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  reset_shadow_zero_bits_mask (struct kvm_vcpu*,struct kvm_mmu*) ; 

void kvm_init_shadow_mmu(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = vcpu->arch.mmu;
	union kvm_mmu_role new_role =
		kvm_calc_shadow_mmu_root_page_role(vcpu, false);

	new_role.base.word &= mmu_base_role_mask.word;
	if (new_role.as_u64 == context->mmu_role.as_u64)
		return;

	if (!is_paging(vcpu))
		nonpaging_init_context(vcpu, context);
	else if (is_long_mode(vcpu))
		paging64_init_context(vcpu, context);
	else if (is_pae(vcpu))
		paging32E_init_context(vcpu, context);
	else
		paging32_init_context(vcpu, context);

	context->mmu_role.as_u64 = new_role.as_u64;
	reset_shadow_zero_bits_mask(vcpu, context);
}