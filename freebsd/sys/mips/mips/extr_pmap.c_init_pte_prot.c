#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int pt_entry_t ;
struct TYPE_3__ {int oflags; } ;

/* Variables and functions */
 int PTE_D ; 
 int PTE_RO ; 
 int PTE_V ; 
 int VM_PROT_WRITE ; 
 int VPO_UNMANAGED ; 

__attribute__((used)) static pt_entry_t
init_pte_prot(vm_page_t m, vm_prot_t access, vm_prot_t prot)
{
	pt_entry_t rw;

	if (!(prot & VM_PROT_WRITE))
		rw = PTE_V | PTE_RO;
	else if ((m->oflags & VPO_UNMANAGED) == 0) {
		if ((access & VM_PROT_WRITE) != 0)
			rw = PTE_V | PTE_D;
		else
			rw = PTE_V;
	} else
		/* Needn't emulate a modified bit for unmanaged pages. */
		rw = PTE_V | PTE_D;
	return (rw);
}