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
typedef  int pt2_entry_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;

/* Variables and functions */
 int ATTR_TO_L2 (int /*<<< orphan*/ ) ; 
 int PTE1_OFFSET ; 
 int PTE2_V ; 
 int /*<<< orphan*/  kern_pte1 (int) ; 
 int /*<<< orphan*/  pt2map_entry (int) ; 
 scalar_t__ pte1_is_link (int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ ) ; 
 int pte1_pa (int /*<<< orphan*/ ) ; 
 int pte2_load (int /*<<< orphan*/ ) ; 
 int pte2_pa (int) ; 

vm_paddr_t
pmap_dump_kextract(vm_offset_t va, pt2_entry_t *pte2p)
{
	vm_paddr_t pa;
	pt1_entry_t pte1;
	pt2_entry_t pte2;

	pte1 = pte1_load(kern_pte1(va));
	if (pte1_is_section(pte1)) {
		pa = pte1_pa(pte1) | (va & PTE1_OFFSET);
		pte2 = pa | ATTR_TO_L2(pte1) | PTE2_V;
	} else if (pte1_is_link(pte1)) {
		pte2 = pte2_load(pt2map_entry(va));
		pa = pte2_pa(pte2);
	} else {
		pte2 = 0;
		pa = 0;
	}
	if (pte2p != NULL)
		*pte2p = pte2;
	return (pa);
}