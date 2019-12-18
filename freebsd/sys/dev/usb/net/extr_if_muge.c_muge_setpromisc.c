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
struct usb_ether {int dummy; } ;
struct muge_softc {int sc_rfe_ctl; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_RFE_CTL ; 
 int ETH_RFE_CTL_MCAST_EN_ ; 
 int ETH_RFE_CTL_UCAST_EN_ ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MUGE_LOCK_ASSERT (struct muge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lan78xx_write_reg (struct muge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*,char*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
muge_setpromisc(struct usb_ether *ue)
{
	struct muge_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	muge_dbg_printf(sc, "promiscuous mode %sabled\n",
	    (ifp->if_flags & IFF_PROMISC) ? "en" : "dis");

	MUGE_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & IFF_PROMISC)
		sc->sc_rfe_ctl |= ETH_RFE_CTL_MCAST_EN_ | ETH_RFE_CTL_UCAST_EN_;
	else
		sc->sc_rfe_ctl &= ~(ETH_RFE_CTL_MCAST_EN_);

	lan78xx_write_reg(sc, ETH_RFE_CTL, sc->sc_rfe_ctl);
}