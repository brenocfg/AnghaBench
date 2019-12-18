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
struct ifnet {int if_drv_flags; } ;
struct hn_softc {int hn_flags; int /*<<< orphan*/  hn_vf_lock; int /*<<< orphan*/ * hn_xact; int /*<<< orphan*/  hn_prichan; int /*<<< orphan*/ * hn_vf_taskq; int /*<<< orphan*/ * hn_mgmt_taskq0; int /*<<< orphan*/ ** hn_tx_taskqs; int /*<<< orphan*/  hn_media; struct ifnet* hn_vf_ifp; int /*<<< orphan*/ * hn_ifnet_lnkhand; int /*<<< orphan*/ * hn_ifnet_dethand; int /*<<< orphan*/ * hn_ifnet_atthand; int /*<<< orphan*/ * hn_ifnet_evthand; int /*<<< orphan*/ * hn_ifaddr_evthand; struct ifnet* hn_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int HN_FLAG_SYNTH_ATTACHED ; 
 int /*<<< orphan*/  HN_LOCK (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_LOCK_DESTROY (struct hn_softc*) ; 
 int /*<<< orphan*/  HN_UNLOCK (struct hn_softc*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  __compiler_membar () ; 
 struct hn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifattach_event ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hn_destroy_rx_data (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_destroy_tx_data (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_ifnet_detevent (struct hn_softc*,struct ifnet*) ; 
 int /*<<< orphan*/  hn_stop (struct hn_softc*,int) ; 
 int /*<<< orphan*/  hn_suspend_mgmt (struct hn_softc*) ; 
 int /*<<< orphan*/  hn_synth_detach (struct hn_softc*) ; 
 int hn_tx_taskq_cnt ; 
 int /*<<< orphan*/ ** hn_tx_taskque ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifaddr_event ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ifnet_departure_event ; 
 int /*<<< orphan*/  ifnet_event ; 
 int /*<<< orphan*/  ifnet_link_event ; 
 int /*<<< orphan*/  rm_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 
 scalar_t__ vmbus_chan_is_revoked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_chan_unset_orphan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_xact_ctx_orphan (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
hn_detach(device_t dev)
{
	struct hn_softc *sc = device_get_softc(dev);
	struct ifnet *ifp = sc->hn_ifp, *vf_ifp;

	if (sc->hn_xact != NULL && vmbus_chan_is_revoked(sc->hn_prichan)) {
		/*
		 * In case that the vmbus missed the orphan handler
		 * installation.
		 */
		vmbus_xact_ctx_orphan(sc->hn_xact);
	}

	if (sc->hn_ifaddr_evthand != NULL)
		EVENTHANDLER_DEREGISTER(ifaddr_event, sc->hn_ifaddr_evthand);
	if (sc->hn_ifnet_evthand != NULL)
		EVENTHANDLER_DEREGISTER(ifnet_event, sc->hn_ifnet_evthand);
	if (sc->hn_ifnet_atthand != NULL) {
		EVENTHANDLER_DEREGISTER(ether_ifattach_event,
		    sc->hn_ifnet_atthand);
	}
	if (sc->hn_ifnet_dethand != NULL) {
		EVENTHANDLER_DEREGISTER(ifnet_departure_event,
		    sc->hn_ifnet_dethand);
	}
	if (sc->hn_ifnet_lnkhand != NULL)
		EVENTHANDLER_DEREGISTER(ifnet_link_event, sc->hn_ifnet_lnkhand);

	vf_ifp = sc->hn_vf_ifp;
	__compiler_membar();
	if (vf_ifp != NULL)
		hn_ifnet_detevent(sc, vf_ifp);

	if (device_is_attached(dev)) {
		HN_LOCK(sc);
		if (sc->hn_flags & HN_FLAG_SYNTH_ATTACHED) {
			if (ifp->if_drv_flags & IFF_DRV_RUNNING)
				hn_stop(sc, true);
			/*
			 * NOTE:
			 * hn_stop() only suspends data, so managment
			 * stuffs have to be suspended manually here.
			 */
			hn_suspend_mgmt(sc);
			hn_synth_detach(sc);
		}
		HN_UNLOCK(sc);
		ether_ifdetach(ifp);
	}

	ifmedia_removeall(&sc->hn_media);
	hn_destroy_rx_data(sc);
	hn_destroy_tx_data(sc);

	if (sc->hn_tx_taskqs != NULL && sc->hn_tx_taskqs != hn_tx_taskque) {
		int i;

		for (i = 0; i < hn_tx_taskq_cnt; ++i)
			taskqueue_free(sc->hn_tx_taskqs[i]);
		free(sc->hn_tx_taskqs, M_DEVBUF);
	}
	taskqueue_free(sc->hn_mgmt_taskq0);
	if (sc->hn_vf_taskq != NULL)
		taskqueue_free(sc->hn_vf_taskq);

	if (sc->hn_xact != NULL) {
		/*
		 * Uninstall the orphan handler _before_ the xact is
		 * destructed.
		 */
		vmbus_chan_unset_orphan(sc->hn_prichan);
		vmbus_xact_ctx_destroy(sc->hn_xact);
	}

	if_free(ifp);

	HN_LOCK_DESTROY(sc);
	rm_destroy(&sc->hn_vf_lock);
	return (0);
}