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
struct dc_softc {int /*<<< orphan*/  dc_mtx; struct dc_mediainfo* dc_srom; struct dc_mediainfo* dc_mi; struct dc_mediainfo* dc_pnic_rx_buf; scalar_t__ dc_res; scalar_t__ dc_irq; scalar_t__ dc_intrhand; scalar_t__ dc_miibus; int /*<<< orphan*/  dc_wdog_ch; int /*<<< orphan*/  dc_stat_ch; struct ifnet* dc_ifp; } ;
struct dc_mediainfo {struct dc_mediainfo* dc_next; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_RES ; 
 int /*<<< orphan*/  DC_RID ; 
 int /*<<< orphan*/  DC_UNLOCK (struct dc_softc*) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dc_dma_free (struct dc_softc*) ; 
 int /*<<< orphan*/  dc_stop (struct dc_softc*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct dc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ether_poll_deregister (struct ifnet*) ; 
 int /*<<< orphan*/  free (struct dc_mediainfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
dc_detach(device_t dev)
{
	struct dc_softc *sc;
	struct ifnet *ifp;
	struct dc_mediainfo *m;

	sc = device_get_softc(dev);
	KASSERT(mtx_initialized(&sc->dc_mtx), ("dc mutex not initialized"));

	ifp = sc->dc_ifp;

#ifdef DEVICE_POLLING
	if (ifp != NULL && ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	/* These should only be active if attach succeeded */
	if (device_is_attached(dev)) {
		DC_LOCK(sc);
		dc_stop(sc);
		DC_UNLOCK(sc);
		callout_drain(&sc->dc_stat_ch);
		callout_drain(&sc->dc_wdog_ch);
		ether_ifdetach(ifp);
	}
	if (sc->dc_miibus)
		device_delete_child(dev, sc->dc_miibus);
	bus_generic_detach(dev);

	if (sc->dc_intrhand)
		bus_teardown_intr(dev, sc->dc_irq, sc->dc_intrhand);
	if (sc->dc_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->dc_irq);
	if (sc->dc_res)
		bus_release_resource(dev, DC_RES, DC_RID, sc->dc_res);

	if (ifp != NULL)
		if_free(ifp);

	dc_dma_free(sc);

	free(sc->dc_pnic_rx_buf, M_DEVBUF);

	while (sc->dc_mi != NULL) {
		m = sc->dc_mi->dc_next;
		free(sc->dc_mi, M_DEVBUF);
		sc->dc_mi = m;
	}
	free(sc->dc_srom, M_DEVBUF);

	mtx_destroy(&sc->dc_mtx);

	return (0);
}