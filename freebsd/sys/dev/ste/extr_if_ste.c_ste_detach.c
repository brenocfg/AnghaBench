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
struct ste_softc {int /*<<< orphan*/  ste_mtx; scalar_t__ ste_res; int /*<<< orphan*/  ste_res_id; int /*<<< orphan*/  ste_res_type; scalar_t__ ste_irq; scalar_t__ ste_intrhand; scalar_t__ ste_miibus; int /*<<< orphan*/  ste_callout; struct ifnet* ste_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  STE_LOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_UNLOCK (struct ste_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ste_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ste_dma_free (struct ste_softc*) ; 
 int /*<<< orphan*/  ste_stop (struct ste_softc*) ; 

__attribute__((used)) static int
ste_detach(device_t dev)
{
	struct ste_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->ste_mtx), ("ste mutex not initialized"));
	ifp = sc->ste_ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		STE_LOCK(sc);
		ste_stop(sc);
		STE_UNLOCK(sc);
		callout_drain(&sc->ste_callout);
	}
	if (sc->ste_miibus)
		device_delete_child(dev, sc->ste_miibus);
	bus_generic_detach(dev);

	if (sc->ste_intrhand)
		bus_teardown_intr(dev, sc->ste_irq, sc->ste_intrhand);
	if (sc->ste_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->ste_irq);
	if (sc->ste_res)
		bus_release_resource(dev, sc->ste_res_type, sc->ste_res_id,
		    sc->ste_res);

	if (ifp)
		if_free(ifp);

	ste_dma_free(sc);
	mtx_destroy(&sc->ste_mtx);

	return (0);
}