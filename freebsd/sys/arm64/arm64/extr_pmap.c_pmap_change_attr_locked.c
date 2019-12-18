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
typedef  int pt_entry_t ;

/* Variables and functions */
 int ATTR_IDX (int) ; 
 int ATTR_IDX_MASK ; 
 int ATTR_XN ; 
 int DEVICE_MEMORY ; 
 int EINVAL ; 
 scalar_t__ L1_OFFSET ; 
 scalar_t__ L1_SIZE ; 
 scalar_t__ L2_OFFSET ; 
 scalar_t__ L2_SIZE ; 
 int /*<<< orphan*/  L3_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VIRT_IN_DMAP (scalar_t__) ; 
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 int VM_MEMATTR_UNCACHEABLE ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  cpu_dcache_wbinv_range (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int* pmap_demote_l1 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int* pmap_demote_l2 (int /*<<< orphan*/ ,int*,scalar_t__) ; 
 int* pmap_l1_to_l2 (int*,scalar_t__) ; 
 int* pmap_l2_to_l3 (int*,scalar_t__) ; 
 int pmap_load (int*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pmap_update_entry (int /*<<< orphan*/ ,int*,int,scalar_t__,scalar_t__) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

__attribute__((used)) static int
pmap_change_attr_locked(vm_offset_t va, vm_size_t size, int mode)
{
	vm_offset_t base, offset, tmpva;
	pt_entry_t l3, *pte, *newpte;
	int lvl;

	PMAP_LOCK_ASSERT(kernel_pmap, MA_OWNED);
	base = trunc_page(va);
	offset = va & PAGE_MASK;
	size = round_page(offset + size);

	if (!VIRT_IN_DMAP(base) &&
	    !(base >= VM_MIN_KERNEL_ADDRESS && base < VM_MAX_KERNEL_ADDRESS))
		return (EINVAL);

	for (tmpva = base; tmpva < base + size; ) {
		pte = pmap_pte(kernel_pmap, tmpva, &lvl);
		if (pte == NULL)
			return (EINVAL);

		if ((pmap_load(pte) & ATTR_IDX_MASK) == ATTR_IDX(mode)) {
			/*
			 * We already have the correct attribute,
			 * ignore this entry.
			 */
			switch (lvl) {
			default:
				panic("Invalid DMAP table level: %d\n", lvl);
			case 1:
				tmpva = (tmpva & ~L1_OFFSET) + L1_SIZE;
				break;
			case 2:
				tmpva = (tmpva & ~L2_OFFSET) + L2_SIZE;
				break;
			case 3:
				tmpva += PAGE_SIZE;
				break;
			}
		} else {
			/*
			 * Split the entry to an level 3 table, then
			 * set the new attribute.
			 */
			switch (lvl) {
			default:
				panic("Invalid DMAP table level: %d\n", lvl);
			case 1:
				newpte = pmap_demote_l1(kernel_pmap, pte,
				    tmpva & ~L1_OFFSET);
				if (newpte == NULL)
					return (EINVAL);
				pte = pmap_l1_to_l2(pte, tmpva);
			case 2:
				newpte = pmap_demote_l2(kernel_pmap, pte,
				    tmpva);
				if (newpte == NULL)
					return (EINVAL);
				pte = pmap_l2_to_l3(pte, tmpva);
			case 3:
				/* Update the entry */
				l3 = pmap_load(pte);
				l3 &= ~ATTR_IDX_MASK;
				l3 |= ATTR_IDX(mode);
				if (mode == DEVICE_MEMORY)
					l3 |= ATTR_XN;

				pmap_update_entry(kernel_pmap, pte, l3, tmpva,
				    PAGE_SIZE);

				/*
				 * If moving to a non-cacheable entry flush
				 * the cache.
				 */
				if (mode == VM_MEMATTR_UNCACHEABLE)
					cpu_dcache_wbinv_range(tmpva, L3_SIZE);

				break;
			}
			tmpva += PAGE_SIZE;
		}
	}

	return (0);
}