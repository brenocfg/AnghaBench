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
struct rue_softc {int dummy; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  RUE_CLRBIT (struct rue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUE_LOCK_ASSERT (struct rue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RUE_RCR ; 
 int /*<<< orphan*/  RUE_RCR_AAP ; 
 int /*<<< orphan*/  RUE_SETBIT (struct rue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct rue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
rue_setpromisc(struct usb_ether *ue)
{
	struct rue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	RUE_LOCK_ASSERT(sc, MA_OWNED);

	/* If we want promiscuous mode, set the allframes bit. */
	if (ifp->if_flags & IFF_PROMISC)
		RUE_SETBIT(sc, RUE_RCR, RUE_RCR_AAP);
	else
		RUE_CLRBIT(sc, RUE_RCR, RUE_RCR_AAP);
}