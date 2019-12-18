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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm {int /*<<< orphan*/  mmu_lock; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  unsigned long gfn_t ;

/* Variables and functions */
 int EFAULT ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/ * kvm_mips_pte_for_gpa (struct kvm*,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  kvm_set_pfn_accessed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_set_pfn_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_page_dirty (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  pte_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_young (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ptep_buddy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int _kvm_mips_map_page_fast(struct kvm_vcpu *vcpu, unsigned long gpa,
				   bool write_fault,
				   pte_t *out_entry, pte_t *out_buddy)
{
	struct kvm *kvm = vcpu->kvm;
	gfn_t gfn = gpa >> PAGE_SHIFT;
	pte_t *ptep;
	kvm_pfn_t pfn = 0;	/* silence bogus GCC warning */
	bool pfn_valid = false;
	int ret = 0;

	spin_lock(&kvm->mmu_lock);

	/* Fast path - just check GPA page table for an existing entry */
	ptep = kvm_mips_pte_for_gpa(kvm, NULL, gpa);
	if (!ptep || !pte_present(*ptep)) {
		ret = -EFAULT;
		goto out;
	}

	/* Track access to pages marked old */
	if (!pte_young(*ptep)) {
		set_pte(ptep, pte_mkyoung(*ptep));
		pfn = pte_pfn(*ptep);
		pfn_valid = true;
		/* call kvm_set_pfn_accessed() after unlock */
	}
	if (write_fault && !pte_dirty(*ptep)) {
		if (!pte_write(*ptep)) {
			ret = -EFAULT;
			goto out;
		}

		/* Track dirtying of writeable pages */
		set_pte(ptep, pte_mkdirty(*ptep));
		pfn = pte_pfn(*ptep);
		mark_page_dirty(kvm, gfn);
		kvm_set_pfn_dirty(pfn);
	}

	if (out_entry)
		*out_entry = *ptep;
	if (out_buddy)
		*out_buddy = *ptep_buddy(ptep);

out:
	spin_unlock(&kvm->mmu_lock);
	if (pfn_valid)
		kvm_set_pfn_accessed(pfn);
	return ret;
}