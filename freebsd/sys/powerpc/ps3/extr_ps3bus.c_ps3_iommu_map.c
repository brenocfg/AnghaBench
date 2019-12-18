#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ps3bus_softc {int rcount; TYPE_1__* regions; } ;
struct ps3bus_devinfo {scalar_t__* dma_base; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  bus_size_t ;
struct TYPE_5__ {scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_4__ {scalar_t__ mr_start; scalar_t__ mr_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 struct ps3bus_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3_iommu_map(device_t dev, bus_dma_segment_t *segs, int *nsegs,
    bus_addr_t min, bus_addr_t max, bus_size_t alignment, bus_addr_t boundary,
    void *cookie)
{
	struct ps3bus_devinfo *dinfo = cookie;
	struct ps3bus_softc *sc = device_get_softc(dev);
	int i, j;

	for (i = 0; i < *nsegs; i++) {
		for (j = 0; j < sc->rcount; j++) {
			if (segs[i].ds_addr >= sc->regions[j].mr_start &&
			    segs[i].ds_addr < sc->regions[j].mr_start +
			      sc->regions[j].mr_size)
				break;
		}
		KASSERT(j < sc->rcount,
		    ("Trying to map address %#lx not in physical memory",
		    segs[i].ds_addr));

		segs[i].ds_addr = dinfo->dma_base[j] +
		    (segs[i].ds_addr - sc->regions[j].mr_start);
	}

	return (0);
}