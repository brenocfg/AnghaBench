#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int gva_t ;
typedef  int gfn_t ;
struct TYPE_6__ {unsigned long mmu_notifier_seq; int /*<<< orphan*/  mmu_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  root_hpa; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_ALL ; 
 int KVM_PAGES_PER_HPAGE (int) ; 
 int /*<<< orphan*/  MMU_WARN_ON (int) ; 
 int PAGE_SHIFT ; 
 int PFERR_FETCH_MASK ; 
 int PFERR_WRITE_MASK ; 
 int PT_DIRECTORY_LEVEL ; 
 int RET_PF_EMULATE ; 
 int RET_PF_RETRY ; 
 int /*<<< orphan*/  VALID_PAGE (int /*<<< orphan*/ ) ; 
 int __direct_map (struct kvm_vcpu*,int,int,int,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  check_hugepage_cache_consistency (struct kvm_vcpu*,int,int) ; 
 scalar_t__ fast_page_fault (struct kvm_vcpu*,int,int,int) ; 
 scalar_t__ handle_abnormal_pfn (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ is_nx_huge_page_enabled () ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ make_mmu_pages_available (struct kvm_vcpu*) ; 
 int mapping_level (struct kvm_vcpu*,int,int*) ; 
 scalar_t__ mmu_notifier_retry (TYPE_3__*,unsigned long) ; 
 int mmu_topup_memory_caches (struct kvm_vcpu*) ; 
 scalar_t__ page_fault_handle_page_track (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  smp_rmb () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transparent_hugepage_adjust (struct kvm_vcpu*,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ try_async_pf (struct kvm_vcpu*,int,int,int,int /*<<< orphan*/ *,int,int*) ; 

__attribute__((used)) static int tdp_page_fault(struct kvm_vcpu *vcpu, gva_t gpa, u32 error_code,
			  bool prefault)
{
	kvm_pfn_t pfn;
	int r;
	int level;
	bool force_pt_level;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	unsigned long mmu_seq;
	int write = error_code & PFERR_WRITE_MASK;
	bool map_writable;
	bool lpage_disallowed = (error_code & PFERR_FETCH_MASK) &&
				is_nx_huge_page_enabled();

	MMU_WARN_ON(!VALID_PAGE(vcpu->arch.mmu->root_hpa));

	if (page_fault_handle_page_track(vcpu, error_code, gfn))
		return RET_PF_EMULATE;

	r = mmu_topup_memory_caches(vcpu);
	if (r)
		return r;

	force_pt_level =
		lpage_disallowed ||
		!check_hugepage_cache_consistency(vcpu, gfn, PT_DIRECTORY_LEVEL);
	level = mapping_level(vcpu, gfn, &force_pt_level);
	if (likely(!force_pt_level)) {
		if (level > PT_DIRECTORY_LEVEL &&
		    !check_hugepage_cache_consistency(vcpu, gfn, level))
			level = PT_DIRECTORY_LEVEL;
		gfn &= ~(KVM_PAGES_PER_HPAGE(level) - 1);
	}

	if (fast_page_fault(vcpu, gpa, level, error_code))
		return RET_PF_RETRY;

	mmu_seq = vcpu->kvm->mmu_notifier_seq;
	smp_rmb();

	if (try_async_pf(vcpu, prefault, gfn, gpa, &pfn, write, &map_writable))
		return RET_PF_RETRY;

	if (handle_abnormal_pfn(vcpu, 0, gfn, pfn, ACC_ALL, &r))
		return r;

	r = RET_PF_RETRY;
	spin_lock(&vcpu->kvm->mmu_lock);
	if (mmu_notifier_retry(vcpu->kvm, mmu_seq))
		goto out_unlock;
	if (make_mmu_pages_available(vcpu) < 0)
		goto out_unlock;
	if (likely(!force_pt_level))
		transparent_hugepage_adjust(vcpu, gfn, &pfn, &level);
	r = __direct_map(vcpu, gpa, write, map_writable, level, pfn,
			 prefault, lpage_disallowed);
out_unlock:
	spin_unlock(&vcpu->kvm->mmu_lock);
	kvm_release_pfn_clean(pfn);
	return r;
}