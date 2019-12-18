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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int TLBLO_PTE_TO_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int) ; 

vm_paddr_t
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	pt_entry_t *pte;
	vm_offset_t retval = 0;

	PMAP_LOCK(pmap);
	pte = pmap_pte(pmap, va);
	if (pte) {
		retval = TLBLO_PTE_TO_PA(*pte) | (va & PAGE_MASK);
	}
	PMAP_UNLOCK(pmap);
	return (retval);
}