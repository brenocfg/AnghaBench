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
typedef  scalar_t__ vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int uint64_t ;
typedef  int pml4_entry_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int AMDID_PAGE1GB ; 
 int DMPDPphys ; 
 int DMPDphys ; 
 int DMPML4I ; 
 scalar_t__ KERNBASE ; 
 int KERNend ; 
 int KPDPI ; 
 int KPDPphys ; 
 int KPDphys ; 
 int KPML4BASE ; 
 int KPML4I ; 
 int KPML4phys ; 
 int KPTphys ; 
 int Maxmem ; 
 int /*<<< orphan*/  NBPDP ; 
 int NBPML4 ; 
 int NDMPML4E ; 
 int NKPDPE (int) ; 
 int NKPML4E ; 
 int NPDEPG ; 
 int /*<<< orphan*/  NPDPEPG ; 
 scalar_t__ PDPSHIFT ; 
 int PDRSHIFT ; 
 int PG_PS ; 
 size_t PML4PML4I ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 void* allocpages (scalar_t__*,int) ; 
 int amd_feature ; 
 int atop (int) ; 
 int bootaddr_rwx (int) ; 
 scalar_t__ brwsection ; 
 scalar_t__ dmaplimit ; 
 int howmany (int,int /*<<< orphan*/ ) ; 
 int ndmpdp ; 
 int ndmpdpphys ; 
 int nkpt ; 
 int /*<<< orphan*/  nkpt_init (scalar_t__) ; 
 int pg_g ; 
 int pg_nx ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int ptoa (int) ; 
 scalar_t__ round_2mpage (int) ; 

