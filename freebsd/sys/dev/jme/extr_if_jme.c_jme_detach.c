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
struct jme_softc {int jme_flags; int /*<<< orphan*/  jme_mtx; int /*<<< orphan*/ ** jme_res; int /*<<< orphan*/  jme_res_spec; int /*<<< orphan*/ ** jme_irq; int /*<<< orphan*/  jme_irq_spec; int /*<<< orphan*/ ** jme_intrhand; struct ifnet* jme_ifp; int /*<<< orphan*/ * jme_miibus; int /*<<< orphan*/ * jme_tq; int /*<<< orphan*/  jme_int_task; int /*<<< orphan*/  jme_eaddr; int /*<<< orphan*/  jme_link_task; int /*<<< orphan*/  jme_tick_ch; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int JME_FLAG_DETACH ; 
 int JME_FLAG_EFUSE ; 
 int JME_FLAG_MSI ; 
 int JME_FLAG_MSIX ; 
 int /*<<< orphan*/  JME_LOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_UNLOCK (struct jme_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct jme_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  jme_dma_free (struct jme_softc*) ; 
 int /*<<< orphan*/  jme_set_macaddr (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jme_stop (struct jme_softc*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * taskqueue_swi ; 

__attribute__((used)) static int
jme_detach(device_t dev)
{
	struct jme_softc *sc;
	struct ifnet *ifp;
	int i;

	sc = device_get_softc(dev);

	ifp = sc->jme_ifp;
	if (device_is_attached(dev)) {
		JME_LOCK(sc);
		sc->jme_flags |= JME_FLAG_DETACH;
		jme_stop(sc);
		JME_UNLOCK(sc);
		callout_drain(&sc->jme_tick_ch);
		taskqueue_drain(sc->jme_tq, &sc->jme_int_task);
		taskqueue_drain(taskqueue_swi, &sc->jme_link_task);
		/* Restore possibly modified station address. */
		if ((sc->jme_flags & JME_FLAG_EFUSE) != 0)
			jme_set_macaddr(sc, sc->jme_eaddr);
		ether_ifdetach(ifp);
	}

	if (sc->jme_tq != NULL) {
		taskqueue_drain(sc->jme_tq, &sc->jme_int_task);
		taskqueue_free(sc->jme_tq);
		sc->jme_tq = NULL;
	}

	if (sc->jme_miibus != NULL) {
		device_delete_child(dev, sc->jme_miibus);
		sc->jme_miibus = NULL;
	}
	bus_generic_detach(dev);
	jme_dma_free(sc);

	if (ifp != NULL) {
		if_free(ifp);
		sc->jme_ifp = NULL;
	}

	for (i = 0; i < 1; i++) {
		if (sc->jme_intrhand[i] != NULL) {
			bus_teardown_intr(dev, sc->jme_irq[i],
			    sc->jme_intrhand[i]);
			sc->jme_intrhand[i] = NULL;
		}
	}

	if (sc->jme_irq[0] != NULL)
		bus_release_resources(dev, sc->jme_irq_spec, sc->jme_irq);
	if ((sc->jme_flags & (JME_FLAG_MSIX | JME_FLAG_MSI)) != 0)
		pci_release_msi(dev);
	if (sc->jme_res[0] != NULL)
		bus_release_resources(dev, sc->jme_res_spec, sc->jme_res);
	mtx_destroy(&sc->jme_mtx);

	return (0);
}