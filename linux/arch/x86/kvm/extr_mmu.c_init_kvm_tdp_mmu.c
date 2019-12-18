#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  word; } ;
union kvm_mmu_role {scalar_t__ as_u64; TYPE_2__ base; } ;
struct TYPE_6__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_8__ {scalar_t__ as_u64; } ;
struct kvm_mmu {int direct_map; int nx; void* gva_to_gpa; scalar_t__ root_level; int /*<<< orphan*/  inject_page_fault; int /*<<< orphan*/  get_pdptr; int /*<<< orphan*/  get_cr3; int /*<<< orphan*/  set_cr3; int /*<<< orphan*/  shadow_root_level; int /*<<< orphan*/  update_pte; int /*<<< orphan*/  invlpg; int /*<<< orphan*/  sync_page; int /*<<< orphan*/  page_fault; TYPE_3__ mmu_role; } ;
struct TYPE_10__ {int /*<<< orphan*/  set_tdp_cr3; int /*<<< orphan*/  (* get_tdp_level ) (struct kvm_vcpu*) ;} ;
struct TYPE_9__ {int /*<<< orphan*/  word; } ;

/* Variables and functions */
 scalar_t__ PT32E_ROOT_LEVEL ; 
 scalar_t__ PT32_ROOT_LEVEL ; 
 scalar_t__ PT64_ROOT_4LEVEL ; 
 scalar_t__ PT64_ROOT_5LEVEL ; 
 int /*<<< orphan*/  get_cr3 ; 
 scalar_t__ is_la57_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 void* is_nx (struct kvm_vcpu*) ; 
 scalar_t__ is_pae (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_paging (struct kvm_vcpu*) ; 
 union kvm_mmu_role kvm_calc_tdp_mmu_root_page_role (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_inject_page_fault ; 
 int /*<<< orphan*/  kvm_pdptr_read ; 
 TYPE_5__* kvm_x86_ops ; 
 TYPE_4__ mmu_base_role_mask ; 
 void* nonpaging_gva_to_gpa ; 
 int /*<<< orphan*/  nonpaging_invlpg ; 
 int /*<<< orphan*/  nonpaging_sync_page ; 
 int /*<<< orphan*/  nonpaging_update_pte ; 
 void* paging32_gva_to_gpa ; 
 void* paging64_gva_to_gpa ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  reset_tdp_shadow_zero_bits_mask (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  tdp_page_fault ; 
 int /*<<< orphan*/  update_last_nonleaf_level (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_permission_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  update_pkru_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 

__attribute__((used)) static void init_kvm_tdp_mmu(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *context = vcpu->arch.mmu;
	union kvm_mmu_role new_role =
		kvm_calc_tdp_mmu_root_page_role(vcpu, false);

	new_role.base.word &= mmu_base_role_mask.word;
	if (new_role.as_u64 == context->mmu_role.as_u64)
		return;

	context->mmu_role.as_u64 = new_role.as_u64;
	context->page_fault = tdp_page_fault;
	context->sync_page = nonpaging_sync_page;
	context->invlpg = nonpaging_invlpg;
	context->update_pte = nonpaging_update_pte;
	context->shadow_root_level = kvm_x86_ops->get_tdp_level(vcpu);
	context->direct_map = true;
	context->set_cr3 = kvm_x86_ops->set_tdp_cr3;
	context->get_cr3 = get_cr3;
	context->get_pdptr = kvm_pdptr_read;
	context->inject_page_fault = kvm_inject_page_fault;

	if (!is_paging(vcpu)) {
		context->nx = false;
		context->gva_to_gpa = nonpaging_gva_to_gpa;
		context->root_level = 0;
	} else if (is_long_mode(vcpu)) {
		context->nx = is_nx(vcpu);
		context->root_level = is_la57_mode(vcpu) ?
				PT64_ROOT_5LEVEL : PT64_ROOT_4LEVEL;
		reset_rsvds_bits_mask(vcpu, context);
		context->gva_to_gpa = paging64_gva_to_gpa;
	} else if (is_pae(vcpu)) {
		context->nx = is_nx(vcpu);
		context->root_level = PT32E_ROOT_LEVEL;
		reset_rsvds_bits_mask(vcpu, context);
		context->gva_to_gpa = paging64_gva_to_gpa;
	} else {
		context->nx = false;
		context->root_level = PT32_ROOT_LEVEL;
		reset_rsvds_bits_mask(vcpu, context);
		context->gva_to_gpa = paging32_gva_to_gpa;
	}

	update_permission_bitmask(vcpu, context, false);
	update_pkru_bitmask(vcpu, context, false);
	update_last_nonleaf_level(vcpu, context);
	reset_tdp_shadow_zero_bits_mask(vcpu, context);
}