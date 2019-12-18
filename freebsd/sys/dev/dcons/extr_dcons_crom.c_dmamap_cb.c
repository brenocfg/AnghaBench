#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uintmax_t ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct dcons_crom_softc {scalar_t__ bus_addr; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; TYPE_1__ fd; } ;
struct TYPE_6__ {scalar_t__ ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_7__ {int /*<<< orphan*/  cdev; int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cnselect (int /*<<< orphan*/ ) ; 
 TYPE_4__* dcons_conf ; 
 scalar_t__ dcons_paddr ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ force_console ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static void
dmamap_cb(void *arg, bus_dma_segment_t *segments, int seg, int error)
{
	struct dcons_crom_softc *sc;

	if (error)
		printf("dcons_dmamap_cb: error=%d\n", error);

	sc = (struct dcons_crom_softc *)arg;
	sc->bus_addr = segments[0].ds_addr;

	bus_dmamap_sync(sc->dma_tag, sc->dma_map, BUS_DMASYNC_PREWRITE);
	device_printf(sc->fd.dev,
	    "bus_addr 0x%jx\n", (uintmax_t)sc->bus_addr);
	if (dcons_paddr != 0) {
		/* XXX */
		device_printf(sc->fd.dev, "dcons_paddr is already set\n");
		return;
	}
	dcons_conf->dma_tag = sc->dma_tag;
	dcons_conf->dma_map = sc->dma_map;
	dcons_paddr = sc->bus_addr;

	/* Force to be the high-level console */
	if (force_console)
		cnselect(dcons_conf->cdev);
}