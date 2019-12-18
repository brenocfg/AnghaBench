#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
typedef  TYPE_1__* bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_3__ {int flags; scalar_t__ pagesneeded; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int DMAMAP_COULD_BOUNCE ; 
 int /*<<< orphan*/  KTR_BUSDMA ; 
 int /*<<< orphan*/  _bus_dmamap_pagesneeded (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void
_bus_dmamap_count_phys(bus_dma_tag_t dmat, bus_dmamap_t map, vm_paddr_t buf,
    bus_size_t buflen, int flags)
{

	if ((map->flags & DMAMAP_COULD_BOUNCE) != 0 && map->pagesneeded == 0) {
		_bus_dmamap_pagesneeded(dmat, buf, buflen, &map->pagesneeded);
		CTR1(KTR_BUSDMA, "pagesneeded= %d\n", map->pagesneeded);
	}
}