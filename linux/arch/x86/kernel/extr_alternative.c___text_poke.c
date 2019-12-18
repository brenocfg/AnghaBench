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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  temp_mm_state_t ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  spinlock_t ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 int /*<<< orphan*/  PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PageReserved (struct page*) ; 
 int /*<<< orphan*/  VM_BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int _PAGE_GLOBAL ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  after_bootmem ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  core_kernel_text (unsigned long) ; 
 int /*<<< orphan*/  flush_tlb_mm_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * get_locked_pte (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  kasan_disable_current () ; 
 int /*<<< orphan*/  kasan_enable_current () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int memcmp (void*,void const*,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/  mk_pte (struct page*,int /*<<< orphan*/ ) ; 
 int offset_in_page (void*) ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 scalar_t__ poking_addr ; 
 int /*<<< orphan*/  poking_mm ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_unmap_unlock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_pte_at (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unuse_temporary_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  use_temporary_mm (int /*<<< orphan*/ ) ; 
 struct page* virt_to_page (void*) ; 
 struct page* vmalloc_to_page (void*) ; 

__attribute__((used)) static void *__text_poke(void *addr, const void *opcode, size_t len)
{
	bool cross_page_boundary = offset_in_page(addr) + len > PAGE_SIZE;
	struct page *pages[2] = {NULL};
	temp_mm_state_t prev;
	unsigned long flags;
	pte_t pte, *ptep;
	spinlock_t *ptl;
	pgprot_t pgprot;

	/*
	 * While boot memory allocator is running we cannot use struct pages as
	 * they are not yet initialized. There is no way to recover.
	 */
	BUG_ON(!after_bootmem);

	if (!core_kernel_text((unsigned long)addr)) {
		pages[0] = vmalloc_to_page(addr);
		if (cross_page_boundary)
			pages[1] = vmalloc_to_page(addr + PAGE_SIZE);
	} else {
		pages[0] = virt_to_page(addr);
		WARN_ON(!PageReserved(pages[0]));
		if (cross_page_boundary)
			pages[1] = virt_to_page(addr + PAGE_SIZE);
	}
	/*
	 * If something went wrong, crash and burn since recovery paths are not
	 * implemented.
	 */
	BUG_ON(!pages[0] || (cross_page_boundary && !pages[1]));

	local_irq_save(flags);

	/*
	 * Map the page without the global bit, as TLB flushing is done with
	 * flush_tlb_mm_range(), which is intended for non-global PTEs.
	 */
	pgprot = __pgprot(pgprot_val(PAGE_KERNEL) & ~_PAGE_GLOBAL);

	/*
	 * The lock is not really needed, but this allows to avoid open-coding.
	 */
	ptep = get_locked_pte(poking_mm, poking_addr, &ptl);

	/*
	 * This must not fail; preallocated in poking_init().
	 */
	VM_BUG_ON(!ptep);

	pte = mk_pte(pages[0], pgprot);
	set_pte_at(poking_mm, poking_addr, ptep, pte);

	if (cross_page_boundary) {
		pte = mk_pte(pages[1], pgprot);
		set_pte_at(poking_mm, poking_addr + PAGE_SIZE, ptep + 1, pte);
	}

	/*
	 * Loading the temporary mm behaves as a compiler barrier, which
	 * guarantees that the PTE will be set at the time memcpy() is done.
	 */
	prev = use_temporary_mm(poking_mm);

	kasan_disable_current();
	memcpy((u8 *)poking_addr + offset_in_page(addr), opcode, len);
	kasan_enable_current();

	/*
	 * Ensure that the PTE is only cleared after the instructions of memcpy
	 * were issued by using a compiler barrier.
	 */
	barrier();

	pte_clear(poking_mm, poking_addr, ptep);
	if (cross_page_boundary)
		pte_clear(poking_mm, poking_addr + PAGE_SIZE, ptep + 1);

	/*
	 * Loading the previous page-table hierarchy requires a serializing
	 * instruction that already allows the core to see the updated version.
	 * Xen-PV is assumed to serialize execution in a similar manner.
	 */
	unuse_temporary_mm(prev);

	/*
	 * Flushing the TLB might involve IPIs, which would require enabled
	 * IRQs, but not if the mm is not used, as it is in this point.
	 */
	flush_tlb_mm_range(poking_mm, poking_addr, poking_addr +
			   (cross_page_boundary ? 2 : 1) * PAGE_SIZE,
			   PAGE_SHIFT, false);

	/*
	 * If the text does not match what we just wrote then something is
	 * fundamentally screwy; there's nothing we can really do about that.
	 */
	BUG_ON(memcmp(addr, opcode, len));

	pte_unmap_unlock(ptep, ptl);
	local_irq_restore(flags);
	return addr;
}