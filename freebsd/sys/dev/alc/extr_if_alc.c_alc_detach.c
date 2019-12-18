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
struct alc_softc {int alc_flags; int /*<<< orphan*/  alc_mtx; int /*<<< orphan*/ ** alc_res; int /*<<< orphan*/  alc_res_spec; int /*<<< orphan*/ ** alc_irq; int /*<<< orphan*/  alc_irq_spec; int /*<<< orphan*/ ** alc_intrhand; struct ifnet* alc_ifp; int /*<<< orphan*/ * alc_miibus; int /*<<< orphan*/ * alc_tq; int /*<<< orphan*/  alc_int_task; int /*<<< orphan*/  alc_tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ALC_FLAG_MSI ; 
 int ALC_FLAG_MSIX ; 
 int /*<<< orphan*/  ALC_LOCK (struct alc_softc*) ; 
 int ALC_MSIX_MESSAGES ; 
 int ALC_MSI_MESSAGES ; 
 int /*<<< orphan*/  ALC_UNLOCK (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_dma_free (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_phy_down (struct alc_softc*) ; 
 int /*<<< orphan*/  alc_stop (struct alc_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct alc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
alc_detach(device_t dev)
{
	struct alc_softc *sc;
	struct ifnet *ifp;
	int i, msic;

	sc = device_get_softc(dev);

	ifp = sc->alc_ifp;
	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		ALC_LOCK(sc);
		alc_stop(sc);
		ALC_UNLOCK(sc);
		callout_drain(&sc->alc_tick_ch);
		taskqueue_drain(sc->alc_tq, &sc->alc_int_task);
	}

	if (sc->alc_tq != NULL) {
		taskqueue_drain(sc->alc_tq, &sc->alc_int_task);
		taskqueue_free(sc->alc_tq);
		sc->alc_tq = NULL;
	}

	if (sc->alc_miibus != NULL) {
		device_delete_child(dev, sc->alc_miibus);
		sc->alc_miibus = NULL;
	}
	bus_generic_detach(dev);
	alc_dma_free(sc);

	if (ifp != NULL) {
		if_free(ifp);
		sc->alc_ifp = NULL;
	}

	if ((sc->alc_flags & ALC_FLAG_MSIX) != 0)
		msic = ALC_MSIX_MESSAGES;
	else if ((sc->alc_flags & ALC_FLAG_MSI) != 0)
		msic = ALC_MSI_MESSAGES;
	else
		msic = 1;
	for (i = 0; i < msic; i++) {
		if (sc->alc_intrhand[i] != NULL) {
			bus_teardown_intr(dev, sc->alc_irq[i],
			    sc->alc_intrhand[i]);
			sc->alc_intrhand[i] = NULL;
		}
	}
	if (sc->alc_res[0] != NULL)
		alc_phy_down(sc);
	bus_release_resources(dev, sc->alc_irq_spec, sc->alc_irq);
	if ((sc->alc_flags & (ALC_FLAG_MSI | ALC_FLAG_MSIX)) != 0)
		pci_release_msi(dev);
	bus_release_resources(dev, sc->alc_res_spec, sc->alc_res);
	mtx_destroy(&sc->alc_mtx);

	return (0);
}