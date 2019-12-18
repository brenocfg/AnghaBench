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
typedef  size_t vm_offset_t ;
typedef  size_t u_int ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 size_t L1_SHIFT ; 
 size_t Ln_ADDR_MASK ; 
 int PTE_RX ; 
 scalar_t__ init_pt_va ; 
 size_t pmap_l2_index (size_t) ; 

__attribute__((used)) static pt_entry_t *
pmap_early_page_idx(vm_offset_t l1pt, vm_offset_t va, u_int *l1_slot,
    u_int *l2_slot)
{
	pt_entry_t *l2;
	pd_entry_t *l1;

	l1 = (pd_entry_t *)l1pt;
	*l1_slot = (va >> L1_SHIFT) & Ln_ADDR_MASK;

	/* Check locore has used a table L1 map */
	KASSERT((l1[*l1_slot] & PTE_RX) == 0,
		("Invalid bootstrap L1 table"));

	/* Find the address of the L2 table */
	l2 = (pt_entry_t *)init_pt_va;
	*l2_slot = pmap_l2_index(va);

	return (l2);
}