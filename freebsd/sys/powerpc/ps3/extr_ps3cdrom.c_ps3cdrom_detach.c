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
struct ps3cdrom_softc {int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_irqid; int /*<<< orphan*/  sc_irqctx; int /*<<< orphan*/  sc_dmatag; TYPE_1__* sc_xfer; int /*<<< orphan*/  sc_sim; int /*<<< orphan*/  sc_path; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  x_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC_LOST_DEVICE ; 
 int /*<<< orphan*/  PS3CDROM_LOCK_DESTROY (struct ps3cdrom_softc*) ; 
 int PS3CDROM_MAX_XFERS ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cam_sim_path (int /*<<< orphan*/ ) ; 
 struct ps3cdrom_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_async (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xpt_bus_deregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpt_free_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ps3cdrom_detach(device_t dev)
{
	struct ps3cdrom_softc *sc = device_get_softc(dev);
	int i;

	xpt_async(AC_LOST_DEVICE, sc->sc_path, NULL);
	xpt_free_path(sc->sc_path);
	xpt_bus_deregister(cam_sim_path(sc->sc_sim));
	cam_sim_free(sc->sc_sim, TRUE);

	for (i = 0; i < PS3CDROM_MAX_XFERS; i++)
		bus_dmamap_destroy(sc->sc_dmatag, sc->sc_xfer[i].x_dmamap);

	bus_dma_tag_destroy(sc->sc_dmatag);

	bus_teardown_intr(dev, sc->sc_irq, sc->sc_irqctx);
	bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irqid, sc->sc_irq);

	PS3CDROM_LOCK_DESTROY(sc);

	return (0);
}