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
struct emac_softc {int /*<<< orphan*/  emac_mtx; TYPE_1__* emac_ifp; int /*<<< orphan*/ * emac_irq; int /*<<< orphan*/ * emac_res; int /*<<< orphan*/ * emac_clk; int /*<<< orphan*/  emac_dev; int /*<<< orphan*/ * emac_miibus; int /*<<< orphan*/ * emac_intrhand; int /*<<< orphan*/  emac_tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_3__ {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMAC_LOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  EMAC_UNLOCK (struct emac_softc*) ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct emac_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emac_stop_locked (struct emac_softc*) ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_1__*) ; 
 int /*<<< orphan*/  if_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
emac_detach(device_t dev)
{
	struct emac_softc *sc;

	sc = device_get_softc(dev);
	sc->emac_ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
	if (device_is_attached(dev)) {
		ether_ifdetach(sc->emac_ifp);
		EMAC_LOCK(sc);
		emac_stop_locked(sc);
		EMAC_UNLOCK(sc);
		callout_drain(&sc->emac_tick_ch);
	}

	if (sc->emac_intrhand != NULL)
		bus_teardown_intr(sc->emac_dev, sc->emac_irq,
		    sc->emac_intrhand);

	if (sc->emac_miibus != NULL) {
		device_delete_child(sc->emac_dev, sc->emac_miibus);
		bus_generic_detach(sc->emac_dev);
	}

	if (sc->emac_clk != NULL)
		clk_disable(sc->emac_clk);

	if (sc->emac_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->emac_res);

	if (sc->emac_irq != NULL)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->emac_irq);

	if (sc->emac_ifp != NULL)
		if_free(sc->emac_ifp);

	if (mtx_initialized(&sc->emac_mtx))
		mtx_destroy(&sc->emac_mtx);

	return (0);
}