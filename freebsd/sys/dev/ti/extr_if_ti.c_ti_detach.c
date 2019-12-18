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
struct ti_softc {int /*<<< orphan*/  ti_mtx; scalar_t__ ti_membuf2; scalar_t__ ti_membuf; scalar_t__ ti_res; scalar_t__ ti_irq; scalar_t__ ti_intrhand; int /*<<< orphan*/  ifmedia; int /*<<< orphan*/  ti_watchdog; struct ifnet* ti_ifp; scalar_t__ dev; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  TI_LOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  TI_UNLOCK (struct ti_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_dev (scalar_t__) ; 
 struct ti_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_dma_free (struct ti_softc*) ; 
 int /*<<< orphan*/  ti_stop (struct ti_softc*) ; 

__attribute__((used)) static int
ti_detach(device_t dev)
{
	struct ti_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	if (sc->dev)
		destroy_dev(sc->dev);
	KASSERT(mtx_initialized(&sc->ti_mtx), ("ti mutex not initialized"));
	ifp = sc->ti_ifp;
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		TI_LOCK(sc);
		ti_stop(sc);
		TI_UNLOCK(sc);
	}

	/* These should only be active if attach succeeded */
	callout_drain(&sc->ti_watchdog);
	bus_generic_detach(dev);
	ti_dma_free(sc);
	ifmedia_removeall(&sc->ifmedia);

	if (sc->ti_intrhand)
		bus_teardown_intr(dev, sc->ti_irq, sc->ti_intrhand);
	if (sc->ti_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->ti_irq);
	if (sc->ti_res) {
		bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BAR(0),
		    sc->ti_res);
	}
	if (ifp)
		if_free(ifp);
	if (sc->ti_membuf)
		free(sc->ti_membuf, M_DEVBUF);
	if (sc->ti_membuf2)
		free(sc->ti_membuf2, M_DEVBUF);

	mtx_destroy(&sc->ti_mtx);

	return (0);
}