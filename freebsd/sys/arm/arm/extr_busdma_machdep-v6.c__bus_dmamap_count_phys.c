#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_paddr_t ;
typedef  scalar_t__ bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  TYPE_2__* bus_dma_tag_t ;
typedef  int bus_addr_t ;
struct TYPE_9__ {scalar_t__ maxsegsz; int /*<<< orphan*/  alignment; int /*<<< orphan*/  boundary; int /*<<< orphan*/  lowaddr; } ;
struct TYPE_8__ {scalar_t__ pagesneeded; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  CTR5 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  KTR_BUSDMA ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ must_bounce (TYPE_2__*,TYPE_1__*,int,scalar_t__) ; 

__attribute__((used)) static void
_bus_dmamap_count_phys(bus_dma_tag_t dmat, bus_dmamap_t map, vm_paddr_t buf,
    bus_size_t buflen, int flags)
{
	bus_addr_t curaddr;
	bus_size_t sgsize;

	if (map->pagesneeded == 0) {
		CTR5(KTR_BUSDMA, "lowaddr= %d, boundary= %d, alignment= %d"
		    " map= %p, pagesneeded= %d",
		    dmat->lowaddr, dmat->boundary, dmat->alignment,
		    map, map->pagesneeded);
		/*
		 * Count the number of bounce pages
		 * needed in order to complete this transfer
		 */
		curaddr = buf;
		while (buflen != 0) {
			sgsize = MIN(buflen, dmat->maxsegsz);
			if (must_bounce(dmat, map, curaddr, sgsize) != 0) {
				sgsize = MIN(sgsize,
				    PAGE_SIZE - (curaddr & PAGE_MASK));
				map->pagesneeded++;
			}
			curaddr += sgsize;
			buflen -= sgsize;
		}
		CTR1(KTR_BUSDMA, "pagesneeded= %d", map->pagesneeded);
	}
}