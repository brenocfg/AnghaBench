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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ pd_entry_t ;

/* Variables and functions */
 int EINVAL ; 
 int NBPDR ; 
 int NBSEG ; 
 scalar_t__ PAGE_SIZE ; 
 int PDRMASK ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_V ; 
 int SEGMASK ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  mips_dcache_wbinv_range (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (scalar_t__*,int) ; 
 scalar_t__* pmap_pdpe_to_pde (scalar_t__*,int) ; 
 int /*<<< orphan*/  pmap_pte_attr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__* pmap_segmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_cache_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pmap_change_attr(vm_offset_t sva, vm_size_t size, vm_memattr_t ma)
{
	pd_entry_t *pde, *pdpe;
	pt_entry_t *pte;
	vm_offset_t ova, eva, va, va_next;
	pmap_t pmap;

	ova = sva;
	eva = sva + size;
	if (eva < sva)
		return (EINVAL);

	pmap = kernel_pmap;
	PMAP_LOCK(pmap);

	for (; sva < eva; sva = va_next) {
		pdpe = pmap_segmap(pmap, sva);
#ifdef __mips_n64
		if (*pdpe == 0) {
			va_next = (sva + NBSEG) & ~SEGMASK;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
#endif
		va_next = (sva + NBPDR) & ~PDRMASK;
		if (va_next < sva)
			va_next = eva;

		pde = pmap_pdpe_to_pde(pdpe, sva);
		if (*pde == NULL)
			continue;

		/*
		 * Limit our scan to either the end of the va represented
		 * by the current page table page, or to the end of the
		 * range being removed.
		 */
		if (va_next > eva)
			va_next = eva;

		va = va_next;
		for (pte = pmap_pde_to_pte(pde, sva); sva != va_next; pte++,
		    sva += PAGE_SIZE) {
			if (!pte_test(pte, PTE_V) || pte_cache_bits(pte) == ma) {
				if (va != va_next) {
					pmap_invalidate_range(pmap, va, sva);
					va = va_next;
				}
				continue;
			}
			if (va == va_next)
				va = sva;

			pmap_pte_attr(pte, ma);
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
	PMAP_UNLOCK(pmap);

	/* Flush caches to be in the safe side */
	mips_dcache_wbinv_range(ova, size);
	return 0;
}