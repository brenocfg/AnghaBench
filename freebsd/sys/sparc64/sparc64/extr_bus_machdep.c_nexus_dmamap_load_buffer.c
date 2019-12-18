#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int u_long ;
typedef  scalar_t__ pmap_t ;
typedef  scalar_t__ bus_size_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  TYPE_1__* bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
typedef  scalar_t__ bus_addr_t ;
struct TYPE_4__ {scalar_t__ dt_maxsegsz; int /*<<< orphan*/ * dt_segments; } ;

/* Variables and functions */
 int EFBIG ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ kernel_pmap ; 
 scalar_t__ nexus_dmamap_addseg (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ pmap_extract (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_kextract (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nexus_dmamap_load_buffer(bus_dma_tag_t dmat, bus_dmamap_t map, void *buf,
    bus_size_t buflen, pmap_t pmap, int flags, bus_dma_segment_t *segs,
    int *segp)
{
	bus_size_t sgsize;
	bus_addr_t curaddr;
	vm_offset_t vaddr = (vm_offset_t)buf;

	if (segs == NULL)
		segs = dmat->dt_segments;

	while (buflen > 0) {
		/*
		 * Get the physical address for this segment.
		 */
		if (pmap == kernel_pmap)
			curaddr = pmap_kextract(vaddr);
		else
			curaddr = pmap_extract(pmap, vaddr);

		/*
		 * Compute the segment size, and adjust counts.
		 */
		sgsize = PAGE_SIZE - ((u_long)curaddr & PAGE_MASK);
		if (sgsize > dmat->dt_maxsegsz)
			sgsize = dmat->dt_maxsegsz;
		if (buflen < sgsize)
			sgsize = buflen;

		sgsize = nexus_dmamap_addseg(dmat, map, curaddr, sgsize, segs,
		    segp);
		if (sgsize == 0)
			break;

		vaddr += sgsize;
		buflen -= sgsize;
	}

	/*
	 * Did we fit?
	 */
	return (buflen != 0 ? EFBIG : 0); /* XXX better return value here? */
}