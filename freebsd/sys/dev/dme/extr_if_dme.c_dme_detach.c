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
struct ifnet {int dummy; } ;
struct dme_softc {scalar_t__ dme_vcc_regulator; int /*<<< orphan*/  dme_mtx; scalar_t__ dme_res; scalar_t__ dme_irq; scalar_t__ dme_intrhand; scalar_t__ dme_miibus; int /*<<< orphan*/  dme_tick_ch; struct ifnet* dme_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DME_LOCK (struct dme_softc*) ; 
 int /*<<< orphan*/  DME_UNLOCK (struct dme_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct dme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dme_stop (struct dme_softc*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regulator_release (scalar_t__) ; 

__attribute__((used)) static int
dme_detach(device_t dev)
{
	struct dme_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->dme_mtx), ("dme mutex not initialized"));

	ifp = sc->dme_ifp;

	if (device_is_attached(dev)) {
		DME_LOCK(sc);
		dme_stop(sc);
		DME_UNLOCK(sc);
		ether_ifdetach(ifp);
		callout_drain(&sc->dme_tick_ch);
	}

	if (sc->dme_miibus)
		device_delete_child(dev, sc->dme_miibus);
	bus_generic_detach(dev);

	if (sc->dme_vcc_regulator != 0)
		regulator_release(sc->dme_vcc_regulator);
	if (sc->dme_intrhand)
		bus_teardown_intr(dev, sc->dme_irq, sc->dme_intrhand);
	if (sc->dme_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->dme_irq);
	if (sc->dme_res)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->dme_res);

	if (ifp != NULL)
		if_free(ifp);

	mtx_destroy(&sc->dme_mtx);

	return (0);
}