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
typedef  int /*<<< orphan*/  u32 ;
struct ifnet {int dummy; } ;
struct bce_softc {int bce_flags; int bce_phy_flags; int /*<<< orphan*/  bce_miibus; int /*<<< orphan*/  bce_ifmedia; int /*<<< orphan*/  bce_pulse_callout; struct ifnet* bce_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_DRV_MSG_CODE_UNLOAD ; 
 int /*<<< orphan*/  BCE_DRV_MSG_CODE_UNLOAD_LNK_DN ; 
 int /*<<< orphan*/  BCE_LOCK (struct bce_softc*) ; 
 int BCE_NO_WOL_FLAG ; 
 int BCE_PHY_REMOTE_CAP_FLAG ; 
 int /*<<< orphan*/  BCE_UNLOCK (struct bce_softc*) ; 
 int BCE_VERBOSE_RESET ; 
 int BCE_VERBOSE_UNLOAD ; 
 int /*<<< orphan*/  DBENTER (int) ; 
 int /*<<< orphan*/  DBEXIT (int) ; 
 int /*<<< orphan*/  bce_release_resources (struct bce_softc*) ; 
 int /*<<< orphan*/  bce_reset (struct bce_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bce_stop (struct bce_softc*) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bce_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bce_detach(device_t dev)
{
	struct bce_softc *sc = device_get_softc(dev);
	struct ifnet *ifp;
	u32 msg;

	DBENTER(BCE_VERBOSE_UNLOAD | BCE_VERBOSE_RESET);

	ifp = sc->bce_ifp;

	/* Stop and reset the controller. */
	BCE_LOCK(sc);

	/* Stop the pulse so the bootcode can go to driver absent state. */
	callout_stop(&sc->bce_pulse_callout);

	bce_stop(sc);
	if (sc->bce_flags & BCE_NO_WOL_FLAG)
		msg = BCE_DRV_MSG_CODE_UNLOAD_LNK_DN;
	else
		msg = BCE_DRV_MSG_CODE_UNLOAD;
	bce_reset(sc, msg);

	BCE_UNLOCK(sc);

	ether_ifdetach(ifp);

	/* If we have a child device on the MII bus remove it too. */
	if ((sc->bce_phy_flags & BCE_PHY_REMOTE_CAP_FLAG) != 0)
		ifmedia_removeall(&sc->bce_ifmedia);
	else {
		bus_generic_detach(dev);
		device_delete_child(dev, sc->bce_miibus);
	}

	/* Release all remaining resources. */
	bce_release_resources(sc);

	DBEXIT(BCE_VERBOSE_UNLOAD | BCE_VERBOSE_RESET);

	return(0);
}