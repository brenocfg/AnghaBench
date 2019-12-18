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
struct bge_softc {int bge_flags; int /*<<< orphan*/ * bge_miibus; int /*<<< orphan*/  bge_ifmedia; int /*<<< orphan*/  bge_intr_task; scalar_t__ bge_tq; int /*<<< orphan*/  bge_stat_ch; int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int BGE_FLAG_TBI ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  bge_release_resources (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_stop (struct bge_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct bge_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_poll_deregister (int /*<<< orphan*/ ) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bge_detach(device_t dev)
{
	struct bge_softc *sc;
	if_t ifp;

	sc = device_get_softc(dev);
	ifp = sc->bge_ifp;

#ifdef DEVICE_POLLING
	if (if_getcapenable(ifp) & IFCAP_POLLING)
		ether_poll_deregister(ifp);
#endif

	if (device_is_attached(dev)) {
		ether_ifdetach(ifp);
		BGE_LOCK(sc);
		bge_stop(sc);
		BGE_UNLOCK(sc);
		callout_drain(&sc->bge_stat_ch);
	}

	if (sc->bge_tq)
		taskqueue_drain(sc->bge_tq, &sc->bge_intr_task);

	if (sc->bge_flags & BGE_FLAG_TBI)
		ifmedia_removeall(&sc->bge_ifmedia);
	else if (sc->bge_miibus != NULL) {
		bus_generic_detach(dev);
		device_delete_child(dev, sc->bge_miibus);
	}

	bge_release_resources(sc);

	return (0);
}