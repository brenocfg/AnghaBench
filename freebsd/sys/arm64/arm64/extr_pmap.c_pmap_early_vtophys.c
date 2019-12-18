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
typedef  int pt_entry_t ;

/* Variables and functions */
 int ATTR_MASK ; 
 int L2_OFFSET ; 
 int* pmap_early_page_idx (int,int,size_t*,size_t*) ; 

__attribute__((used)) static vm_paddr_t
pmap_early_vtophys(vm_offset_t l1pt, vm_offset_t va)
{
	u_int l1_slot, l2_slot;
	pt_entry_t *l2;

	l2 = pmap_early_page_idx(l1pt, va, &l1_slot, &l2_slot);

	return ((l2[l2_slot] & ~ATTR_MASK) + (va & L2_OFFSET));
}