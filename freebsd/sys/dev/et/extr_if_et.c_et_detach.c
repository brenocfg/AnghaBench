#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct et_softc {int sc_flags; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/ * ifp; int /*<<< orphan*/ * sc_mem_res; int /*<<< orphan*/ * sc_irq_res; int /*<<< orphan*/ * sc_irq_handle; int /*<<< orphan*/ * sc_miibus; int /*<<< orphan*/  sc_tick; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ET_FLAG_MSI ; 
 int /*<<< orphan*/  ET_LOCK (struct et_softc*) ; 
 int /*<<< orphan*/  ET_UNLOCK (struct et_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct et_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  et_dma_free (struct et_softc*) ; 
 int /*<<< orphan*/  et_stop (struct et_softc*) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
et_detach(device_t dev)
{
	struct et_softc *sc;

	sc = device_get_softc(dev);
	if (device_is_attached(dev)) {
		ether_ifdetach(sc->ifp);
		ET_LOCK(sc);
		et_stop(sc);
		ET_UNLOCK(sc);
		callout_drain(&sc->sc_tick);
	}

	if (sc->sc_miibus != NULL)
		device_delete_child(dev, sc->sc_miibus);
	bus_generic_detach(dev);

	if (sc->sc_irq_handle != NULL)
		bus_teardown_intr(dev, sc->sc_irq_res, sc->sc_irq_handle);
	if (sc->sc_irq_res != NULL)
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(sc->sc_irq_res), sc->sc_irq_res);
	if ((sc->sc_flags & ET_FLAG_MSI) != 0)
		pci_release_msi(dev);
	if (sc->sc_mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->sc_mem_res), sc->sc_mem_res);

	if (sc->ifp != NULL)
		if_free(sc->ifp);

	et_dma_free(sc);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}