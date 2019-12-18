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
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 scalar_t__ NBPDR ; 
 int PG_PROMOTED ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void
pmap_invalidate_pde_page(pmap_t pmap, vm_offset_t va, pd_entry_t pde)
{

	/*
	 * When the PDE has PG_PROMOTED set, the 2MB page mapping was created
	 * by a promotion that did not invalidate the 512 4KB page mappings
	 * that might exist in the TLB.  Consequently, at this point, the TLB
	 * may hold both 4KB and 2MB page mappings for the address range [va,
	 * va + NBPDR).  Therefore, the entire range must be invalidated here.
	 * In contrast, when PG_PROMOTED is clear, the TLB will not hold any
	 * 4KB page mappings for the address range [va, va + NBPDR), and so a
	 * single INVLPG suffices to invalidate the 2MB page mapping from the
	 * TLB.
	 */
	if ((pde & PG_PROMOTED) != 0)
		pmap_invalidate_range(pmap, va, va + NBPDR - 1);
	else
		pmap_invalidate_page(pmap, va);
}