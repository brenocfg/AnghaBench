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
struct vr_softc {int /*<<< orphan*/  vr_mtx; scalar_t__ vr_res; int /*<<< orphan*/  vr_res_id; int /*<<< orphan*/  vr_res_type; scalar_t__ vr_irq; scalar_t__ vr_intrhand; scalar_t__ vr_miibus; int /*<<< orphan*/  vr_inttask; int /*<<< orphan*/  vr_stat_callout; int /*<<< orphan*/  vr_flags; struct ifnet* vr_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  VR_F_DETACHED ; 
 int /*<<< orphan*/  VR_LOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  VR_UNLOCK (struct vr_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vr_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_fast ; 
 int /*<<< orphan*/  vr_dma_free (struct vr_softc*) ; 
 int /*<<< orphan*/  vr_stop (struct vr_softc*) ; 

__attribute__((used)) static int
vr_detach(device_t dev)
{
	struct vr_softc		*sc = device_get_softc(dev);
	struct ifnet		*ifp = sc->vr_ifp;

	KASSERT(mtx_initialized(&sc->vr_mtx), ("vr mutex not initialized"));

#ifdef DEVICE_POLLING
	if (ifp != NULL && ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* These should only be active if attach succeeded. */
	if (device_is_attached(dev)) {
		VR_LOCK(sc);
		sc->vr_flags |= VR_F_DETACHED;
		vr_stop(sc);
		VR_UNLOCK(sc);
		callout_drain(&sc->vr_stat_callout);
		taskqueue_drain(taskqueue_fast, &sc->vr_inttask);
		ether_ifdetach(ifp);
	}
	if (sc->vr_miibus)
		device_delete_child(dev, sc->vr_miibus);
	bus_generic_detach(dev);

	if (sc->vr_intrhand)
		bus_teardown_intr(dev, sc->vr_irq, sc->vr_intrhand);
	if (sc->vr_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->vr_irq);
	if (sc->vr_res)
		bus_release_resource(dev, sc->vr_res_type, sc->vr_res_id,
		    sc->vr_res);

	if (ifp)
		if_free(ifp);

	vr_dma_free(sc);

	mtx_destroy(&sc->vr_mtx);

	return (0);
}