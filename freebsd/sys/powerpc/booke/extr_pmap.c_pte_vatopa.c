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
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 scalar_t__ PTE_ISVALID (int /*<<< orphan*/ *) ; 
 int PTE_PA (int /*<<< orphan*/ *) ; 
 int PTE_PA_MASK ; 
 int /*<<< orphan*/ * pte_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static vm_paddr_t
pte_vatopa(mmu_t mmu, pmap_t pmap, vm_offset_t va)
{
	vm_paddr_t pa = 0;
	pte_t *pte;

	pte = pte_find(mmu, pmap, va);
	if ((pte != NULL) && PTE_ISVALID(pte))
		pa = (PTE_PA(pte) | (va & PTE_PA_MASK));
	return (pa);
}