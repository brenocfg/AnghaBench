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
typedef  union kvm_mmu_page_role {int dummy; } kvm_mmu_page_role ;
struct TYPE_3__ {struct kvm_mmu* mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mmu {scalar_t__ shadow_root_level; scalar_t__ root_level; int /*<<< orphan*/  root_hpa; } ;
typedef  int gpa_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* tlb_flush ) (struct kvm_vcpu*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_LOAD_CR3 ; 
 int /*<<< orphan*/  KVM_REQ_MMU_SYNC ; 
 int /*<<< orphan*/  MMIO_GVA_ANY ; 
 int PAGE_SHIFT ; 
 scalar_t__ PT64_ROOT_4LEVEL ; 
 int /*<<< orphan*/  __clear_sp_write_flooding_count (int /*<<< orphan*/ ) ; 
 scalar_t__ cached_root_available (struct kvm_vcpu*,int,union kvm_mmu_page_role) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_2__* kvm_x86_ops ; 
 scalar_t__ mmu_check_root (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  page_header (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  vcpu_clear_mmio_info (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool fast_cr3_switch(struct kvm_vcpu *vcpu, gpa_t new_cr3,
			    union kvm_mmu_page_role new_role,
			    bool skip_tlb_flush)
{
	struct kvm_mmu *mmu = vcpu->arch.mmu;

	/*
	 * For now, limit the fast switch to 64-bit hosts+VMs in order to avoid
	 * having to deal with PDPTEs. We may add support for 32-bit hosts/VMs
	 * later if necessary.
	 */
	if (mmu->shadow_root_level >= PT64_ROOT_4LEVEL &&
	    mmu->root_level >= PT64_ROOT_4LEVEL) {
		if (mmu_check_root(vcpu, new_cr3 >> PAGE_SHIFT))
			return false;

		if (cached_root_available(vcpu, new_cr3, new_role)) {
			/*
			 * It is possible that the cached previous root page is
			 * obsolete because of a change in the MMU generation
			 * number. However, changing the generation number is
			 * accompanied by KVM_REQ_MMU_RELOAD, which will free
			 * the root set here and allocate a new one.
			 */
			kvm_make_request(KVM_REQ_LOAD_CR3, vcpu);
			if (!skip_tlb_flush) {
				kvm_make_request(KVM_REQ_MMU_SYNC, vcpu);
				kvm_x86_ops->tlb_flush(vcpu, true);
			}

			/*
			 * The last MMIO access's GVA and GPA are cached in the
			 * VCPU. When switching to a new CR3, that GVA->GPA
			 * mapping may no longer be valid. So clear any cached
			 * MMIO info even when we don't need to sync the shadow
			 * page tables.
			 */
			vcpu_clear_mmio_info(vcpu, MMIO_GVA_ANY);

			__clear_sp_write_flooding_count(
				page_header(mmu->root_hpa));

			return true;
		}
	}

	return false;
}