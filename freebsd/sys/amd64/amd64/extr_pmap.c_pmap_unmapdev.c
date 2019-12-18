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
struct pmap_preinit_mapping {scalar_t__ va; scalar_t__ sz; scalar_t__ mode; scalar_t__ pa; } ;

/* Variables and functions */
 scalar_t__ DMAP_MAX_ADDRESS ; 
 scalar_t__ DMAP_MIN_ADDRESS ; 
 scalar_t__ PAGE_MASK ; 
 int PMAP_PREINIT_MAPPING_COUNT ; 
 int /*<<< orphan*/  kva_free (scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_initialized ; 
 struct pmap_preinit_mapping* pmap_preinit_mapping ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 scalar_t__ virtual_avail ; 

void
pmap_unmapdev(vm_offset_t va, vm_size_t size)
{
	struct pmap_preinit_mapping *ppim;
	vm_offset_t offset;
	int i;

	/* If we gave a direct map region in pmap_mapdev, do nothing */
	if (va >= DMAP_MIN_ADDRESS && va < DMAP_MAX_ADDRESS)
		return;
	offset = va & PAGE_MASK;
	size = round_page(offset + size);
	va = trunc_page(va);
	for (i = 0; i < PMAP_PREINIT_MAPPING_COUNT; i++) {
		ppim = pmap_preinit_mapping + i;
		if (ppim->va == va && ppim->sz == size) {
			if (pmap_initialized)
				return;
			ppim->pa = 0;
			ppim->va = 0;
			ppim->sz = 0;
			ppim->mode = 0;
			if (va + size == virtual_avail)
				virtual_avail = va;
			return;
		}
	}
	if (pmap_initialized)
		kva_free(va, size);
}