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
struct vtnet_softc {int /*<<< orphan*/ * vtnet_ctrl_vq; struct ifnet* vtnet_ifp; int /*<<< orphan*/  vtnet_media; int /*<<< orphan*/ * vtnet_vlan_detach; int /*<<< orphan*/ * vtnet_vlan_attach; int /*<<< orphan*/  vtnet_tick_ch; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_LOCK_DESTROY (struct vtnet_softc*) ; 
 int /*<<< orphan*/  VTNET_CORE_UNLOCK (struct vtnet_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct vtnet_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netmap_detach (struct ifnet*) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 
 int /*<<< orphan*/  vtnet_drain_taskqueues (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_free_ctrl_vq (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_free_rx_filters (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_free_rxtx_queues (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_free_taskqueues (struct vtnet_softc*) ; 
 int /*<<< orphan*/  vtnet_stop (struct vtnet_softc*) ; 

__attribute__((used)) static int
vtnet_detach(device_t dev)
{
	struct vtnet_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->vtnet_ifp;

	if (device_is_attached(dev)) {
		VTNET_CORE_LOCK(sc);
		vtnet_stop(sc);
		VTNET_CORE_UNLOCK(sc);

		callout_drain(&sc->vtnet_tick_ch);
		vtnet_drain_taskqueues(sc);

		ether_ifdetach(ifp);
	}

#ifdef DEV_NETMAP
	netmap_detach(ifp);
#endif /* DEV_NETMAP */

	vtnet_free_taskqueues(sc);

	if (sc->vtnet_vlan_attach != NULL) {
		EVENTHANDLER_DEREGISTER(vlan_config, sc->vtnet_vlan_attach);
		sc->vtnet_vlan_attach = NULL;
	}
	if (sc->vtnet_vlan_detach != NULL) {
		EVENTHANDLER_DEREGISTER(vlan_unconfig, sc->vtnet_vlan_detach);
		sc->vtnet_vlan_detach = NULL;
	}

	ifmedia_removeall(&sc->vtnet_media);

	if (ifp != NULL) {
		if_free(ifp);
		sc->vtnet_ifp = NULL;
	}

	vtnet_free_rxtx_queues(sc);
	vtnet_free_rx_filters(sc);

	if (sc->vtnet_ctrl_vq != NULL)
		vtnet_free_ctrl_vq(sc);

	VTNET_CORE_LOCK_DESTROY(sc);

	return (0);
}