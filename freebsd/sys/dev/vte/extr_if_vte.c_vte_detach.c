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
struct vte_softc {int /*<<< orphan*/  vte_mtx; struct ifnet* vte_ifp; int /*<<< orphan*/ * vte_res; int /*<<< orphan*/  vte_res_id; int /*<<< orphan*/  vte_res_type; int /*<<< orphan*/ * vte_irq; int /*<<< orphan*/ * vte_intrhand; int /*<<< orphan*/ * vte_miibus; int /*<<< orphan*/  vte_tick_ch; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vte_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vte_dma_free (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_stop (struct vte_softc*) ; 

__attribute__((used)) static int
vte_detach(device_t dev)
{
	struct vte_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	ifp = sc->vte_ifp;
	if (device_is_attached(dev)) {
		VTE_LOCK(sc);
		vte_stop(sc);
		VTE_UNLOCK(sc);
		callout_drain(&sc->vte_tick_ch);
		ether_ifdetach(ifp);
	}

	if (sc->vte_miibus != NULL) {
		device_delete_child(dev, sc->vte_miibus);
		sc->vte_miibus = NULL;
	}
	bus_generic_detach(dev);

	if (sc->vte_intrhand != NULL) {
		bus_teardown_intr(dev, sc->vte_irq, sc->vte_intrhand);
		sc->vte_intrhand = NULL;
	}
	if (sc->vte_irq != NULL) {
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->vte_irq);
		sc->vte_irq = NULL;
	}
	if (sc->vte_res != NULL) {
		bus_release_resource(dev, sc->vte_res_type, sc->vte_res_id,
		    sc->vte_res);
		sc->vte_res = NULL;
	}
	if (ifp != NULL) {
		if_free(ifp);
		sc->vte_ifp = NULL;
	}
	vte_dma_free(sc);
	mtx_destroy(&sc->vte_mtx);

	return (0);
}