#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int vmem_size_t ;
typedef  int /*<<< orphan*/  vmem_addr_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int u_long ;
struct pmap_preinit_mapping {scalar_t__ va; scalar_t__ pa; scalar_t__ sz; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int* pm_pml4; } ;
struct TYPE_13__ {int /*<<< orphan*/  pvc_list; int /*<<< orphan*/  pvc_lock; } ;
struct TYPE_12__ {int ref_count; scalar_t__ phys_addr; scalar_t__ pindex; } ;

/* Variables and functions */
 int AMDID2_FMA4 ; 
 int AMDID2_XOP ; 
 int CPUID2_AESNI ; 
 int CPUID2_AVX ; 
 int CPUID2_SSE41 ; 
 int CPUID2_SSSE3 ; 
 int CPUID2_XSAVE ; 
 int CPUID_SS ; 
 int CPUID_TO_FAMILY (int /*<<< orphan*/ ) ; 
 int CPUID_TO_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CPU_VENDOR_INTEL ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KERNBASE ; 
 scalar_t__ KERNend ; 
 scalar_t__ KPTphys ; 
 int /*<<< orphan*/  LARGEMAP_MIN_ADDRESS ; 
 int LMEPML4I ; 
 int LMSPML4I ; 
 int MAXPAGESIZES ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int M_BESTFIT ; 
 int M_WAITOK ; 
 scalar_t__ NBPDR ; 
 int NBPML4 ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PDRSHIFT ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (scalar_t__) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_5__*) ; 
 int PMAP_MEMDOM ; 
 int PMAP_PREINIT_MAPPING_COUNT ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_5__*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 scalar_t__ VM_GUEST_NO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int X86_PG_A ; 
 int X86_PG_M ; 
 int X86_PG_RW ; 
 int X86_PG_V ; 
 int amd_feature2 ; 
 int atop (int) ; 
 scalar_t__ bootverbose ; 
 int cpu_feature ; 
 int cpu_feature2 ; 
 int /*<<< orphan*/  cpu_id ; 
 scalar_t__ cpu_vendor_id ; 
 scalar_t__ dmaplimit ; 
 int /*<<< orphan*/  kernel_arena ; 
 TYPE_5__* kernel_pmap ; 
 int /*<<< orphan*/ * large_vmem ; 
 int lm_ents ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int nkpt ; 
 scalar_t__* pagesizes ; 
 int /*<<< orphan*/  panic (char*) ; 
 int pg_nx ; 
 int pg_ps_enabled ; 
 int /*<<< orphan*/  pmap_allow_2m_x_ept_recalculate () ; 
 int /*<<< orphan*/  pmap_change_attr (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_init_pv_table () ; 
 int pmap_initialized ; 
 scalar_t__ pmap_insert_pt_page (TYPE_5__*,TYPE_1__*,int) ; 
 TYPE_1__* pmap_large_map_getptp_unlocked () ; 
 scalar_t__ pmap_pde_pindex (int /*<<< orphan*/ ) ; 
 struct pmap_preinit_mapping* pmap_preinit_mapping ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ ptoa (int) ; 
 TYPE_3__* pv_chunks ; 
 int /*<<< orphan*/  qframe ; 
 int /*<<< orphan*/  qframe_mtx ; 
 scalar_t__ vm_guest ; 
 TYPE_1__* vm_page_array ; 
 size_t vm_page_array_size ; 
 int vm_page_blacklist_add (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_wire_add (int) ; 
 int vmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vmem_create (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int workaround_erratum383 ; 

void
pmap_init(void)
{
	struct pmap_preinit_mapping *ppim;
	vm_page_t m, mpte;
	int error, i, ret, skz63;

	/* L1TF, reserve page @0 unconditionally */
	vm_page_blacklist_add(0, bootverbose);

	/* Detect bare-metal Skylake Server and Skylake-X. */
	if (vm_guest == VM_GUEST_NO && cpu_vendor_id == CPU_VENDOR_INTEL &&
	    CPUID_TO_FAMILY(cpu_id) == 0x6 && CPUID_TO_MODEL(cpu_id) == 0x55) {
		/*
		 * Skylake-X errata SKZ63. Processor May Hang When
		 * Executing Code In an HLE Transaction Region between
		 * 40000000H and 403FFFFFH.
		 *
		 * Mark the pages in the range as preallocated.  It
		 * seems to be impossible to distinguish between
		 * Skylake Server and Skylake X.
		 */
		skz63 = 1;
		TUNABLE_INT_FETCH("hw.skz63_enable", &skz63);
		if (skz63 != 0) {
			if (bootverbose)
				printf("SKZ63: skipping 4M RAM starting "
				    "at physical 1G\n");
			for (i = 0; i < atop(0x400000); i++) {
				ret = vm_page_blacklist_add(0x40000000 +
				    ptoa(i), FALSE);
				if (!ret && bootverbose)
					printf("page at %#lx already used\n",
					    0x40000000 + ptoa(i));
			}
		}
	}

	/* IFU */
	pmap_allow_2m_x_ept_recalculate();

	/*
	 * Initialize the vm page array entries for the kernel pmap's
	 * page table pages.
	 */ 
	PMAP_LOCK(kernel_pmap);
	for (i = 0; i < nkpt; i++) {
		mpte = PHYS_TO_VM_PAGE(KPTphys + (i << PAGE_SHIFT));
		KASSERT(mpte >= vm_page_array &&
		    mpte < &vm_page_array[vm_page_array_size],
		    ("pmap_init: page table page is out of range"));
		mpte->pindex = pmap_pde_pindex(KERNBASE) + i;
		mpte->phys_addr = KPTphys + (i << PAGE_SHIFT);
		mpte->ref_count = 1;

		/*
		 * Collect the page table pages that were replaced by a 2MB
		 * page in create_pagetables().  They are zero filled.
		 */
		if (i << PDRSHIFT < KERNend &&
		    pmap_insert_pt_page(kernel_pmap, mpte, false))
			panic("pmap_init: pmap_insert_pt_page failed");
	}
	PMAP_UNLOCK(kernel_pmap);
	vm_wire_add(nkpt);

	/*
	 * If the kernel is running on a virtual machine, then it must assume
	 * that MCA is enabled by the hypervisor.  Moreover, the kernel must
	 * be prepared for the hypervisor changing the vendor and family that
	 * are reported by CPUID.  Consequently, the workaround for AMD Family
	 * 10h Erratum 383 is enabled if the processor's feature set does not
	 * include at least one feature that is only supported by older Intel
	 * or newer AMD processors.
	 */
	if (vm_guest != VM_GUEST_NO && (cpu_feature & CPUID_SS) == 0 &&
	    (cpu_feature2 & (CPUID2_SSSE3 | CPUID2_SSE41 | CPUID2_AESNI |
	    CPUID2_AVX | CPUID2_XSAVE)) == 0 && (amd_feature2 & (AMDID2_XOP |
	    AMDID2_FMA4)) == 0)
		workaround_erratum383 = 1;

	/*
	 * Are large page mappings enabled?
	 */
	TUNABLE_INT_FETCH("vm.pmap.pg_ps_enabled", &pg_ps_enabled);
	if (pg_ps_enabled) {
		KASSERT(MAXPAGESIZES > 1 && pagesizes[1] == 0,
		    ("pmap_init: can't assign to pagesizes[1]"));
		pagesizes[1] = NBPDR;
	}

	/*
	 * Initialize pv chunk lists.
	 */
	for (i = 0; i < PMAP_MEMDOM; i++) {
		mtx_init(&pv_chunks[i].pvc_lock, "pmap pv chunk list", NULL, MTX_DEF);
		TAILQ_INIT(&pv_chunks[i].pvc_list);
	}
	pmap_init_pv_table();

	pmap_initialized = 1;
	for (i = 0; i < PMAP_PREINIT_MAPPING_COUNT; i++) {
		ppim = pmap_preinit_mapping + i;
		if (ppim->va == 0)
			continue;
		/* Make the direct map consistent */
		if (ppim->pa < dmaplimit && ppim->pa + ppim->sz <= dmaplimit) {
			(void)pmap_change_attr(PHYS_TO_DMAP(ppim->pa),
			    ppim->sz, ppim->mode);
		}
		if (!bootverbose)
			continue;
		printf("PPIM %u: PA=%#lx, VA=%#lx, size=%#lx, mode=%#x\n", i,
		    ppim->pa, ppim->va, ppim->sz, ppim->mode);
	}

	mtx_init(&qframe_mtx, "qfrmlk", NULL, MTX_SPIN);
	error = vmem_alloc(kernel_arena, PAGE_SIZE, M_BESTFIT | M_WAITOK,
	    (vmem_addr_t *)&qframe);
	if (error != 0)
		panic("qframe allocation failed");

	lm_ents = 8;
	TUNABLE_INT_FETCH("vm.pmap.large_map_pml4_entries", &lm_ents);
	if (lm_ents > LMEPML4I - LMSPML4I + 1)
		lm_ents = LMEPML4I - LMSPML4I + 1;
	if (bootverbose)
		printf("pmap: large map %u PML4 slots (%lu GB)\n",
		    lm_ents, (u_long)lm_ents * (NBPML4 / 1024 / 1024 / 1024));
	if (lm_ents != 0) {
		large_vmem = vmem_create("large", LARGEMAP_MIN_ADDRESS,
		    (vmem_size_t)lm_ents * NBPML4, PAGE_SIZE, 0, M_WAITOK);
		if (large_vmem == NULL) {
			printf("pmap: cannot create large map\n");
			lm_ents = 0;
		}
		for (i = 0; i < lm_ents; i++) {
			m = pmap_large_map_getptp_unlocked();
			kernel_pmap->pm_pml4[LMSPML4I + i] = X86_PG_V |
			    X86_PG_RW | X86_PG_A | X86_PG_M | pg_nx |
			    VM_PAGE_TO_PHYS(m);
		}
	}
}