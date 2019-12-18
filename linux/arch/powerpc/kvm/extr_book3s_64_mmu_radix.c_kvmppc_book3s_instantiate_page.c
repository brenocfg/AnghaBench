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
struct page {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  pgdir; } ;
struct kvm_vcpu {TYPE_1__ arch; struct kvm* kvm; } ;
struct kvm_memory_slot {int flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  num_1G_pages; int /*<<< orphan*/  num_2M_pages; } ;
struct TYPE_5__ {int /*<<< orphan*/  lpid; int /*<<< orphan*/  pgtable; } ;
struct kvm {unsigned long mmu_notifier_seq; TYPE_3__ stat; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int EFAULT ; 
 int KVM_MEM_LOG_DIRTY_PAGES ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PAGE_SIZE ; 
 unsigned int PMD_SHIFT ; 
 unsigned long PMD_SIZE ; 
 unsigned int PUD_SHIFT ; 
 unsigned long PUD_SIZE ; 
 scalar_t__ PageReserved (struct page*) ; 
 int RESUME_GUEST ; 
 int _PAGE_ACCESSED ; 
 int _PAGE_DIRTY ; 
 int _PAGE_EXEC ; 
 int _PAGE_WRITE ; 
 int /*<<< orphan*/ * __find_linux_pte (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,unsigned int*) ; 
 int __get_user_pages_fast (unsigned long,int,int,struct page**) ; 
 unsigned long __gfn_to_pfn_memslot (struct kvm_memory_slot*,unsigned long,int,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  __pte (int) ; 
 unsigned long gfn_to_hva_memslot (struct kvm_memory_slot*,unsigned long) ; 
 scalar_t__ is_error_noslot_pfn (unsigned long) ; 
 int kvmppc_create_pte (struct kvm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned int,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 struct page* pfn_to_page (unsigned long) ; 
 scalar_t__ pfn_valid (unsigned long) ; 
 int pte_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty_lock (struct page*) ; 
 int /*<<< orphan*/  smp_rmb () ; 

int kvmppc_book3s_instantiate_page(struct kvm_vcpu *vcpu,
				   unsigned long gpa,
				   struct kvm_memory_slot *memslot,
				   bool writing, bool kvm_ro,
				   pte_t *inserted_pte, unsigned int *levelp)
{
	struct kvm *kvm = vcpu->kvm;
	struct page *page = NULL;
	unsigned long mmu_seq;
	unsigned long hva, gfn = gpa >> PAGE_SHIFT;
	bool upgrade_write = false;
	bool *upgrade_p = &upgrade_write;
	pte_t pte, *ptep;
	unsigned int shift, level;
	int ret;
	bool large_enable;

	/* used to check for invalidations in progress */
	mmu_seq = kvm->mmu_notifier_seq;
	smp_rmb();

	/*
	 * Do a fast check first, since __gfn_to_pfn_memslot doesn't
	 * do it with !atomic && !async, which is how we call it.
	 * We always ask for write permission since the common case
	 * is that the page is writable.
	 */
	hva = gfn_to_hva_memslot(memslot, gfn);
	if (!kvm_ro && __get_user_pages_fast(hva, 1, 1, &page) == 1) {
		upgrade_write = true;
	} else {
		unsigned long pfn;

		/* Call KVM generic code to do the slow-path check */
		pfn = __gfn_to_pfn_memslot(memslot, gfn, false, NULL,
					   writing, upgrade_p);
		if (is_error_noslot_pfn(pfn))
			return -EFAULT;
		page = NULL;
		if (pfn_valid(pfn)) {
			page = pfn_to_page(pfn);
			if (PageReserved(page))
				page = NULL;
		}
	}

	/*
	 * Read the PTE from the process' radix tree and use that
	 * so we get the shift and attribute bits.
	 */
	local_irq_disable();
	ptep = __find_linux_pte(vcpu->arch.pgdir, hva, NULL, &shift);
	/*
	 * If the PTE disappeared temporarily due to a THP
	 * collapse, just return and let the guest try again.
	 */
	if (!ptep) {
		local_irq_enable();
		if (page)
			put_page(page);
		return RESUME_GUEST;
	}
	pte = *ptep;
	local_irq_enable();

	/* If we're logging dirty pages, always map single pages */
	large_enable = !(memslot->flags & KVM_MEM_LOG_DIRTY_PAGES);

	/* Get pte level from shift/size */
	if (large_enable && shift == PUD_SHIFT &&
	    (gpa & (PUD_SIZE - PAGE_SIZE)) ==
	    (hva & (PUD_SIZE - PAGE_SIZE))) {
		level = 2;
	} else if (large_enable && shift == PMD_SHIFT &&
		   (gpa & (PMD_SIZE - PAGE_SIZE)) ==
		   (hva & (PMD_SIZE - PAGE_SIZE))) {
		level = 1;
	} else {
		level = 0;
		if (shift > PAGE_SHIFT) {
			/*
			 * If the pte maps more than one page, bring over
			 * bits from the virtual address to get the real
			 * address of the specific single page we want.
			 */
			unsigned long rpnmask = (1ul << shift) - PAGE_SIZE;
			pte = __pte(pte_val(pte) | (hva & rpnmask));
		}
	}

	pte = __pte(pte_val(pte) | _PAGE_EXEC | _PAGE_ACCESSED);
	if (writing || upgrade_write) {
		if (pte_val(pte) & _PAGE_WRITE)
			pte = __pte(pte_val(pte) | _PAGE_DIRTY);
	} else {
		pte = __pte(pte_val(pte) & ~(_PAGE_WRITE | _PAGE_DIRTY));
	}

	/* Allocate space in the tree and write the PTE */
	ret = kvmppc_create_pte(kvm, kvm->arch.pgtable, pte, gpa, level,
				mmu_seq, kvm->arch.lpid, NULL, NULL);
	if (inserted_pte)
		*inserted_pte = pte;
	if (levelp)
		*levelp = level;

	if (page) {
		if (!ret && (pte_val(pte) & _PAGE_WRITE))
			set_page_dirty_lock(page);
		put_page(page);
	}

	/* Increment number of large pages if we (successfully) inserted one */
	if (!ret) {
		if (level == 1)
			kvm->stat.num_2M_pages++;
		else if (level == 2)
			kvm->stat.num_1G_pages++;
	}

	return ret;
}