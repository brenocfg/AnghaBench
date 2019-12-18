#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_2__* pmap_t ;
struct TYPE_4__ {scalar_t__ resident_count; } ;
struct TYPE_5__ {scalar_t__ pm_type; int /*<<< orphan*/  pm_pkru; int /*<<< orphan*/ * pm_pml4u; scalar_t__* pm_pml4; int /*<<< orphan*/  pm_active; int /*<<< orphan*/  pm_root; TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int CPUID_STDEXT2_PKU ; 
 int CPU_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMAP_TO_PHYS (int /*<<< orphan*/ ) ; 
 int DMPML4I ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int KPML4BASE ; 
 int LMSPML4I ; 
 int NKPML4E ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 size_t PML4PML4I ; 
 scalar_t__ PT_X86 ; 
 int cpu_stdext_feature2 ; 
 int lm_ents ; 
 int ndmpdpphys ; 
 int /*<<< orphan*/  rangeset_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ ) ; 
 int vm_radix_is_empty (int /*<<< orphan*/ *) ; 

void
pmap_release(pmap_t pmap)
{
	vm_page_t m;
	int i;

	KASSERT(pmap->pm_stats.resident_count == 0,
	    ("pmap_release: pmap resident count %ld != 0",
	    pmap->pm_stats.resident_count));
	KASSERT(vm_radix_is_empty(&pmap->pm_root),
	    ("pmap_release: pmap has reserved page table page(s)"));
	KASSERT(CPU_EMPTY(&pmap->pm_active),
	    ("releasing active pmap %p", pmap));

	m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pmap->pm_pml4));

	for (i = 0; i < NKPML4E; i++)	/* KVA */
		pmap->pm_pml4[KPML4BASE + i] = 0;
	for (i = 0; i < ndmpdpphys; i++)/* Direct Map */
		pmap->pm_pml4[DMPML4I + i] = 0;
	pmap->pm_pml4[PML4PML4I] = 0;	/* Recursive Mapping */
	for (i = 0; i < lm_ents; i++)	/* Large Map */
		pmap->pm_pml4[LMSPML4I + i] = 0;

	vm_page_unwire_noq(m);
	vm_page_free_zero(m);

	if (pmap->pm_pml4u != NULL) {
		m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)pmap->pm_pml4u));
		vm_page_unwire_noq(m);
		vm_page_free(m);
	}
	if (pmap->pm_type == PT_X86 &&
	    (cpu_stdext_feature2 & CPUID_STDEXT2_PKU) != 0)
		rangeset_fini(&pmap->pm_pkru);
}