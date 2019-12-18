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
struct smsc_softc {int /*<<< orphan*/  sc_mac_csr; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC_MAC_CSR ; 
 int /*<<< orphan*/  SMSC_MAC_CSR_PRMS ; 
 int /*<<< orphan*/  smsc_dbg_printf (struct smsc_softc*,char*,char*) ; 
 int /*<<< orphan*/  smsc_write_reg (struct smsc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct smsc_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
smsc_setpromisc(struct usb_ether *ue)
{
	struct smsc_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	smsc_dbg_printf(sc, "promiscuous mode %sabled\n",
	                (ifp->if_flags & IFF_PROMISC) ? "en" : "dis");

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & IFF_PROMISC)
		sc->sc_mac_csr |= SMSC_MAC_CSR_PRMS;
	else
		sc->sc_mac_csr &= ~SMSC_MAC_CSR_PRMS;

	smsc_write_reg(sc, SMSC_MAC_CSR, sc->sc_mac_csr);
}