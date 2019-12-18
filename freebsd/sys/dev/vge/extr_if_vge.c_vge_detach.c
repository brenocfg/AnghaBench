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
struct vge_softc {int vge_flags; int /*<<< orphan*/  vge_mtx; scalar_t__ vge_res; scalar_t__ vge_irq; scalar_t__ vge_intrhand; scalar_t__ vge_miibus; int /*<<< orphan*/  vge_watchdog; struct ifnet* vge_ifp; } ;
struct ifnet {int if_capenable; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int PCIR_BAR (int) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int VGE_FLAG_MSI ; 
 int /*<<< orphan*/  VGE_LOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  VGE_UNLOCK (struct vge_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct vge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vge_dma_free (struct vge_softc*) ; 
 int /*<<< orphan*/  vge_stop (struct vge_softc*) ; 

__attribute__((used)) static int
vge_detach(device_t dev)
{
	struct vge_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->vge_mtx), ("vge mutex not initialized"));
	ifp = sc->vge_ifp;

#ifdef DEVICE_POLLING
	if (ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		VGE_LOCK(sc);
		vge_stop(sc);
		VGE_UNLOCK(sc);
		callout_drain(&sc->vge_watchdog);
	}
	if (sc->vge_miibus)
		device_delete_child(dev, sc->vge_miibus);
	bus_generic_detach(dev);

	if (sc->vge_intrhand)
		bus_teardown_intr(dev, sc->vge_irq, sc->vge_intrhand);
	if (sc->vge_irq)
		bus_release_resource(dev, SYS_RES_IRQ,
		    sc->vge_flags & VGE_FLAG_MSI ? 1 : 0, sc->vge_irq);
	if (sc->vge_flags & VGE_FLAG_MSI)
		pci_release_msi(dev);
	if (sc->vge_res)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    PCIR_BAR(1), sc->vge_res);
	if (ifp)
		if_free(ifp);

	vge_dma_free(sc);
	mtx_destroy(&sc->vge_mtx);

	return (0);
}