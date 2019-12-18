#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  scalar_t__ pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  pat_mode; } ;
struct TYPE_6__ {int oflags; TYPE_1__ md; } ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_U ; 
 int PG_V ; 
 int PMAP_ENTER_NORECLAIM ; 
 int PMAP_ENTER_NOREPLACE ; 
 int PMAP_ENTER_NOSLEEP ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (scalar_t__,int /*<<< orphan*/ ) ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int VM_PROT_EXECUTE ; 
 int VPO_UNMANAGED ; 
 int /*<<< orphan*/  i386_read_exec ; 
 scalar_t__ kernel_pmap ; 
 int pg_nx ; 
 int pmap_cache_bits (scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmap_enter_pde (scalar_t__,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
pmap_enter_4mpage(pmap_t pmap, vm_offset_t va, vm_page_t m, vm_prot_t prot)
{
	pd_entry_t newpde;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	newpde = VM_PAGE_TO_PHYS(m) | pmap_cache_bits(pmap, m->md.pat_mode, 1) |
	    PG_PS | PG_V;
	if ((m->oflags & VPO_UNMANAGED) == 0)
		newpde |= PG_MANAGED;
#ifdef PMAP_PAE_COMP
	if ((prot & VM_PROT_EXECUTE) == 0 && !i386_read_exec)
		newpde |= pg_nx;
#endif
	if (pmap != kernel_pmap)
		newpde |= PG_U;
	return (pmap_enter_pde(pmap, va, newpde, PMAP_ENTER_NOSLEEP |
	    PMAP_ENTER_NOREPLACE | PMAP_ENTER_NORECLAIM, NULL) ==
	    KERN_SUCCESS);
}