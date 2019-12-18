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
struct are_softc {int are_detach; int /*<<< orphan*/  are_mtx; scalar_t__ are_res; int /*<<< orphan*/  are_rid; scalar_t__ are_irq; scalar_t__ are_intrhand; scalar_t__ are_miibus; int /*<<< orphan*/  are_link_task; struct ifnet* are_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARE_LOCK (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_UNLOCK (struct are_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  are_dma_free (struct are_softc*) ; 
 int /*<<< orphan*/  are_stop (struct are_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct are_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static int
are_detach(device_t dev)
{
	struct are_softc		*sc = device_get_softc(dev);
	struct ifnet		*ifp = sc->are_ifp;

	KASSERT(mtx_initialized(&sc->are_mtx), ("vr mutex not initialized"));

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		ARE_LOCK(sc);
		sc->are_detach = 1;
		are_stop(sc);
		ARE_UNLOCK(sc);
		taskqueue_drain(taskqueue_swi, &sc->are_link_task);
		ether_ifdetach(ifp);
	}
#ifdef ARE_MII
	if (sc->are_miibus)
		device_delete_child(dev, sc->are_miibus);
#endif
	bus_generic_detach(dev);

	if (sc->are_intrhand)
		bus_teardown_intr(dev, sc->are_irq, sc->are_intrhand);
	if (sc->are_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->are_irq);

	if (sc->are_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->are_rid, 
		    sc->are_res);

	if (ifp)
		if_free(ifp);

	are_dma_free(sc);

	mtx_destroy(&sc->are_mtx);

	return (0);

}