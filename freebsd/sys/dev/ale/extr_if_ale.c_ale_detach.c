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
struct ale_softc {int ale_flags; int /*<<< orphan*/  ale_mtx; int /*<<< orphan*/ * ale_res; int /*<<< orphan*/  ale_res_spec; int /*<<< orphan*/ * ale_irq; int /*<<< orphan*/  ale_irq_spec; int /*<<< orphan*/ ** ale_intrhand; struct ifnet* ale_ifp; int /*<<< orphan*/ * ale_miibus; int /*<<< orphan*/ * ale_tq; int /*<<< orphan*/  ale_int_task; int /*<<< orphan*/  ale_tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALE_FLAG_MSI ; 
 int ALE_FLAG_MSIX ; 
 int /*<<< orphan*/  ALE_LOCK (struct ale_softc*) ; 
 int ALE_MSIX_MESSAGES ; 
 int ALE_MSI_MESSAGES ; 
 int /*<<< orphan*/  ALE_UNLOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_dma_free (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_stop (struct ale_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ale_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ale_detach(device_t dev)
{
	struct ale_softc *sc;
	struct ifnet *ifp;
	int i, msic;

	sc = device_get_softc(dev);

	ifp = sc->ale_ifp;
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		ALE_LOCK(sc);
		ale_stop(sc);
		ALE_UNLOCK(sc);
		callout_drain(&sc->ale_tick_ch);
		taskqueue_drain(sc->ale_tq, &sc->ale_int_task);
	}

	if (sc->ale_tq != NULL) {
		taskqueue_drain(sc->ale_tq, &sc->ale_int_task);
		taskqueue_free(sc->ale_tq);
		sc->ale_tq = NULL;
	}

	if (sc->ale_miibus != NULL) {
		device_delete_child(dev, sc->ale_miibus);
		sc->ale_miibus = NULL;
	}
	bus_generic_detach(dev);
	ale_dma_free(sc);

	if (ifp != NULL) {
		if_free(ifp);
		sc->ale_ifp = NULL;
	}

	if ((sc->ale_flags & ALE_FLAG_MSIX) != 0)
		msic = ALE_MSIX_MESSAGES;
	else if ((sc->ale_flags & ALE_FLAG_MSI) != 0)
		msic = ALE_MSI_MESSAGES;
	else
		msic = 1;
	for (i = 0; i < msic; i++) {
		if (sc->ale_intrhand[i] != NULL) {
			bus_teardown_intr(dev, sc->ale_irq[i],
			    sc->ale_intrhand[i]);
			sc->ale_intrhand[i] = NULL;
		}
	}

	bus_release_resources(dev, sc->ale_irq_spec, sc->ale_irq);
	if ((sc->ale_flags & (ALE_FLAG_MSI | ALE_FLAG_MSIX)) != 0)
		pci_release_msi(dev);
	bus_release_resources(dev, sc->ale_res_spec, sc->ale_res);
	mtx_destroy(&sc->ale_mtx);

	return (0);
}