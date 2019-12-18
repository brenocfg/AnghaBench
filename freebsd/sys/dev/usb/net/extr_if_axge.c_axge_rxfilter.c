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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct usb_ether {int dummy; } ;
struct ifnet {int if_flags; } ;
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 int /*<<< orphan*/  AXGE_LOCK_ASSERT (struct axge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AXGE_MFA ; 
 int /*<<< orphan*/  AXGE_RCR ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int RCR_ACPT_ALL_MCAST ; 
 int RCR_ACPT_BCAST ; 
 int RCR_ACPT_MCAST ; 
 int RCR_DROP_CRCERR ; 
 int RCR_PROMISC ; 
 int RCR_START ; 
 int /*<<< orphan*/  axge_hash_maddr ; 
 int /*<<< orphan*/  axge_write_cmd_2 (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  axge_write_mem (struct axge_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axge_rxfilter(struct usb_ether *ue)
{
	struct axge_softc *sc;
	struct ifnet *ifp;
	uint16_t rxmode;
	uint8_t hashtbl[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

	sc = uether_getsc(ue);
	ifp = uether_getifp(ue);
	AXGE_LOCK_ASSERT(sc, MA_OWNED);

	/*
	 * Configure RX settings.
	 * Don't set RCR_IPE(IP header alignment on 32bit boundary) to disable
	 * inserting extra padding bytes.  This wastes ethernet to USB host
	 * bandwidth as well as complicating RX handling logic.  Current USB
	 * framework requires copying RX frames to mbufs so there is no need
	 * to worry about alignment.
	 */
	rxmode = RCR_DROP_CRCERR | RCR_START;
	if (ifp->if_flags & IFF_BROADCAST)
		rxmode |= RCR_ACPT_BCAST;
	if (ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) {
		if (ifp->if_flags & IFF_PROMISC)
			rxmode |= RCR_PROMISC;
		rxmode |= RCR_ACPT_ALL_MCAST;
		axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);
		return;
	}

	rxmode |= RCR_ACPT_MCAST;
	if_foreach_llmaddr(ifp, axge_hash_maddr, &hashtbl);

	axge_write_mem(sc, AXGE_ACCESS_MAC, 8, AXGE_MFA, (void *)&hashtbl, 8);
	axge_write_cmd_2(sc, AXGE_ACCESS_MAC, 2, AXGE_RCR, rxmode);
}