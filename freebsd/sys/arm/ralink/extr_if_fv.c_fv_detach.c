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
struct fv_softc {int fv_detach; int /*<<< orphan*/  fv_mtx; scalar_t__ fv_res; int /*<<< orphan*/  fv_rid; scalar_t__ fv_irq; scalar_t__ fv_intrhand; scalar_t__ fv_miibus; int /*<<< orphan*/  fv_link_task; struct ifnet* fv_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FV_LOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  FV_UNLOCK (struct fv_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct fv_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  fv_dma_free (struct fv_softc*) ; 
 int /*<<< orphan*/  fv_stop (struct fv_softc*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_swi ; 

__attribute__((used)) static int
fv_detach(device_t dev)
{
	struct fv_softc		*sc = device_get_softc(dev);
	struct ifnet		*ifp = sc->fv_ifp;

	KASSERT(mtx_initialized(&sc->fv_mtx), ("vr mutex not initialized"));

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		FV_LOCK(sc);
		sc->fv_detach = 1;
		fv_stop(sc);
		FV_UNLOCK(sc);
		taskqueue_drain(taskqueue_swi, &sc->fv_link_task);
		ether_ifdetach(ifp);
	}
#ifdef MII
	if (sc->fv_miibus)
		device_delete_child(dev, sc->fv_miibus);
#endif
	bus_generic_detach(dev);

	if (sc->fv_intrhand)
		bus_teardown_intr(dev, sc->fv_irq, sc->fv_intrhand);
	if (sc->fv_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->fv_irq);

	if (sc->fv_res)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->fv_rid, 
		    sc->fv_res);

	if (ifp)
		if_free(ifp);

	fv_dma_free(sc);

	mtx_destroy(&sc->fv_mtx);

	return (0);

}