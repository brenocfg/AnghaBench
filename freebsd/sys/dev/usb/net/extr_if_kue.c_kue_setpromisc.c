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
struct kue_softc {int /*<<< orphan*/  sc_rxfilt; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  KUE_CMD_SET_PKT_FILTER ; 
 int /*<<< orphan*/  KUE_LOCK_ASSERT (struct kue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KUE_RXFILT_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  kue_setword (struct kue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct kue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
kue_setpromisc(struct usb_ether *ue)
{
	struct kue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	KUE_LOCK_ASSERT(sc, MA_OWNED);

	if (ifp->if_flags & IFF_PROMISC)
		sc->sc_rxfilt |= KUE_RXFILT_PROMISC;
	else
		sc->sc_rxfilt &= ~KUE_RXFILT_PROMISC;

	kue_setword(sc, KUE_CMD_SET_PKT_FILTER, sc->sc_rxfilt);
}