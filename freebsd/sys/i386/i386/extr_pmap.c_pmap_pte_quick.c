#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_2__ {scalar_t__ td_pinned; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int NPTEPG ; 
 int* PADDR1 ; 
 scalar_t__ PCPU_GET (int /*<<< orphan*/ ) ; 
 int PG_A ; 
 int PG_FRAME ; 
 int PG_M ; 
 int PG_PS ; 
 int PG_RW ; 
 int PG_V ; 
 int* PMAP1 ; 
 int /*<<< orphan*/  PMAP1changed ; 
 int /*<<< orphan*/  PMAP1changedcpu ; 
 scalar_t__ PMAP1cpu ; 
 int /*<<< orphan*/  PMAP1unchanged ; 
 int /*<<< orphan*/  RA_WLOCKED ; 
 int /*<<< orphan*/  cpuid ; 
 TYPE_1__* curthread ; 
 int i386_btop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invlcaddr (int*) ; 
 scalar_t__ pmap_is_current (int /*<<< orphan*/ ) ; 
 int* pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int* vtopte (int /*<<< orphan*/ ) ; 

__attribute__((used)) static pt_entry_t *
pmap_pte_quick(pmap_t pmap, vm_offset_t va)
{
	pd_entry_t newpf;
	pd_entry_t *pde;

	pde = pmap_pde(pmap, va);
	if (*pde & PG_PS)
		return (pde);
	if (*pde != 0) {
		/* are we current address space or kernel? */
		if (pmap_is_current(pmap))
			return (vtopte(va));
		rw_assert(&pvh_global_lock, RA_WLOCKED);
		KASSERT(curthread->td_pinned > 0, ("curthread not pinned"));
		newpf = *pde & PG_FRAME;
		if ((*PMAP1 & PG_FRAME) != newpf) {
			*PMAP1 = newpf | PG_RW | PG_V | PG_A | PG_M;
#ifdef SMP
			PMAP1cpu = PCPU_GET(cpuid);
#endif
			invlcaddr(PADDR1);
			PMAP1changed++;
		} else
#ifdef SMP
		if (PMAP1cpu != PCPU_GET(cpuid)) {
			PMAP1cpu = PCPU_GET(cpuid);
			invlcaddr(PADDR1);
			PMAP1changedcpu++;
		} else
#endif
			PMAP1unchanged++;
		return (PADDR1 + (i386_btop(va) & (NPTEPG - 1)));
	}
	return (0);
}