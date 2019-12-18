#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int uint64_t ;
struct TYPE_3__ {int prot; int pa; } ;
struct pvo_entry {int pvo_vaddr; TYPE_1__ pvo_pte; } ;
typedef  int /*<<< orphan*/  register_t ;
typedef  int /*<<< orphan*/  mmu_t ;
struct TYPE_4__ {int mr_start; int mr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_TRANS (int /*<<< orphan*/ ) ; 
 int DMAP_BASE_ADDRESS ; 
 int /*<<< orphan*/  ENABLE_TRANS (int /*<<< orphan*/ ) ; 
 int EXC_LAST ; 
 int EXC_RSVD ; 
 int LPTE_G ; 
 int LPTE_M ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PVO_LARGE ; 
 int PVO_WIRED ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,scalar_t__*) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 struct pvo_entry* alloc_pvo_entry (int) ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  init_pvo_entry (struct pvo_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ moea64_bpvo_pool ; 
 int moea64_bpvo_pool_size ; 
 int /*<<< orphan*/  moea64_kenter (int /*<<< orphan*/ ,int,int) ; 
 int moea64_large_page_mask ; 
 scalar_t__ moea64_large_page_size ; 
 int /*<<< orphan*/  moea64_pvo_enter (int /*<<< orphan*/ ,struct pvo_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* pregions ; 
 int pregions_sz ; 
 scalar_t__ unmapped_buf_allowed ; 

__attribute__((used)) static void
moea64_setup_direct_map(mmu_t mmup, vm_offset_t kernelstart,
    vm_offset_t kernelend)
{
	struct pvo_entry *pvo;
	register_t msr;
	vm_paddr_t pa, pkernelstart, pkernelend;
	vm_offset_t size, off;
	uint64_t pte_lo;
	int i;

	if (moea64_large_page_size == 0) 
		hw_direct_map = 0;

	DISABLE_TRANS(msr);
	if (hw_direct_map) {
		PMAP_LOCK(kernel_pmap);
		for (i = 0; i < pregions_sz; i++) {
		  for (pa = pregions[i].mr_start; pa < pregions[i].mr_start +
		     pregions[i].mr_size; pa += moea64_large_page_size) {
			pte_lo = LPTE_M;

			pvo = alloc_pvo_entry(1 /* bootstrap */);
			pvo->pvo_vaddr |= PVO_WIRED | PVO_LARGE;
			init_pvo_entry(pvo, kernel_pmap, PHYS_TO_DMAP(pa));

			/*
			 * Set memory access as guarded if prefetch within
			 * the page could exit the available physmem area.
			 */
			if (pa & moea64_large_page_mask) {
				pa &= moea64_large_page_mask;
				pte_lo |= LPTE_G;
			}
			if (pa + moea64_large_page_size >
			    pregions[i].mr_start + pregions[i].mr_size)
				pte_lo |= LPTE_G;

			pvo->pvo_pte.prot = VM_PROT_READ | VM_PROT_WRITE |
			    VM_PROT_EXECUTE;
			pvo->pvo_pte.pa = pa | pte_lo;
			moea64_pvo_enter(mmup, pvo, NULL, NULL);
		  }
		}
		PMAP_UNLOCK(kernel_pmap);
	}

	/*
	 * Make sure the kernel and BPVO pool stay mapped on systems either
	 * without a direct map or on which the kernel is not already executing
	 * out of the direct-mapped region.
	 */
	if (kernelstart < DMAP_BASE_ADDRESS) {
		/*
		 * For pre-dmap execution, we need to use identity mapping
		 * because we will be operating with the mmu on but in the
		 * wrong address configuration until we __restartkernel().
		 */
		for (pa = kernelstart & ~PAGE_MASK; pa < kernelend;
		    pa += PAGE_SIZE)
			moea64_kenter(mmup, pa, pa);
	} else if (!hw_direct_map) {
		pkernelstart = kernelstart & ~DMAP_BASE_ADDRESS;
		pkernelend = kernelend & ~DMAP_BASE_ADDRESS;
		for (pa = pkernelstart & ~PAGE_MASK; pa < pkernelend;
		    pa += PAGE_SIZE)
			moea64_kenter(mmup, pa | DMAP_BASE_ADDRESS, pa);
	}

	if (!hw_direct_map) {
		size = moea64_bpvo_pool_size*sizeof(struct pvo_entry);
		off = (vm_offset_t)(moea64_bpvo_pool);
		for (pa = off; pa < off + size; pa += PAGE_SIZE)
			moea64_kenter(mmup, pa, pa);

		/* Map exception vectors */
		for (pa = EXC_RSVD; pa < EXC_LAST; pa += PAGE_SIZE)
			moea64_kenter(mmup, pa | DMAP_BASE_ADDRESS, pa);
	}
	ENABLE_TRANS(msr);

	/*
	 * Allow user to override unmapped_buf_allowed for testing.
	 * XXXKIB Only direct map implementation was tested.
	 */
	if (!TUNABLE_INT_FETCH("vfs.unmapped_buf_allowed",
	    &unmapped_buf_allowed))
		unmapped_buf_allowed = hw_direct_map;
}