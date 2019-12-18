#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct intel_gtt {scalar_t__ gma_bus_addr; int /*<<< orphan*/  scratch_page_dma; scalar_t__ do_idle_maps; int /*<<< orphan*/  gtt_mappable_entries; int /*<<< orphan*/  gtt_total_entries; int /*<<< orphan*/  stolen_size; } ;
struct TYPE_2__ {int /*<<< orphan*/ * as_aperture; } ;
struct agp_i810_softc {TYPE_1__ agp; int /*<<< orphan*/  gtt_mappable_entries; int /*<<< orphan*/  gtt_total_entries; int /*<<< orphan*/  stolen_size; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bogus_page ; 
 struct agp_i810_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ *) ; 

struct intel_gtt
agp_intel_gtt_get(device_t dev)
{
	struct agp_i810_softc *sc;
	struct intel_gtt res;

	sc = device_get_softc(dev);
	res.stolen_size = sc->stolen_size;
	res.gtt_total_entries = sc->gtt_total_entries;
	res.gtt_mappable_entries = sc->gtt_mappable_entries;
	res.do_idle_maps = 0;
	res.scratch_page_dma = VM_PAGE_TO_PHYS(bogus_page);
	if (sc->agp.as_aperture != NULL)
		res.gma_bus_addr = rman_get_start(sc->agp.as_aperture);
	else
		res.gma_bus_addr = 0;
	return (res);
}