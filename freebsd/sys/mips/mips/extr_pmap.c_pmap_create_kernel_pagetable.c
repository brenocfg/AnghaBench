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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_5__ {TYPE_1__* pm_asid; int /*<<< orphan*/  pm_pvchunk; int /*<<< orphan*/  pm_active; scalar_t__* pm_segtab; } ;
struct TYPE_4__ {scalar_t__ gen; int /*<<< orphan*/  asid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FILL (int /*<<< orphan*/ *) ; 
 int NKPT ; 
 int NPDEPG ; 
 int NPTEPG ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_ASID_RESERVED ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_2__*) ; 
 int /*<<< orphan*/  PTE_G ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_MIN_KERNEL_ADDRESS ; 
 int howmany (int,int) ; 
 TYPE_2__* kernel_pmap ; 
 scalar_t__* kernel_segmap ; 
 int kernel_vm_end ; 
 int nkpt ; 
 int pmap_seg_index (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_steal_memory (int) ; 

__attribute__((used)) static void
pmap_create_kernel_pagetable(void)
{
	int i, j;
	vm_offset_t ptaddr;
	pt_entry_t *pte;
#ifdef __mips_n64
	pd_entry_t *pde;
	vm_offset_t pdaddr;
	int npt, npde;
#endif

	/*
	 * Allocate segment table for the kernel
	 */
	kernel_segmap = (pd_entry_t *)pmap_steal_memory(PAGE_SIZE);

	/*
	 * Allocate second level page tables for the kernel
	 */
#ifdef __mips_n64
	npde = howmany(NKPT, NPDEPG);
	pdaddr = pmap_steal_memory(PAGE_SIZE * npde);
#endif
	nkpt = NKPT;
	ptaddr = pmap_steal_memory(PAGE_SIZE * nkpt);

	/*
	 * The R[4-7]?00 stores only one copy of the Global bit in the
	 * translation lookaside buffer for each 2 page entry. Thus invalid
	 * entrys must have the Global bit set so when Entry LO and Entry HI
	 * G bits are anded together they will produce a global bit to store
	 * in the tlb.
	 */
	for (i = 0, pte = (pt_entry_t *)ptaddr; i < (nkpt * NPTEPG); i++, pte++)
		*pte = PTE_G;

#ifdef __mips_n64
	for (i = 0,  npt = nkpt; npt > 0; i++) {
		kernel_segmap[i] = (pd_entry_t)(pdaddr + i * PAGE_SIZE);
		pde = (pd_entry_t *)kernel_segmap[i];

		for (j = 0; j < NPDEPG && npt > 0; j++, npt--)
			pde[j] = (pd_entry_t)(ptaddr + (i * NPDEPG + j) * PAGE_SIZE);
	}
#else
	for (i = 0, j = pmap_seg_index(VM_MIN_KERNEL_ADDRESS); i < nkpt; i++, j++)
		kernel_segmap[j] = (pd_entry_t)(ptaddr + (i * PAGE_SIZE));
#endif

	PMAP_LOCK_INIT(kernel_pmap);
	kernel_pmap->pm_segtab = kernel_segmap;
	CPU_FILL(&kernel_pmap->pm_active);
	TAILQ_INIT(&kernel_pmap->pm_pvchunk);
	kernel_pmap->pm_asid[0].asid = PMAP_ASID_RESERVED;
	kernel_pmap->pm_asid[0].gen = 0;
	kernel_vm_end += nkpt * NPTEPG * PAGE_SIZE;
}