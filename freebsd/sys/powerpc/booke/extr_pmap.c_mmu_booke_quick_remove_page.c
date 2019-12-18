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
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ pte_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_exit () ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__* pte_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  qmap_addr ; 

__attribute__((used)) static void
mmu_booke_quick_remove_page(mmu_t mmu, vm_offset_t addr)
{
#ifndef __powerpc64__
	pte_t *pte;

	pte = pte_find(mmu, kernel_pmap, addr);

	KASSERT(PCPU_GET(qmap_addr) == addr,
	    ("mmu_booke_quick_remove_page: invalid address"));
	KASSERT(*pte != 0,
	    ("mmu_booke_quick_remove_page: PTE not in use"));

	*pte = 0;
	critical_exit();
#endif
}