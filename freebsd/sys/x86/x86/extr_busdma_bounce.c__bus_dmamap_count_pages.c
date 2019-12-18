#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  scalar_t__ pmap_t ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
struct TYPE_11__ {int /*<<< orphan*/  alignment; int /*<<< orphan*/  boundary; int /*<<< orphan*/  lowaddr; } ;
struct TYPE_10__ {TYPE_4__ common; } ;
struct TYPE_9__ {scalar_t__ pagesneeded; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,TYPE_1__*,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_BUSDMA ; 
 scalar_t__ Maxmem ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ bus_dma_run_filter (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ kernel_pmap ; 
 TYPE_1__ nobounce_dmamap ; 
 int /*<<< orphan*/  pmap_extract (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_kextract (scalar_t__) ; 
 int /*<<< orphan*/  ptoa (int /*<<< orphan*/ ) ; 
 scalar_t__ roundup2 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_bus_dmamap_count_pages(bus_dma_tag_t dmat, bus_dmamap_t map, pmap_t pmap,
    void *buf, bus_size_t buflen, int flags)
{
	vm_offset_t vaddr;
	vm_offset_t vendaddr;
	vm_paddr_t paddr;
	bus_size_t sg_len;

	if (map != &nobounce_dmamap && map->pagesneeded == 0) {
		CTR4(KTR_BUSDMA, "lowaddr= %d Maxmem= %d, boundary= %d, "
		    "alignment= %d", dmat->common.lowaddr,
		    ptoa((vm_paddr_t)Maxmem),
		    dmat->common.boundary, dmat->common.alignment);
		CTR3(KTR_BUSDMA, "map= %p, nobouncemap= %p, pagesneeded= %d",
		    map, &nobounce_dmamap, map->pagesneeded);
		/*
		 * Count the number of bounce pages
		 * needed in order to complete this transfer
		 */
		vaddr = (vm_offset_t)buf;
		vendaddr = (vm_offset_t)buf + buflen;

		while (vaddr < vendaddr) {
			sg_len = PAGE_SIZE - ((vm_offset_t)vaddr & PAGE_MASK);
			if (pmap == kernel_pmap)
				paddr = pmap_kextract(vaddr);
			else
				paddr = pmap_extract(pmap, vaddr);
			if (bus_dma_run_filter(&dmat->common, paddr) != 0) {
				sg_len = roundup2(sg_len,
				    dmat->common.alignment);
				map->pagesneeded++;
			}
			vaddr += sg_len;
		}
		CTR1(KTR_BUSDMA, "pagesneeded= %d\n", map->pagesneeded);
	}
}