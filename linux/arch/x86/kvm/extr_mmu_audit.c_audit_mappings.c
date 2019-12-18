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
typedef  int u64 ;
struct TYPE_4__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_2__ arch; int /*<<< orphan*/  kvm; } ;
struct kvm_mmu_page {int spt; scalar_t__ unsync; } ;
typedef  int kvm_pfn_t ;
typedef  int hpa_t ;
typedef  int /*<<< orphan*/  gfn_t ;
struct TYPE_3__ {int /*<<< orphan*/  root_level; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int PT64_BASE_ADDR_MASK ; 
 int PT_PAGE_TABLE_LEVEL ; 
 int /*<<< orphan*/  __pa (int*) ; 
 int /*<<< orphan*/  audit_printk (int /*<<< orphan*/ ,char*,struct kvm_mmu_page*,int,...) ; 
 scalar_t__ is_error_pfn (int) ; 
 int /*<<< orphan*/  is_last_spte (int,int) ; 
 int /*<<< orphan*/  is_shadow_present_pte (int) ; 
 int /*<<< orphan*/  kvm_mmu_page_get_gfn (struct kvm_mmu_page*,int*) ; 
 int kvm_vcpu_gfn_to_pfn_atomic (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 struct kvm_mmu_page* page_header (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void audit_mappings(struct kvm_vcpu *vcpu, u64 *sptep, int level)
{
	struct kvm_mmu_page *sp;
	gfn_t gfn;
	kvm_pfn_t pfn;
	hpa_t hpa;

	sp = page_header(__pa(sptep));

	if (sp->unsync) {
		if (level != PT_PAGE_TABLE_LEVEL) {
			audit_printk(vcpu->kvm, "unsync sp: %p "
				     "level = %d\n", sp, level);
			return;
		}
	}

	if (!is_shadow_present_pte(*sptep) || !is_last_spte(*sptep, level))
		return;

	gfn = kvm_mmu_page_get_gfn(sp, sptep - sp->spt);
	pfn = kvm_vcpu_gfn_to_pfn_atomic(vcpu, gfn);

	if (is_error_pfn(pfn))
		return;

	hpa =  pfn << PAGE_SHIFT;
	if ((*sptep & PT64_BASE_ADDR_MASK) != hpa)
		audit_printk(vcpu->kvm, "levels %d pfn %llx hpa %llx "
			     "ent %llxn", vcpu->arch.mmu->root_level, pfn,
			     hpa, *sptep);
}