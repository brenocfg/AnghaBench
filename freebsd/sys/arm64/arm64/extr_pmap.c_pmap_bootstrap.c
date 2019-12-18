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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ uint64_t ;
typedef  size_t u_int ;
typedef  scalar_t__ pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  pm_cookie; scalar_t__ pm_l0_paddr; } ;
struct TYPE_4__ {int /*<<< orphan*/ * pm_l0; } ;

/* Variables and functions */
 scalar_t__ ATTR_DESCR_MASK ; 
 scalar_t__ ATTR_MASK ; 
 int /*<<< orphan*/  COOKIE_FROM (int,int /*<<< orphan*/ ) ; 
 scalar_t__ DPCPU_SIZE ; 
 int /*<<< orphan*/  EXFLAG_NOALLOC ; 
 int /*<<< orphan*/  INT_MIN ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ KERNBASE ; 
 scalar_t__ L1_SHIFT ; 
 scalar_t__ L1_SIZE ; 
 scalar_t__ L2_BLOCK ; 
 scalar_t__ L2_SIZE ; 
 scalar_t__ Ln_ADDR_MASK ; 
 size_t Ln_ENTRIES ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PMAP_LOCK_INIT (TYPE_2__*) ; 
 scalar_t__ PMAP_MAPDEV_EARLY_SIZE ; 
 scalar_t__ PMAP_PREINIT_MAPPING_SIZE ; 
 int READ_SPECIALREG (int /*<<< orphan*/ ) ; 
 int TCR_A1 ; 
 scalar_t__ VM_MAX_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  alloc_pages (scalar_t__,scalar_t__) ; 
 int arm_physmem_avail (scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_physmem_exclude_region (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_tlb_flushID () ; 
 int /*<<< orphan*/  dpcpu_init (void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kernel_pmap ; 
 TYPE_1__ kernel_pmap_store ; 
 scalar_t__ kernel_vm_end ; 
 void* msgbufp ; 
 int /*<<< orphan*/  msgbufsize ; 
 int /*<<< orphan*/  nitems (scalar_t__*) ; 
 scalar_t__* physmap ; 
 int physmap_idx ; 
 scalar_t__ pmap_bootstrap_dmap (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_bootstrap_l2 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ pmap_bootstrap_l3 (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* pmap_early_page_idx (scalar_t__,scalar_t__,size_t*,size_t*) ; 
 scalar_t__ pmap_early_vtophys (scalar_t__,scalar_t__) ; 
 void* preinit_map_va ; 
 int /*<<< orphan*/  printf (char*,scalar_t__,...) ; 
 scalar_t__ round_page (int /*<<< orphan*/ ) ; 
 void* roundup2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  tcr_el1 ; 
 scalar_t__ virtual_avail ; 
 scalar_t__ virtual_end ; 

void
pmap_bootstrap(vm_offset_t l0pt, vm_offset_t l1pt, vm_paddr_t kernstart,
    vm_size_t kernlen)
{
	u_int l1_slot, l2_slot;
	pt_entry_t *l2;
	vm_offset_t va, freemempos;
	vm_offset_t dpcpu, msgbufpv;
	vm_paddr_t start_pa, pa, min_pa;
	uint64_t kern_delta;
	int i;

	/* Verify that the ASID is set through TTBR0. */
	KASSERT((READ_SPECIALREG(tcr_el1) & TCR_A1) == 0,
	    ("pmap_bootstrap: TCR_EL1.A1 != 0"));

	kern_delta = KERNBASE - kernstart;

	printf("pmap_bootstrap %lx %lx %lx\n", l1pt, kernstart, kernlen);
	printf("%lx\n", l1pt);
	printf("%lx\n", (KERNBASE >> L1_SHIFT) & Ln_ADDR_MASK);

	/* Set this early so we can use the pagetable walking functions */
	kernel_pmap_store.pm_l0 = (pd_entry_t *)l0pt;
	PMAP_LOCK_INIT(kernel_pmap);
	kernel_pmap->pm_l0_paddr = l0pt - kern_delta;
	kernel_pmap->pm_cookie = COOKIE_FROM(-1, INT_MIN);

	/* Assume the address we were loaded to is a valid physical address */
	min_pa = KERNBASE - kern_delta;

	physmap_idx = arm_physmem_avail(physmap, nitems(physmap));
	physmap_idx /= 2;

	/*
	 * Find the minimum physical address. physmap is sorted,
	 * but may contain empty ranges.
	 */
	for (i = 0; i < (physmap_idx * 2); i += 2) {
		if (physmap[i] == physmap[i + 1])
			continue;
		if (physmap[i] <= min_pa)
			min_pa = physmap[i];
	}

	freemempos = KERNBASE + kernlen;
	freemempos = roundup2(freemempos, PAGE_SIZE);

	/* Create a direct map region early so we can use it for pa -> va */
	freemempos = pmap_bootstrap_dmap(l1pt, min_pa, freemempos);

	va = KERNBASE;
	start_pa = pa = KERNBASE - kern_delta;

	/*
	 * Read the page table to find out what is already mapped.
	 * This assumes we have mapped a block of memory from KERNBASE
	 * using a single L1 entry.
	 */
	l2 = pmap_early_page_idx(l1pt, KERNBASE, &l1_slot, &l2_slot);

	/* Sanity check the index, KERNBASE should be the first VA */
	KASSERT(l2_slot == 0, ("The L2 index is non-zero"));

	/* Find how many pages we have mapped */
	for (; l2_slot < Ln_ENTRIES; l2_slot++) {
		if ((l2[l2_slot] & ATTR_DESCR_MASK) == 0)
			break;

		/* Check locore used L2 blocks */
		KASSERT((l2[l2_slot] & ATTR_DESCR_MASK) == L2_BLOCK,
		    ("Invalid bootstrap L2 table"));
		KASSERT((l2[l2_slot] & ~ATTR_MASK) == pa,
		    ("Incorrect PA in L2 table"));

		va += L2_SIZE;
		pa += L2_SIZE;
	}

	va = roundup2(va, L1_SIZE);

	/* Create the l2 tables up to VM_MAX_KERNEL_ADDRESS */
	freemempos = pmap_bootstrap_l2(l1pt, va, freemempos);
	/* And the l3 tables for the early devmap */
	freemempos = pmap_bootstrap_l3(l1pt,
	    VM_MAX_KERNEL_ADDRESS - (PMAP_MAPDEV_EARLY_SIZE), freemempos);

	cpu_tlb_flushID();

#define alloc_pages(var, np)						\
	(var) = freemempos;						\
	freemempos += (np * PAGE_SIZE);					\
	memset((char *)(var), 0, ((np) * PAGE_SIZE));

	/* Allocate dynamic per-cpu area. */
	alloc_pages(dpcpu, DPCPU_SIZE / PAGE_SIZE);
	dpcpu_init((void *)dpcpu, 0);

	/* Allocate memory for the msgbuf, e.g. for /sbin/dmesg */
	alloc_pages(msgbufpv, round_page(msgbufsize) / PAGE_SIZE);
	msgbufp = (void *)msgbufpv;

	/* Reserve some VA space for early BIOS/ACPI mapping */
	preinit_map_va = roundup2(freemempos, L2_SIZE);

	virtual_avail = preinit_map_va + PMAP_PREINIT_MAPPING_SIZE;
	virtual_avail = roundup2(virtual_avail, L1_SIZE);
	virtual_end = VM_MAX_KERNEL_ADDRESS - (PMAP_MAPDEV_EARLY_SIZE);
	kernel_vm_end = virtual_avail;

	pa = pmap_early_vtophys(l1pt, freemempos);

	arm_physmem_exclude_region(start_pa, pa - start_pa, EXFLAG_NOALLOC);

	cpu_tlb_flushID();
}