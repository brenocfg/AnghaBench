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
struct xae_softc {int /*<<< orphan*/  xae_callout; int /*<<< orphan*/  mii_softc; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RCW1_RX ; 
 int /*<<< orphan*/  TC_TX ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XAE_ASSERT_LOCKED (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_RCW1 ; 
 int /*<<< orphan*/  XAE_TC ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xae_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  mii_mediachg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xae_setup_rxfilter (struct xae_softc*) ; 
 int /*<<< orphan*/  xae_tick ; 

__attribute__((used)) static void
xae_init_locked(struct xae_softc *sc)
{
	struct ifnet *ifp;

	XAE_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	ifp->if_drv_flags |= IFF_DRV_RUNNING;

	xae_setup_rxfilter(sc);

	/* Enable the transmitter */
	WRITE4(sc, XAE_TC, TC_TX);

	/* Enable the receiver. */
	WRITE4(sc, XAE_RCW1, RCW1_RX);

	/*
	 * Call mii_mediachg() which will call back into xae_miibus_statchg()
	 * to set up the remaining config registers based on current media.
	 */
	mii_mediachg(sc->mii_softc);
	callout_reset(&sc->xae_callout, hz, xae_tick, sc);
}