__attribute__((used)) static void
create_pagetables(vm_paddr_t *firstaddr)
{
	int i, j, ndm1g, nkpdpe, nkdmpde;
	pd_entry_t *pd_p;
	pdp_entry_t *pdp_p;
	pml4_entry_t *p4_p;
	uint64_t DMPDkernphys;

	/* Allocate page table pages for the direct map */
	ndmpdp = howmany(ptoa(Maxmem), NBPDP);
	if (ndmpdp < 4)		/* Minimum 4GB of dirmap */
		ndmpdp = 4;
	ndmpdpphys = howmany(ndmpdp, NPDPEPG);
	if (ndmpdpphys > NDMPML4E) {
		/*
		 * Each NDMPML4E allows 512 GB, so limit to that,
		 * and then readjust ndmpdp and ndmpdpphys.
		 */
		printf("NDMPML4E limits system to %d GB\n", NDMPML4E * 512);
		Maxmem = atop(NDMPML4E * NBPML4);
		ndmpdpphys = NDMPML4E;
		ndmpdp = NDMPML4E * NPDEPG;
	}
	DMPDPphys = allocpages(firstaddr, ndmpdpphys);
	ndm1g = 0;
	if ((amd_feature & AMDID_PAGE1GB) != 0) {
		/*
		 * Calculate the number of 1G pages that will fully fit in
		 * Maxmem.
		 */
		ndm1g = ptoa(Maxmem) >> PDPSHIFT;

		/*
		 * Allocate 2M pages for the kernel. These will be used in
		 * place of the first one or more 1G pages from ndm1g.
		 */
		nkdmpde = howmany((vm_offset_t)(brwsection - KERNBASE), NBPDP);
		DMPDkernphys = allocpages(firstaddr, nkdmpde);
	}
	if (ndm1g < ndmpdp)
		DMPDphys = allocpages(firstaddr, ndmpdp - ndm1g);
	dmaplimit = (vm_paddr_t)ndmpdp << PDPSHIFT;

	/* Allocate pages */
	KPML4phys = allocpages(firstaddr, 1);
	KPDPphys = allocpages(firstaddr, NKPML4E);

	/*
	 * Allocate the initial number of kernel page table pages required to
	 * bootstrap.  We defer this until after all memory-size dependent
	 * allocations are done (e.g. direct map), so that we don't have to
	 * build in too much slop in our estimate.
	 *
	 * Note that when NKPML4E > 1, we have an empty page underneath
	 * all but the KPML4I'th one, so we need NKPML4E-1 extra (zeroed)
	 * pages.  (pmap_enter requires a PD page to exist for each KPML4E.)
	 */
	nkpt_init(*firstaddr);
	nkpdpe = NKPDPE(nkpt);

	KPTphys = allocpages(firstaddr, nkpt);
	KPDphys = allocpages(firstaddr, nkpdpe);

	/*
	 * Connect the zero-filled PT pages to their PD entries.  This
	 * implicitly maps the PT pages at their correct locations within
	 * the PTmap.
	 */
	pd_p = (pd_entry_t *)KPDphys;
	for (i = 0; i < nkpt; i++)
		pd_p[i] = (KPTphys + ptoa(i)) | X86_PG_RW | X86_PG_V;

	/*
	 * Map from physical address zero to the end of loader preallocated
	 * memory using 2MB pages.  This replaces some of the PD entries
	 * created above.
	 */
	for (i = 0; (i << PDRSHIFT) < KERNend; i++)
		/* Preset PG_M and PG_A because demotion expects it. */
		pd_p[i] = (i << PDRSHIFT) | X86_PG_V | PG_PS | pg_g |
		    X86_PG_M | X86_PG_A | bootaddr_rwx(i << PDRSHIFT);

	/*
	 * Because we map the physical blocks in 2M pages, adjust firstaddr
	 * to record the physical blocks we've actually mapped into kernel
	 * virtual address space.
	 */
	if (*firstaddr < round_2mpage(KERNend))
		*firstaddr = round_2mpage(KERNend);

	/* And connect up the PD to the PDP (leaving room for L4 pages) */
	pdp_p = (pdp_entry_t *)(KPDPphys + ptoa(KPML4I - KPML4BASE));
	for (i = 0; i < nkpdpe; i++)
		pdp_p[i + KPDPI] = (KPDphys + ptoa(i)) | X86_PG_RW | X86_PG_V;

	/*
	 * Now, set up the direct map region using 2MB and/or 1GB pages.  If
	 * the end of physical memory is not aligned to a 1GB page boundary,
	 * then the residual physical memory is mapped with 2MB pages.  Later,
	 * if pmap_mapdev{_attr}() uses the direct map for non-write-back
	 * memory, pmap_change_attr() will demote any 2MB or 1GB page mappings
	 * that are partially used. 
	 */
	pd_p = (pd_entry_t *)DMPDphys;
	for (i = NPDEPG * ndm1g, j = 0; i < NPDEPG * ndmpdp; i++, j++) {
		pd_p[j] = (vm_paddr_t)i << PDRSHIFT;
		/* Preset PG_M and PG_A because demotion expects it. */
		pd_p[j] |= X86_PG_RW | X86_PG_V | PG_PS | pg_g |
		    X86_PG_M | X86_PG_A | pg_nx;
	}
	pdp_p = (pdp_entry_t *)DMPDPphys;
	for (i = 0; i < ndm1g; i++) {
		pdp_p[i] = (vm_paddr_t)i << PDPSHIFT;
		/* Preset PG_M and PG_A because demotion expects it. */
		pdp_p[i] |= X86_PG_RW | X86_PG_V | PG_PS | pg_g |
		    X86_PG_M | X86_PG_A | pg_nx;
	}
	for (j = 0; i < ndmpdp; i++, j++) {
		pdp_p[i] = DMPDphys + ptoa(j);
		pdp_p[i] |= X86_PG_RW | X86_PG_V | pg_nx;
	}

	/*
	 * Instead of using a 1G page for the memory containing the kernel,
	 * use 2M pages with read-only and no-execute permissions.  (If using 1G
	 * pages, this will partially overwrite the PDPEs above.)
	 */
	if (ndm1g) {
		pd_p = (pd_entry_t *)DMPDkernphys;
		for (i = 0; i < (NPDEPG * nkdmpde); i++)
			pd_p[i] = (i << PDRSHIFT) | X86_PG_V | PG_PS | pg_g |
			    X86_PG_M | X86_PG_A | pg_nx |
			    bootaddr_rwx(i << PDRSHIFT);
		for (i = 0; i < nkdmpde; i++)
			pdp_p[i] = (DMPDkernphys + ptoa(i)) | X86_PG_RW |
			    X86_PG_V | pg_nx;
	}

	/* And recursively map PML4 to itself in order to get PTmap */
	p4_p = (pml4_entry_t *)KPML4phys;
	p4_p[PML4PML4I] = KPML4phys;
	p4_p[PML4PML4I] |= X86_PG_RW | X86_PG_V | pg_nx;

	/* Connect the Direct Map slot(s) up to the PML4. */
	for (i = 0; i < ndmpdpphys; i++) {
		p4_p[DMPML4I + i] = DMPDPphys + ptoa(i);
		p4_p[DMPML4I + i] |= X86_PG_RW | X86_PG_V | pg_nx;
	}

	/* Connect the KVA slots up to the PML4 */
	for (i = 0; i < NKPML4E; i++) {
		p4_p[KPML4BASE + i] = KPDPphys + ptoa(i);
		p4_p[KPML4BASE + i] |= X86_PG_RW | X86_PG_V;
	}
}