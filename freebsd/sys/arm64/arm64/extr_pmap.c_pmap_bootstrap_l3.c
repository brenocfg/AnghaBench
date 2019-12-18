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
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int ATTR_UXN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L2_OFFSET ; 
 scalar_t__ L2_SIZE ; 
 int L2_TABLE ; 
 size_t Ln_ENTRIES ; 
 int Ln_TABLE_MASK ; 
 int PAGE_SIZE ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 int pmap_early_vtophys (int,int) ; 
 int /*<<< orphan*/ * pmap_l2 (int /*<<< orphan*/ ,int) ; 
 size_t pmap_l2_index (int) ; 
 int /*<<< orphan*/  pmap_store (int /*<<< orphan*/ *,int) ; 
 scalar_t__ rounddown2 (uintptr_t,int) ; 

__attribute__((used)) static vm_offset_t
pmap_bootstrap_l3(vm_offset_t l1pt, vm_offset_t va, vm_offset_t l3_start)
{
	vm_offset_t l3pt;
	vm_paddr_t pa;
	pd_entry_t *l2;
	u_int l2_slot;

	KASSERT((va & L2_OFFSET) == 0, ("Invalid virtual address"));

	l2 = pmap_l2(kernel_pmap, va);
	l2 = (pd_entry_t *)rounddown2((uintptr_t)l2, PAGE_SIZE);
	l2_slot = pmap_l2_index(va);
	l3pt = l3_start;

	for (; va < VM_MAX_KERNEL_ADDRESS; l2_slot++, va += L2_SIZE) {
		KASSERT(l2_slot < Ln_ENTRIES, ("Invalid L2 index"));

		pa = pmap_early_vtophys(l1pt, l3pt);
		pmap_store(&l2[l2_slot],
		    (pa & ~Ln_TABLE_MASK) | ATTR_UXN | L2_TABLE);
		l3pt += PAGE_SIZE;
	}

	/* Clean the L2 page table */
	memset((void *)l3_start, 0, l3pt - l3_start);

	return l3pt;
}