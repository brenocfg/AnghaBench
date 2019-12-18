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
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;
struct TYPE_3__ {int /*<<< orphan*/  ds_len; scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int _bus_dmamap_load_phys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static int
_bus_dmamap_load_plist(bus_dma_tag_t dmat, bus_dmamap_t map,
    bus_dma_segment_t *list, int sglist_cnt, int *nsegs, int flags)
{
	int error;

	error = 0;
	for (; sglist_cnt > 0; sglist_cnt--, list++) {
		error = _bus_dmamap_load_phys(dmat, map,
		    (vm_paddr_t)list->ds_addr, list->ds_len, flags, NULL,
		    nsegs);
		if (error)
			break;
	}
	return (error);
}