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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int L2_OFFSET ; 
 int L2_SHIFT ; 
 int L3_OFFSET ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_PPN1_S ; 
 int PTE_RX ; 
 int PTE_TO_PHYS (int) ; 
 int* pmap_l2 (int /*<<< orphan*/ ,int) ; 
 int* pmap_l2_to_l3 (int*,int) ; 
 int pmap_load (int*) ; 

vm_paddr_t 
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	pd_entry_t *l2p, l2;
	pt_entry_t *l3p, l3;
	vm_paddr_t pa;

	pa = 0;
	PMAP_LOCK(pmap);
	/*
	 * Start with the l2 tabel. We are unable to allocate
	 * pages in the l1 table.
	 */
	l2p = pmap_l2(pmap, va);
	if (l2p != NULL) {
		l2 = pmap_load(l2p);
		if ((l2 & PTE_RX) == 0) {
			l3p = pmap_l2_to_l3(l2p, va);
			if (l3p != NULL) {
				l3 = pmap_load(l3p);
				pa = PTE_TO_PHYS(l3);
				pa |= (va & L3_OFFSET);
			}
		} else {
			/* L2 is superpages */
			pa = (l2 >> PTE_PPN1_S) << L2_SHIFT;
			pa |= (va & L2_OFFSET);
		}
	}
	PMAP_UNLOCK(pmap);
	return (pa);
}