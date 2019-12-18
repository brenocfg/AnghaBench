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
typedef  int /*<<< orphan*/  uint32_t ;
struct xae_softc {int /*<<< orphan*/  xae_callout; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  RCW1_RX ; 
 int /*<<< orphan*/  READ4 (struct xae_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TC_TX ; 
 int /*<<< orphan*/  WRITE4 (struct xae_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XAE_ASSERT_LOCKED (struct xae_softc*) ; 
 int /*<<< orphan*/  XAE_RCW1 ; 
 int /*<<< orphan*/  XAE_TC ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xae_stop_locked(struct xae_softc *sc)
{
	struct ifnet *ifp;
	uint32_t reg;

	XAE_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);

	callout_stop(&sc->xae_callout);

	/* Stop the transmitter */
	reg = READ4(sc, XAE_TC);
	reg &= ~TC_TX;
	WRITE4(sc, XAE_TC, reg);

	/* Stop the receiver. */
	reg = READ4(sc, XAE_RCW1);
	reg &= ~RCW1_RX;
	WRITE4(sc, XAE_RCW1, reg);
}