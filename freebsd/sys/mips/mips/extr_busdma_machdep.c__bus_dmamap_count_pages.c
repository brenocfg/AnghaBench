#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ pmap_t ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  alignment; int /*<<< orphan*/  boundary; int /*<<< orphan*/  lowaddr; } ;
struct TYPE_7__ {scalar_t__ pagesneeded; } ;

/* Variables and functions */
 int BUS_DMA_COULD_BOUNCE ; 
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_BUSDMA ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ run_filter (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bus_dmamap_count_pages(bus_dma_tag_t dmat, bus_dmamap_t map, pmap_t pmap,
    void *buf, bus_size_t buflen, int flags)
{
	vm_offset_t vaddr;
	vm_offset_t vendaddr;
	bus_addr_t paddr;

	if (map->pagesneeded == 0) {
		CTR3(KTR_BUSDMA, "lowaddr= %d, boundary= %d, alignment= %d",
		    dmat->lowaddr, dmat->boundary, dmat->alignment);
		CTR2(KTR_BUSDMA, "map= %p, pagesneeded= %d",
		    map, map->pagesneeded);
		/*
		 * Count the number of bounce pages
		 * needed in order to complete this transfer
		 */
		vaddr = (vm_offset_t)buf;
		vendaddr = (vm_offset_t)buf + buflen;

		while (vaddr < vendaddr) {
			bus_size_t sg_len;

			KASSERT(kernel_pmap == pmap, ("pmap is not kernel pmap"));
			sg_len = PAGE_SIZE - ((vm_offset_t)vaddr & PAGE_MASK);
			paddr = pmap_kextract(vaddr);
			if (((dmat->flags & BUS_DMA_COULD_BOUNCE) != 0) &&
			    run_filter(dmat, paddr) != 0) {
				sg_len = roundup2(sg_len, dmat->alignment);
				map->pagesneeded++;
			}
			vaddr += sg_len;
		}
		CTR1(KTR_BUSDMA, "pagesneeded= %d\n", map->pagesneeded);
	}
}