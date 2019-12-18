#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;
typedef  unsigned long kvm_pfn_t ;
typedef  unsigned long gfn_t ;

/* Variables and functions */
 int KVM_PAGES_PER_HPAGE (int) ; 
 int PT_DIRECTORY_LEVEL ; 
 int PT_PAGE_TABLE_LEVEL ; 
 scalar_t__ PageTransCompoundMap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  is_error_noslot_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvm_get_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvm_is_reserved_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvm_is_zone_device_pfn (unsigned long) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (unsigned long) ; 
 int /*<<< orphan*/  mmu_gfn_lpage_is_disallowed (struct kvm_vcpu*,unsigned long,int) ; 
 int /*<<< orphan*/  pfn_to_page (unsigned long) ; 

__attribute__((used)) static void transparent_hugepage_adjust(struct kvm_vcpu *vcpu,
					gfn_t gfn, kvm_pfn_t *pfnp,
					int *levelp)
{
	kvm_pfn_t pfn = *pfnp;
	int level = *levelp;

	/*
	 * Check if it's a transparent hugepage. If this would be an
	 * hugetlbfs page, level wouldn't be set to
	 * PT_PAGE_TABLE_LEVEL and there would be no adjustment done
	 * here.
	 */
	if (!is_error_noslot_pfn(pfn) && !kvm_is_reserved_pfn(pfn) &&
	    !kvm_is_zone_device_pfn(pfn) && level == PT_PAGE_TABLE_LEVEL &&
	    PageTransCompoundMap(pfn_to_page(pfn)) &&
	    !mmu_gfn_lpage_is_disallowed(vcpu, gfn, PT_DIRECTORY_LEVEL)) {
		unsigned long mask;
		/*
		 * mmu_notifier_retry was successful and we hold the
		 * mmu_lock here, so the pmd can't become splitting
		 * from under us, and in turn
		 * __split_huge_page_refcount() can't run from under
		 * us and we can safely transfer the refcount from
		 * PG_tail to PG_head as we switch the pfn to tail to
		 * head.
		 */
		*levelp = level = PT_DIRECTORY_LEVEL;
		mask = KVM_PAGES_PER_HPAGE(level) - 1;
		VM_BUG_ON((gfn & mask) != (pfn & mask));
		if (pfn & mask) {
			kvm_release_pfn_clean(pfn);
			pfn &= ~mask;
			kvm_get_pfn(pfn);
			*pfnp = pfn;
		}
	}
}