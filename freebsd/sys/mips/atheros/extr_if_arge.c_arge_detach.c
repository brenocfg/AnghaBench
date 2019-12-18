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
struct ifnet {int if_capenable; } ;
struct arge_softc {int arge_detach; int /*<<< orphan*/  arge_mtx; scalar_t__ arge_res; int /*<<< orphan*/  arge_rid; scalar_t__ arge_intrhand; int /*<<< orphan*/  arge_irq; scalar_t__ arge_miiproxy; scalar_t__ arge_miibus; int /*<<< orphan*/  arge_link_task; struct ifnet* arge_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARGE_LOCK (struct arge_softc*) ; 
 int /*<<< orphan*/  ARGE_UNLOCK (struct arge_softc*) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  arge_dma_free (struct arge_softc*) ; 
 int /*<<< orphan*/  arge_stop (struct arge_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct arge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static int
arge_detach(device_t dev)
{
	struct arge_softc	*sc = device_get_softc(dev);
	struct ifnet		*ifp = sc->arge_ifp;

	KASSERT(mtx_initialized(&sc->arge_mtx),
	    ("arge mutex not initialized"));

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		ARGE_LOCK(sc);
		sc->arge_detach = 1;
#ifdef DEVICE_POLLING
		if (ifp->if_capenable & IFCAP_POLLING)
			ether_poll_deregister(ifp);
#endif

		arge_stop(sc);
		ARGE_UNLOCK(sc);
		taskqueue_drain(taskqueue_swi, &sc->arge_link_task);
		ether_ifdetach(ifp);
	}

	if (sc->arge_miibus)
		device_delete_child(dev, sc->arge_miibus);

	if (sc->arge_miiproxy)
		device_delete_child(dev, sc->arge_miiproxy);

	bus_generic_detach(dev);

	if (sc->arge_intrhand)
		bus_teardown_intr(dev, sc->arge_irq, sc->arge_intrhand);

	if (sc->arge_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->arge_rid,
		    sc->arge_res);

	if (ifp)
		if_free(ifp);

	arge_dma_free(sc);

	mtx_destroy(&sc->arge_mtx);

	return (0);

}