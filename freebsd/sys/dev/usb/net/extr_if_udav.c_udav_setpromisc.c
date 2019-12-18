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
typedef  int uint8_t ;
struct usb_ether {struct udav_softc* ue_sc; } ;
struct udav_softc {int /*<<< orphan*/  sc_ue; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  UDAV_RCR ; 
 int UDAV_RCR_ALL ; 
 int UDAV_RCR_PRMSC ; 
 int udav_csr_read1 (struct udav_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udav_csr_write1 (struct udav_softc*,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
udav_setpromisc(struct usb_ether *ue)
{
	struct udav_softc *sc = ue->ue_sc;
	struct ifnet *ifp = uether_getifp(&sc->sc_ue);
	uint8_t rxmode;

	rxmode = udav_csr_read1(sc, UDAV_RCR);
	rxmode &= ~(UDAV_RCR_ALL | UDAV_RCR_PRMSC);

	if (ifp->if_flags & IFF_PROMISC)
		rxmode |= UDAV_RCR_ALL | UDAV_RCR_PRMSC;
	else if (ifp->if_flags & IFF_ALLMULTI)
		rxmode |= UDAV_RCR_ALL;

	/* write new mode bits */
	udav_csr_write1(sc, UDAV_RCR, rxmode);
}