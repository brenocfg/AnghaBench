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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 scalar_t__ MIPS_DIRECT_MAPPABLE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_G ; 
 int /*<<< orphan*/  crashdumpva ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pmap_kenter_temporary_free(vm_paddr_t pa)
{
 #ifndef __mips_n64    /* XXX : to be converted to new style */
	pt_entry_t *pte;
 #endif
	if (MIPS_DIRECT_MAPPABLE(pa)) {
		/* nothing to do for this case */
		return;
	}
#ifndef __mips_n64    /* XXX : to be converted to new style */
	pte = pmap_pte(kernel_pmap, crashdumpva);
	*pte = PTE_G;
	pmap_invalidate_page(kernel_pmap, crashdumpva);
#endif
}