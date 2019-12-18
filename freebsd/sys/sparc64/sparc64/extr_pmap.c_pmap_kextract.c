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
struct tte {int tte_data; } ;

/* Variables and functions */
 int TD_V ; 
 int TLB_DIRECT_TO_PHYS (int) ; 
 int TTE_GET_PA (struct tte*) ; 
 int TTE_GET_PAGE_MASK (struct tte*) ; 
 int VM_MIN_DIRECT_ADDRESS ; 
 struct tte* tsb_kvtotte (int) ; 

vm_paddr_t
pmap_kextract(vm_offset_t va)
{
	struct tte *tp;

	if (va >= VM_MIN_DIRECT_ADDRESS)
		return (TLB_DIRECT_TO_PHYS(va));
	tp = tsb_kvtotte(va);
	if ((tp->tte_data & TD_V) == 0)
		return (0);
	return (TTE_GET_PA(tp) | (va & TTE_GET_PAGE_MASK(tp)));
}