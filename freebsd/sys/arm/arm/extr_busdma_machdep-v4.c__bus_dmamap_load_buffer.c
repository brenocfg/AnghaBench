#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
struct sync_list {int dataoffs; int datacount; scalar_t__ vaddr; int /*<<< orphan*/  pages; } ;
struct pmap {int dummy; } ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
typedef  int bus_addr_t ;
struct TYPE_17__ {int flags; scalar_t__ maxsegsz; scalar_t__ nsegments; int /*<<< orphan*/  alignment; int /*<<< orphan*/  boundary; int /*<<< orphan*/  lowaddr; } ;
struct TYPE_16__ {int flags; scalar_t__ pagesneeded; int sync_count; struct sync_list* slist; int /*<<< orphan*/ * segments; } ;

/* Variables and functions */
 int BUS_DMA_COULD_BOUNCE ; 
 int BUS_DMA_LOAD_MBUF ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DMAMAP_CACHE_ALIGNED ; 
 int DMAMAP_COHERENT ; 
 int DMAMAP_DMAMEM_ALLOC ; 
 int EFBIG ; 
 int /*<<< orphan*/  KTR_BUSDMA ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_true (int) ; 
 scalar_t__ _bus_dmamap_addseg (TYPE_2__*,TYPE_1__*,int,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  _bus_dmamap_count_pages (TYPE_2__*,TYPE_1__*,struct pmap*,void*,scalar_t__,int) ; 
 int _bus_dmamap_reserve_pages (TYPE_2__*,TYPE_1__*,int) ; 
 int add_bounce_page (TYPE_2__*,TYPE_1__*,scalar_t__,int,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_unload (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 struct pmap* kernel_pmap ; 
 int /*<<< orphan*/  maploads_bounced ; 
 int /*<<< orphan*/  maploads_coherent ; 
 int /*<<< orphan*/  maploads_dmamem ; 
 int /*<<< orphan*/  maploads_mbuf ; 
 int /*<<< orphan*/  maploads_total ; 
 int pmap_extract (struct pmap*,scalar_t__) ; 
 int pmap_kextract (scalar_t__) ; 
 scalar_t__ run_filter (TYPE_2__*,int) ; 

int
_bus_dmamap_load_buffer(bus_dma_tag_t dmat, bus_dmamap_t map, void *buf,
    bus_size_t buflen, struct pmap *pmap, int flags, bus_dma_segment_t *segs,
    int *segp)
{
	bus_size_t sgsize;
	bus_addr_t curaddr;
	bus_addr_t sl_pend = 0;
	struct sync_list *sl;
	vm_offset_t kvaddr;
	vm_offset_t vaddr = (vm_offset_t)buf;
	vm_offset_t sl_vend = 0;
	int error = 0;

	counter_u64_add(maploads_total, 1);
	if (map->flags & DMAMAP_COHERENT)
		counter_u64_add(maploads_coherent, 1);
	if (map->flags & DMAMAP_DMAMEM_ALLOC)
		counter_u64_add(maploads_dmamem, 1);

	if (segs == NULL)
		segs = map->segments;
	if (flags & BUS_DMA_LOAD_MBUF) {
		counter_u64_add(maploads_mbuf, 1);
		map->flags |= DMAMAP_CACHE_ALIGNED;
	}

	if ((dmat->flags & BUS_DMA_COULD_BOUNCE) != 0) {
		_bus_dmamap_count_pages(dmat, map, pmap, buf, buflen, flags);
		if (map->pagesneeded != 0) {
			counter_u64_add(maploads_bounced, 1);
			error = _bus_dmamap_reserve_pages(dmat, map, flags);
			if (error)
				return (error);
		}
	}
	CTR3(KTR_BUSDMA, "lowaddr= %d boundary= %d, "
	    "alignment= %d", dmat->lowaddr, dmat->boundary, dmat->alignment);

	sl = map->slist + map->sync_count - 1;

	while (buflen > 0) {
		/*
		 * Get the physical address for this segment.
		 */
		if (__predict_true(pmap == kernel_pmap)) {
			curaddr = pmap_kextract(vaddr);
			kvaddr = vaddr;
		} else {
			curaddr = pmap_extract(pmap, vaddr);
			map->flags &= ~DMAMAP_COHERENT;
			kvaddr = 0;
		}

		/*
		 * Compute the segment size, and adjust counts.
		 */
		sgsize = PAGE_SIZE - (curaddr & PAGE_MASK);
		if (sgsize > dmat->maxsegsz)
			sgsize = dmat->maxsegsz;
		if (buflen < sgsize)
			sgsize = buflen;

		if (((dmat->flags & BUS_DMA_COULD_BOUNCE) != 0) &&
		    map->pagesneeded != 0 && run_filter(dmat, curaddr)) {
			curaddr = add_bounce_page(dmat, map, kvaddr, curaddr,
			    sgsize);
		} else {
			if (map->sync_count > 0) {
				sl_pend = VM_PAGE_TO_PHYS(sl->pages) +
				    sl->dataoffs + sl->datacount;
				sl_vend = sl->vaddr + sl->datacount;
			}

			if (map->sync_count == 0 ||
			    (kvaddr != 0 && kvaddr != sl_vend) ||
			    (kvaddr == 0 && curaddr != sl_pend)) {

				if (++map->sync_count > dmat->nsegments)
					goto cleanup;
				sl++;
				sl->vaddr = kvaddr;
				sl->datacount = sgsize;
				sl->pages = PHYS_TO_VM_PAGE(curaddr);
				sl->dataoffs = curaddr & PAGE_MASK;
			} else
				sl->datacount += sgsize;
		}
		sgsize = _bus_dmamap_addseg(dmat, map, curaddr, sgsize, segs,
		    segp);
		if (sgsize == 0)
			break;
		vaddr += sgsize;
		buflen -= sgsize;
	}

cleanup:
	/*
	 * Did we fit?
	 */
	if (buflen != 0) {
		bus_dmamap_unload(dmat, map);
		return (EFBIG); /* XXX better return value here? */
	}
	return (0);
}