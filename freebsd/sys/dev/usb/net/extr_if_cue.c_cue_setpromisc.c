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
struct ifnet {int if_flags; } ;
struct cue_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUE_CLRBIT (struct cue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUE_ETHCTL ; 
 int /*<<< orphan*/  CUE_ETHCTL_PROMISC ; 
 int /*<<< orphan*/  CUE_LOCK_ASSERT (struct cue_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CUE_SETBIT (struct cue_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  cue_setmulti (struct usb_ether*) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct cue_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
cue_setpromisc(struct usb_ether *ue)
{
	struct cue_softc *sc = uether_getsc(ue);
	struct ifnet *ifp = uether_getifp(ue);

	CUE_LOCK_ASSERT(sc, MA_OWNED);

	/* if we want promiscuous mode, set the allframes bit */
	if (ifp->if_flags & IFF_PROMISC)
		CUE_SETBIT(sc, CUE_ETHCTL, CUE_ETHCTL_PROMISC);
	else
		CUE_CLRBIT(sc, CUE_ETHCTL, CUE_ETHCTL_PROMISC);

	/* write multicast hash-bits */
	cue_setmulti(ue);
}