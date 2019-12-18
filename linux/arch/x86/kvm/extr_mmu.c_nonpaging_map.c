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
typedef  int u32 ;
struct kvm_vcpu {TYPE_1__* kvm; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int gfn_t ;
struct TYPE_2__ {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int KVM_PAGES_PER_HPAGE (int) ; 
 int PFERR_FETCH_MASK ; 
 int PFERR_WRITE_MASK ; 
 int PT_DIRECTORY_LEVEL ; 
 int RET_PF_RETRY ; 
 int __direct_map (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ fast_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ handle_abnormal_pfn (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_nx_huge_page_enabled () ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ make_mmu_pages_available (struct kvm_vcpu*) ; 
 int mapping_level (struct kvm_vcpu*,int,int*) ; 
 scalar_t__ mmu_notifier_retry (TYPE_1__*,unsigned long) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transparent_hugepage_adjust (struct kvm_vcpu*,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ try_async_pf (struct kvm_vcpu*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int nonpaging_map(struct kvm_vcpu *vcpu, gva_t v, u32 error_code,
			 gfn_t gfn, bool prefault)
{
	int r;
	int level;
	bool force_pt_level;
	kvm_pfn_t pfn;
	unsigned long mmu_seq;
	bool map_writable, write = error_code & PFERR_WRITE_MASK;
	bool lpage_disallowed = (error_code & PFERR_FETCH_MASK) &&
				is_nx_huge_page_enabled();

	force_pt_level = lpage_disallowed;
	level = mapping_level(vcpu, gfn, &force_pt_level);
	if (likely(!force_pt_level)) {
		/*
		 * This path builds a PAE pagetable - so we can map
		 * 2mb pages at maximum. Therefore check if the level
		 * is larger than that.
		 */
		if (level > PT_DIRECTORY_LEVEL)
			level = PT_DIRECTORY_LEVEL;

		gfn &= ~(KVM_PAGES_PER_HPAGE(level) - 1);
	}

	if (fast_page_fault(vcpu, v, level, error_code))
		return RET_PF_RETRY;

	mmu_seq = vcpu->kvm->mmu_notifier_seq;
	smp_rmb();

	if (try_async_pf(vcpu, prefault, gfn, v, &pfn, write, &map_writable))
		return RET_PF_RETRY;

	if (handle_abnormal_pfn(vcpu, v, gfn, pfn, ACC_ALL, &r))
		return r;

	r = RET_PF_RETRY;
	spin_lock(&vcpu->kvm->mmu_lock);
	if (mmu_notifier_retry(vcpu->kvm, mmu_seq))
		goto out_unlock;
	if (make_mmu_pages_available(vcpu) < 0)
		goto out_unlock;
	if (likely(!force_pt_level))
		transparent_hugepage_adjust(vcpu, gfn, &pfn, &level);
	r = __direct_map(vcpu, v, write, map_writable, level, pfn,
			 prefault, false);
out_unlock:
	spin_unlock(&vcpu->kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	return r;
}