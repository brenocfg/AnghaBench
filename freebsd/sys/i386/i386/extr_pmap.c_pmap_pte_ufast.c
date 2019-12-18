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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int NPTEPG ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int PG_A ; 
 int PG_FRAME ; 
 int PG_M ; 
 int PG_RW ; 
 int PG_V ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invlcaddr (void*) ; 
 int /*<<< orphan*/  pmap_eh_ptep ; 
 int /*<<< orphan*/  pmap_eh_va ; 

__attribute__((used)) static pt_entry_t
pmap_pte_ufast(pmap_t pmap, vm_offset_t va, pd_entry_t pde)
{
	pt_entry_t *eh_ptep, pte, *ptep;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	pde &= PG_FRAME;
	critical_enter();
	eh_ptep = (pt_entry_t *)PCPU_GET(pmap_eh_ptep);
	if ((*eh_ptep & PG_FRAME) != pde) {
		*eh_ptep = pde | PG_RW | PG_V | PG_A | PG_M;
		invlcaddr((void *)PCPU_GET(pmap_eh_va));
	}
	ptep = (pt_entry_t *)PCPU_GET(pmap_eh_va) + (i386_btop(va) &
	    (NPTEPG - 1));
	pte = *ptep;
	critical_exit();
	return (pte);
}