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
typedef  int /*<<< orphan*/  pt2_entry_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE1_OFFSET ; 
 int PTE2_OFFSET ; 
 int /*<<< orphan*/  pmap_pte1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pmap_pte2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_pte2_release (int /*<<< orphan*/ *) ; 
 scalar_t__ pte1_is_link (int /*<<< orphan*/ ) ; 
 scalar_t__ pte1_is_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_load (int /*<<< orphan*/ ) ; 
 int pte1_pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_load (int /*<<< orphan*/ *) ; 
 int pte2_pa (int /*<<< orphan*/ ) ; 

vm_paddr_t
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	vm_paddr_t pa;
	pt1_entry_t pte1;
	pt2_entry_t *pte2p;

	PMAP_LOCK(pmap);
	pte1 = pte1_load(pmap_pte1(pmap, va));
	if (pte1_is_section(pte1))
		pa = pte1_pa(pte1) | (va & PTE1_OFFSET);
	else if (pte1_is_link(pte1)) {
		pte2p = pmap_pte2(pmap, va);
		pa = pte2_pa(pte2_load(pte2p)) | (va & PTE2_OFFSET);
		pmap_pte2_release(pte2p);
	} else
		pa = 0;
	PMAP_UNLOCK(pmap);
	return (pa);
}