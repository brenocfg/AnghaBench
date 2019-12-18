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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ u_int ;
typedef  void pt2_entry_t ;
typedef  int /*<<< orphan*/  pt1_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_TO_L1 (int /*<<< orphan*/ ) ; 
 scalar_t__ KERNBASE ; 
 scalar_t__ KERNEL_P2V (scalar_t__) ; 
 scalar_t__ KERNEL_V2P (scalar_t__) ; 
 scalar_t__ NB_IN_PT1 ; 
 scalar_t__ NB_IN_PT2 ; 
 scalar_t__ NB_IN_PT2TAB ; 
 scalar_t__ NKPT2PG ; 
 scalar_t__ NPG_IN_PT1 ; 
 scalar_t__ NPG_IN_PT2TAB ; 
 scalar_t__ NPT2_IN_PT2TAB ; 
 scalar_t__ PAGE_SIZE ; 
 void* PT2MAP ; 
 scalar_t__ PT2MAP_SIZE ; 
 int /*<<< orphan*/  PTE1_AP_KRW ; 
 int /*<<< orphan*/  PTE1_KERN (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE1_LINK (scalar_t__) ; 
 scalar_t__ PTE1_SIZE ; 
 int /*<<< orphan*/  PTE2_ATTR_DEFAULT ; 
 int /*<<< orphan*/  PTE2_KPT (scalar_t__) ; 
 int /*<<< orphan*/  PTE2_KPT_NG (scalar_t__) ; 
 scalar_t__ PTE2_SIZE ; 
 scalar_t__ base_pt1 ; 
 int /*<<< orphan*/  bzero (void*,scalar_t__) ; 
 int /*<<< orphan*/  cpuinfo_reinit_mmu (scalar_t__) ; 
 int /*<<< orphan*/ * kern_pt1 ; 
 void* kern_pt2tab ; 
 void* kern_pt2tab_entry (scalar_t__) ; 
 int /*<<< orphan*/ * kern_pte1 (scalar_t__) ; 
 int /*<<< orphan*/  last_paddr ; 
 void* page_pt2 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_kern_ttb ; 
 scalar_t__ pmap_preboot_get_pages (scalar_t__) ; 
 int /*<<< orphan*/  pt2tab_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_index (scalar_t__) ; 
 int /*<<< orphan*/  pte1_roundup (scalar_t__) ; 
 int /*<<< orphan*/  pte1_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte1_sync_range (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pte2_load (void*) ; 
 scalar_t__ pte2_pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_store (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte2_sync_range (void*,scalar_t__) ; 
 scalar_t__ ttb_flags ; 
 scalar_t__ virtual_avail ; 
 int /*<<< orphan*/  vm_phys_add_seg (scalar_t__,scalar_t__) ; 

void
pmap_bootstrap_prepare(vm_paddr_t last)
{
	vm_paddr_t pt2pg_pa, pt2tab_pa, pa, size;
	vm_offset_t pt2pg_va;
	pt1_entry_t *pte1p;
	pt2_entry_t *pte2p;
	u_int i;
	uint32_t l1_attr;

	/*
	 * Now, we are going to make real kernel mapping. Note that we are
	 * already running on some mapping made in locore.S and we expect
	 * that it's large enough to ensure nofault access to physical memory
	 * allocated herein before switch.
	 *
	 * As kernel image and everything needed before are and will be mapped
	 * by section mappings, we align last physical address to PTE1_SIZE.
	 */
	last_paddr = pte1_roundup(last);

	/*
	 * Allocate and zero page(s) for kernel L1 page table.
	 *
	 * Note that it's first allocation on space which was PTE1_SIZE
	 * aligned and as such base_pt1 is aligned to NB_IN_PT1 too.
	 */
	base_pt1 = pmap_preboot_get_pages(NPG_IN_PT1);
	kern_pt1 = (pt1_entry_t *)KERNEL_P2V(base_pt1);
	bzero((void*)kern_pt1, NB_IN_PT1);
	pte1_sync_range(kern_pt1, NB_IN_PT1);

	/* Allocate and zero page(s) for kernel PT2TAB. */
	pt2tab_pa = pmap_preboot_get_pages(NPG_IN_PT2TAB);
	kern_pt2tab = (pt2_entry_t *)KERNEL_P2V(pt2tab_pa);
	bzero(kern_pt2tab, NB_IN_PT2TAB);
	pte2_sync_range(kern_pt2tab, NB_IN_PT2TAB);

	/* Allocate and zero page(s) for kernel L2 page tables. */
	pt2pg_pa = pmap_preboot_get_pages(NKPT2PG);
	pt2pg_va = KERNEL_P2V(pt2pg_pa);
	size = NKPT2PG * PAGE_SIZE;
	bzero((void*)pt2pg_va, size);
	pte2_sync_range((pt2_entry_t *)pt2pg_va, size);

	/*
	 * Add a physical memory segment (vm_phys_seg) corresponding to the
	 * preallocated pages for kernel L2 page tables so that vm_page
	 * structures representing these pages will be created. The vm_page
	 * structures are required for promotion of the corresponding kernel
	 * virtual addresses to section mappings.
	 */
	vm_phys_add_seg(pt2tab_pa, pmap_preboot_get_pages(0));

	/*
	 * Insert allocated L2 page table pages to PT2TAB and make
	 * link to all PT2s in L1 page table. See how kernel_vm_end
	 * is initialized.
	 *
	 * We play simple and safe. So every KVA will have underlaying
	 * L2 page table, even kernel image mapped by sections.
	 */
	pte2p = kern_pt2tab_entry(KERNBASE);
	for (pa = pt2pg_pa; pa < pt2pg_pa + size; pa += PTE2_SIZE)
		pt2tab_store(pte2p++, PTE2_KPT(pa));

	pte1p = kern_pte1(KERNBASE);
	for (pa = pt2pg_pa; pa < pt2pg_pa + size; pa += NB_IN_PT2)
		pte1_store(pte1p++, PTE1_LINK(pa));

	/* Make section mappings for kernel. */
	l1_attr = ATTR_TO_L1(PTE2_ATTR_DEFAULT);
	pte1p = kern_pte1(KERNBASE);
	for (pa = KERNEL_V2P(KERNBASE); pa < last; pa += PTE1_SIZE)
		pte1_store(pte1p++, PTE1_KERN(pa, PTE1_AP_KRW, l1_attr));

	/*
	 * Get free and aligned space for PT2MAP and make L1 page table links
	 * to L2 page tables held in PT2TAB.
	 *
	 * Note that pages holding PT2s are stored in PT2TAB as pt2_entry_t
	 * descriptors and PT2TAB page(s) itself is(are) used as PT2s. Thus
	 * each entry in PT2TAB maps all PT2s in a page. This implies that
	 * virtual address of PT2MAP must be aligned to NPT2_IN_PG * PTE1_SIZE.
	 */
	PT2MAP = (pt2_entry_t *)(KERNBASE - PT2MAP_SIZE);
	pte1p = kern_pte1((vm_offset_t)PT2MAP);
	for (pa = pt2tab_pa, i = 0; i < NPT2_IN_PT2TAB; i++, pa += NB_IN_PT2) {
		pte1_store(pte1p++, PTE1_LINK(pa));
	}

	/*
	 * Store PT2TAB in PT2TAB itself, i.e. self reference mapping.
	 * Each pmap will hold own PT2TAB, so the mapping should be not global.
	 */
	pte2p = kern_pt2tab_entry((vm_offset_t)PT2MAP);
	for (pa = pt2tab_pa, i = 0; i < NPG_IN_PT2TAB; i++, pa += PTE2_SIZE) {
		pt2tab_store(pte2p++, PTE2_KPT_NG(pa));
	}

	/*
	 * Choose correct L2 page table and make mappings for allocations
	 * made herein which replaces temporary locore.S mappings after a while.
	 * Note that PT2MAP cannot be used until we switch to kern_pt1.
	 *
	 * Note, that these allocations started aligned on 1M section and
	 * kernel PT1 was allocated first. Making of mappings must follow
	 * order of physical allocations as we've used KERNEL_P2V() macro
	 * for virtual addresses resolution.
	 */
	pte2p = kern_pt2tab_entry((vm_offset_t)kern_pt1);
	pt2pg_va = KERNEL_P2V(pte2_pa(pte2_load(pte2p)));

	pte2p = page_pt2(pt2pg_va, pte1_index((vm_offset_t)kern_pt1));

	/* Make mapping for kernel L1 page table. */
	for (pa = base_pt1, i = 0; i < NPG_IN_PT1; i++, pa += PTE2_SIZE)
		pte2_store(pte2p++, PTE2_KPT(pa));

	/* Make mapping for kernel PT2TAB. */
	for (pa = pt2tab_pa, i = 0; i < NPG_IN_PT2TAB; i++, pa += PTE2_SIZE)
		pte2_store(pte2p++, PTE2_KPT(pa));

	/* Finally, switch from 'boot_pt1' to 'kern_pt1'. */
	pmap_kern_ttb = base_pt1 | ttb_flags;
	cpuinfo_reinit_mmu(pmap_kern_ttb);
	/*
	 * Initialize the first available KVA. As kernel image is mapped by
	 * sections, we are leaving some gap behind.
	 */
	virtual_avail = (vm_offset_t)kern_pt2tab + NPG_IN_PT2TAB * PAGE_SIZE;
}