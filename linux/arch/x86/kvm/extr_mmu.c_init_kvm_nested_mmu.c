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
struct TYPE_7__ {scalar_t__ as_u64; } ;
struct kvm_mmu {int nx; void* gva_to_gpa; scalar_t__ root_level; int /*<<< orphan*/  inject_page_fault; int /*<<< orphan*/  get_pdptr; int /*<<< orphan*/  get_cr3; TYPE_3__ mmu_role; } ;
struct TYPE_5__ {struct kvm_mmu nested_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_8__ {int /*<<< orphan*/  word; } ;

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
 union kvm_mmu_role kvm_calc_mmu_role_common (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_inject_page_fault ; 
 int /*<<< orphan*/  kvm_pdptr_read ; 
 TYPE_4__ mmu_base_role_mask ; 
 void* nonpaging_gva_to_gpa_nested ; 
 void* paging32_gva_to_gpa_nested ; 
 void* paging64_gva_to_gpa_nested ; 
 int /*<<< orphan*/  reset_rsvds_bits_mask (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_last_nonleaf_level (struct kvm_vcpu*,struct kvm_mmu*) ; 
 int /*<<< orphan*/  update_permission_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 
 int /*<<< orphan*/  update_pkru_bitmask (struct kvm_vcpu*,struct kvm_mmu*,int) ; 

__attribute__((used)) static void init_kvm_nested_mmu(struct kvm_vcpu *vcpu)
{
	union kvm_mmu_role new_role = kvm_calc_mmu_role_common(vcpu, false);
	struct kvm_mmu *g_context = &vcpu->arch.nested_mmu;

	new_role.base.word &= mmu_base_role_mask.word;
	if (new_role.as_u64 == g_context->mmu_role.as_u64)
		return;

	g_context->mmu_role.as_u64 = new_role.as_u64;
	g_context->get_cr3           = get_cr3;
	g_context->get_pdptr         = kvm_pdptr_read;
	g_context->inject_page_fault = kvm_inject_page_fault;

	/*
	 * Note that arch.mmu->gva_to_gpa translates l2_gpa to l1_gpa using
	 * L1's nested page tables (e.g. EPT12). The nested translation
	 * of l2_gva to l1_gpa is done by arch.nested_mmu.gva_to_gpa using
	 * L2's page tables as the first level of translation and L1's
	 * nested page tables as the second level of translation. Basically
	 * the gva_to_gpa functions between mmu and nested_mmu are swapped.
	 */
	if (!is_paging(vcpu)) {
		g_context->nx = false;
		g_context->root_level = 0;
		g_context->gva_to_gpa = nonpaging_gva_to_gpa_nested;
	} else if (is_long_mode(vcpu)) {
		g_context->nx = is_nx(vcpu);
		g_context->root_level = is_la57_mode(vcpu) ?
					PT64_ROOT_5LEVEL : PT64_ROOT_4LEVEL;
		reset_rsvds_bits_mask(vcpu, g_context);
		g_context->gva_to_gpa = paging64_gva_to_gpa_nested;
	} else if (is_pae(vcpu)) {
		g_context->nx = is_nx(vcpu);
		g_context->root_level = PT32E_ROOT_LEVEL;
		reset_rsvds_bits_mask(vcpu, g_context);
		g_context->gva_to_gpa = paging64_gva_to_gpa_nested;
	} else {
		g_context->nx = false;
		g_context->root_level = PT32_ROOT_LEVEL;
		reset_rsvds_bits_mask(vcpu, g_context);
		g_context->gva_to_gpa = paging32_gva_to_gpa_nested;
	}

	update_permission_bitmask(vcpu, g_context, false);
	update_pkru_bitmask(vcpu, g_context, false);
	update_last_nonleaf_level(vcpu, g_context);
}