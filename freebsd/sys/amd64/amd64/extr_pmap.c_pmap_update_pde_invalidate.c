#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_5__ {scalar_t__ pm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_PS ; 
 scalar_t__ PT_X86 ; 
 int /*<<< orphan*/  invlpg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invltlb () ; 
 int /*<<< orphan*/  invltlb_glob () ; 
 int pmap_global_bit (TYPE_1__*) ; 
 scalar_t__ pmap_type_guest (TYPE_1__*) ; 

__attribute__((used)) static void
pmap_update_pde_invalidate(pmap_t pmap, vm_offset_t va, pd_entry_t newpde)
{
	pt_entry_t PG_G;

	if (pmap_type_guest(pmap))
		return;

	KASSERT(pmap->pm_type == PT_X86,
	    ("pmap_update_pde_invalidate: invalid type %d", pmap->pm_type));

	PG_G = pmap_global_bit(pmap);

	if ((newpde & PG_PS) == 0)
		/* Demotion: flush a specific 2MB page mapping. */
		invlpg(va);
	else if ((newpde & PG_G) == 0)
		/*
		 * Promotion: flush every 4KB page mapping from the TLB
		 * because there are too many to flush individually.
		 */
		invltlb();
	else {
		/*
		 * Promotion: flush every 4KB page mapping from the TLB,
		 * including any global (PG_G) mappings.
		 */
		invltlb_glob();
	}
}