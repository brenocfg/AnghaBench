#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * post_busreset; } ;
struct dcons_crom_softc {int /*<<< orphan*/ * dma_tag; int /*<<< orphan*/  dma_map; scalar_t__ ehand; TYPE_1__ fd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dma_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* dcons_conf ; 
 int /*<<< orphan*/  dcons_poll ; 
 scalar_t__ device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dcons_crom_detach(device_t dev)
{
	struct dcons_crom_softc *sc;

        sc = (struct dcons_crom_softc *) device_get_softc(dev);
	sc->fd.post_busreset = NULL;

	if (sc->ehand)
		EVENTHANDLER_DEREGISTER(dcons_poll, sc->ehand);

	/* XXX */
	if (dcons_conf->dma_tag == sc->dma_tag)
		dcons_conf->dma_tag = NULL;

	bus_dmamap_unload(sc->dma_tag, sc->dma_map);
	bus_dmamap_destroy(sc->dma_tag, sc->dma_map);
	bus_dma_tag_destroy(sc->dma_tag);

	return 0;
}