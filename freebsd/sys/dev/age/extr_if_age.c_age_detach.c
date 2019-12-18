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
struct age_softc {int age_flags; int /*<<< orphan*/  age_mtx; int /*<<< orphan*/ * age_res; int /*<<< orphan*/  age_res_spec; int /*<<< orphan*/ * age_irq; int /*<<< orphan*/  age_irq_spec; int /*<<< orphan*/ ** age_intrhand; struct ifnet* age_ifp; int /*<<< orphan*/ * age_miibus; int /*<<< orphan*/ * age_tq; int /*<<< orphan*/  age_int_task; int /*<<< orphan*/  age_link_task; int /*<<< orphan*/  age_tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int AGE_FLAG_DETACH ; 
 int AGE_FLAG_MSI ; 
 int AGE_FLAG_MSIX ; 
 int /*<<< orphan*/  AGE_LOCK (struct age_softc*) ; 
 int AGE_MSIX_MESSAGES ; 
 int AGE_MSI_MESSAGES ; 
 int /*<<< orphan*/  AGE_UNLOCK (struct age_softc*) ; 
 int /*<<< orphan*/  age_dma_free (struct age_softc*) ; 
 int /*<<< orphan*/  age_stop (struct age_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct age_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taskqueue_swi ; 

__attribute__((used)) static int
age_detach(device_t dev)
{
	struct age_softc *sc;
	struct ifnet *ifp;
	int i, msic;

	sc = device_get_softc(dev);

	ifp = sc->age_ifp;
	if (device_is_attached(dev)) {
		AGE_LOCK(sc);
		sc->age_flags |= AGE_FLAG_DETACH;
		age_stop(sc);
		AGE_UNLOCK(sc);
		callout_drain(&sc->age_tick_ch);
		taskqueue_drain(sc->age_tq, &sc->age_int_task);
		taskqueue_drain(taskqueue_swi, &sc->age_link_task);
		ether_ifdetach(ifp);
	}

	if (sc->age_tq != NULL) {
		taskqueue_drain(sc->age_tq, &sc->age_int_task);
		taskqueue_free(sc->age_tq);
		sc->age_tq = NULL;
	}

	if (sc->age_miibus != NULL) {
		device_delete_child(dev, sc->age_miibus);
		sc->age_miibus = NULL;
	}
	bus_generic_detach(dev);
	age_dma_free(sc);

	if (ifp != NULL) {
		if_free(ifp);
		sc->age_ifp = NULL;
	}

	if ((sc->age_flags & AGE_FLAG_MSIX) != 0)
		msic = AGE_MSIX_MESSAGES;
	else if ((sc->age_flags & AGE_FLAG_MSI) != 0)
		msic = AGE_MSI_MESSAGES;
	else
		msic = 1;
	for (i = 0; i < msic; i++) {
		if (sc->age_intrhand[i] != NULL) {
			bus_teardown_intr(dev, sc->age_irq[i],
			    sc->age_intrhand[i]);
			sc->age_intrhand[i] = NULL;
		}
	}

	bus_release_resources(dev, sc->age_irq_spec, sc->age_irq);
	if ((sc->age_flags & (AGE_FLAG_MSI | AGE_FLAG_MSIX)) != 0)
		pci_release_msi(dev);
	bus_release_resources(dev, sc->age_res_spec, sc->age_res);
	mtx_destroy(&sc->age_mtx);

	return (0);
}