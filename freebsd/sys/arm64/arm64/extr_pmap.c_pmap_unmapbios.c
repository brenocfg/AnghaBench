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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
struct pmap_preinit_mapping {scalar_t__ va; scalar_t__ size; scalar_t__ pa; } ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ L2_SHIFT ; 
 int L2_SIZE ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int PMAP_PREINIT_MAPPING_COUNT ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kva_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_invalidate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove (scalar_t__) ; 
 int /*<<< orphan*/ * pmap_l1_to_l2 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * pmap_pde (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct pmap_preinit_mapping* pmap_preinit_mapping ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ rounddown2 (scalar_t__,int) ; 
 scalar_t__ roundup2 (scalar_t__,int) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 scalar_t__ vm_initialized ; 

void
pmap_unmapbios(vm_offset_t va, vm_size_t size)
{
	struct pmap_preinit_mapping *ppim;
	vm_offset_t offset, tmpsize, va_trunc;
	pd_entry_t *pde;
	pt_entry_t *l2;
	int i, lvl, l2_blocks, block;
	bool preinit_map;

	l2_blocks =
	   (roundup2(va + size, L2_SIZE) - rounddown2(va, L2_SIZE)) >> L2_SHIFT;
	KASSERT(l2_blocks > 0, ("pmap_unmapbios: invalid size %lx", size));

	/* Remove preinit mapping */
	preinit_map = false;
	block = 0;
	for (i = 0; i < PMAP_PREINIT_MAPPING_COUNT; i++) {
		ppim = pmap_preinit_mapping + i;
		if (ppim->va == va) {
			KASSERT(ppim->size == size,
			    ("pmap_unmapbios: size mismatch"));
			ppim->va = 0;
			ppim->pa = 0;
			ppim->size = 0;
			preinit_map = true;
			offset = block * L2_SIZE;
			va_trunc = rounddown2(va, L2_SIZE) + offset;

			/* Remove L2_BLOCK */
			pde = pmap_pde(kernel_pmap, va_trunc, &lvl);
			KASSERT(pde != NULL,
			    ("pmap_unmapbios: Invalid page entry, va: 0x%lx",
			    va_trunc));
			l2 = pmap_l1_to_l2(pde, va_trunc);
			pmap_clear(l2);

			if (block == (l2_blocks - 1))
				break;
			block++;
		}
	}
	if (preinit_map) {
		pmap_invalidate_all(kernel_pmap);
		return;
	}

	/* Unmap the pages reserved with kva_alloc. */
	if (vm_initialized) {
		offset = va & PAGE_MASK;
		size = round_page(offset + size);
		va = trunc_page(va);

		pde = pmap_pde(kernel_pmap, va, &lvl);
		KASSERT(pde != NULL,
		    ("pmap_unmapbios: Invalid page entry, va: 0x%lx", va));
		KASSERT(lvl == 2, ("pmap_unmapbios: Invalid level %d", lvl));

		/* Unmap and invalidate the pages */
                for (tmpsize = 0; tmpsize < size; tmpsize += PAGE_SIZE)
			pmap_kremove(va + tmpsize);

		kva_free(va, size);
	}
}