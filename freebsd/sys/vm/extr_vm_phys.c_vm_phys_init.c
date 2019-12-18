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
typedef  size_t u_long ;
struct vm_phys_seg {scalar_t__ end; scalar_t__ start; size_t domain; struct vm_freelist*** free_queues; int /*<<< orphan*/ * first_page; } ;
struct vm_freelist {int /*<<< orphan*/  pl; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 scalar_t__ VM_DMA32_BOUNDARY ; 
 size_t VM_DMA32_NPAGES_THRESHOLD ; 
 size_t VM_FREELIST_DEFAULT ; 
 size_t VM_FREELIST_DMA32 ; 
 size_t VM_FREELIST_LOWMEM ; 
 scalar_t__ VM_LOWMEM_BOUNDARY ; 
 int VM_NFREELIST ; 
 int VM_NFREEORDER ; 
 int VM_NFREEPOOL ; 
 scalar_t__ atop (scalar_t__) ; 
 int /*<<< orphan*/  rw_init (int /*<<< orphan*/ *,char*) ; 
 int* vm_freelist_to_flind ; 
 int vm_ndomains ; 
 int vm_nfreelists ; 
 int /*<<< orphan*/ * vm_page_array ; 
 int /*<<< orphan*/  vm_phys_fictitious_reg_lock ; 
 struct vm_freelist**** vm_phys_free_queues ; 
 int vm_phys_nsegs ; 
 struct vm_phys_seg* vm_phys_segs ; 

void
vm_phys_init(void)
{
	struct vm_freelist *fl;
	struct vm_phys_seg *end_seg, *prev_seg, *seg, *tmp_seg;
	u_long npages;
	int dom, flind, freelist, oind, pind, segind;

	/*
	 * Compute the number of free lists, and generate the mapping from the
	 * manifest constants VM_FREELIST_* to the free list indices.
	 *
	 * Initially, the entries of vm_freelist_to_flind[] are set to either
	 * 0 or 1 to indicate which free lists should be created.
	 */
	npages = 0;
	for (segind = vm_phys_nsegs - 1; segind >= 0; segind--) {
		seg = &vm_phys_segs[segind];
#ifdef	VM_FREELIST_LOWMEM
		if (seg->end <= VM_LOWMEM_BOUNDARY)
			vm_freelist_to_flind[VM_FREELIST_LOWMEM] = 1;
		else
#endif
#ifdef	VM_FREELIST_DMA32
		if (
#ifdef	VM_DMA32_NPAGES_THRESHOLD
		    /*
		     * Create the DMA32 free list only if the amount of
		     * physical memory above physical address 4G exceeds the
		     * given threshold.
		     */
		    npages > VM_DMA32_NPAGES_THRESHOLD &&
#endif
		    seg->end <= VM_DMA32_BOUNDARY)
			vm_freelist_to_flind[VM_FREELIST_DMA32] = 1;
		else
#endif
		{
			npages += atop(seg->end - seg->start);
			vm_freelist_to_flind[VM_FREELIST_DEFAULT] = 1;
		}
	}
	/* Change each entry into a running total of the free lists. */
	for (freelist = 1; freelist < VM_NFREELIST; freelist++) {
		vm_freelist_to_flind[freelist] +=
		    vm_freelist_to_flind[freelist - 1];
	}
	vm_nfreelists = vm_freelist_to_flind[VM_NFREELIST - 1];
	KASSERT(vm_nfreelists > 0, ("vm_phys_init: no free lists"));
	/* Change each entry into a free list index. */
	for (freelist = 0; freelist < VM_NFREELIST; freelist++)
		vm_freelist_to_flind[freelist]--;

	/*
	 * Initialize the first_page and free_queues fields of each physical
	 * memory segment.
	 */
#ifdef VM_PHYSSEG_SPARSE
	npages = 0;
#endif
	for (segind = 0; segind < vm_phys_nsegs; segind++) {
		seg = &vm_phys_segs[segind];
#ifdef VM_PHYSSEG_SPARSE
		seg->first_page = &vm_page_array[npages];
		npages += atop(seg->end - seg->start);
#else
		seg->first_page = PHYS_TO_VM_PAGE(seg->start);
#endif
#ifdef	VM_FREELIST_LOWMEM
		if (seg->end <= VM_LOWMEM_BOUNDARY) {
			flind = vm_freelist_to_flind[VM_FREELIST_LOWMEM];
			KASSERT(flind >= 0,
			    ("vm_phys_init: LOWMEM flind < 0"));
		} else
#endif
#ifdef	VM_FREELIST_DMA32
		if (seg->end <= VM_DMA32_BOUNDARY) {
			flind = vm_freelist_to_flind[VM_FREELIST_DMA32];
			KASSERT(flind >= 0,
			    ("vm_phys_init: DMA32 flind < 0"));
		} else
#endif
		{
			flind = vm_freelist_to_flind[VM_FREELIST_DEFAULT];
			KASSERT(flind >= 0,
			    ("vm_phys_init: DEFAULT flind < 0"));
		}
		seg->free_queues = &vm_phys_free_queues[seg->domain][flind];
	}

	/*
	 * Coalesce physical memory segments that are contiguous and share the
	 * same per-domain free queues.
	 */
	prev_seg = vm_phys_segs;
	seg = &vm_phys_segs[1];
	end_seg = &vm_phys_segs[vm_phys_nsegs];
	while (seg < end_seg) {
		if (prev_seg->end == seg->start &&
		    prev_seg->free_queues == seg->free_queues) {
			prev_seg->end = seg->end;
			KASSERT(prev_seg->domain == seg->domain,
			    ("vm_phys_init: free queues cannot span domains"));
			vm_phys_nsegs--;
			end_seg--;
			for (tmp_seg = seg; tmp_seg < end_seg; tmp_seg++)
				*tmp_seg = *(tmp_seg + 1);
		} else {
			prev_seg = seg;
			seg++;
		}
	}

	/*
	 * Initialize the free queues.
	 */
	for (dom = 0; dom < vm_ndomains; dom++) {
		for (flind = 0; flind < vm_nfreelists; flind++) {
			for (pind = 0; pind < VM_NFREEPOOL; pind++) {
				fl = vm_phys_free_queues[dom][flind][pind];
				for (oind = 0; oind < VM_NFREEORDER; oind++)
					TAILQ_INIT(&fl[oind].pl);
			}
		}
	}

	rw_init(&vm_phys_fictitious_reg_lock, "vmfctr");
}