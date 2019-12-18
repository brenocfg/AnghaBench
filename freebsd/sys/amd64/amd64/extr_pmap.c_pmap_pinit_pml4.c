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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int pml4_entry_t ;
struct TYPE_2__ {int* pm_pml4; } ;

/* Variables and functions */
 int DMPDPphys ; 
 int DMPML4I ; 
 int KPDPphys ; 
 int KPML4BASE ; 
 int LMSPML4I ; 
 int NKPML4E ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 size_t PML4PML4I ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 TYPE_1__* kernel_pmap ; 
 int lm_ents ; 
 int ndmpdpphys ; 
 int ptoa (int) ; 

void
pmap_pinit_pml4(vm_page_t pml4pg)
{
	pml4_entry_t *pm_pml4;
	int i;

	pm_pml4 = (pml4_entry_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(pml4pg));

	/* Wire in kernel global address entries. */
	for (i = 0; i < NKPML4E; i++) {
		pm_pml4[KPML4BASE + i] = (KPDPphys + ptoa(i)) | X86_PG_RW |
		    X86_PG_V;
	}
	for (i = 0; i < ndmpdpphys; i++) {
		pm_pml4[DMPML4I + i] = (DMPDPphys + ptoa(i)) | X86_PG_RW |
		    X86_PG_V;
	}

	/* install self-referential address mapping entry(s) */
	pm_pml4[PML4PML4I] = VM_PAGE_TO_PHYS(pml4pg) | X86_PG_V | X86_PG_RW |
	    X86_PG_A | X86_PG_M;

	/* install large map entries if configured */
	for (i = 0; i < lm_ents; i++)
		pm_pml4[LMSPML4I + i] = kernel_pmap->pm_pml4[LMSPML4I + i];
}