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
typedef  int uint16_t ;
struct usb_ether {int dummy; } ;
struct ifnet {int if_capenable; } ;
struct axe_softc {int sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXE_772B_CMD_WRITE_RXCSUM ; 
 int /*<<< orphan*/  AXE_772B_CMD_WRITE_TXCSUM ; 
 int AXE_FLAG_772B ; 
 int /*<<< orphan*/  AXE_LOCK_ASSERT (struct axe_softc*,int /*<<< orphan*/ ) ; 
 int AXE_RXCSUM_ICMP ; 
 int AXE_RXCSUM_IGMP ; 
 int AXE_RXCSUM_IP ; 
 int AXE_RXCSUM_IPVE ; 
 int AXE_RXCSUM_TCP ; 
 int AXE_RXCSUM_UDP ; 
 int AXE_TXCSUM_IP ; 
 int AXE_TXCSUM_TCP ; 
 int AXE_TXCSUM_UDP ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  axe_cmd (struct axe_softc*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axe_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axe_csum_cfg(struct usb_ether *ue)
{
	struct axe_softc *sc;
	struct ifnet *ifp;
	uint16_t csum1, csum2;

	sc = uether_getsc(ue);
	AXE_LOCK_ASSERT(sc, MA_OWNED);

	if ((sc->sc_flags & AXE_FLAG_772B) != 0) {
		ifp = uether_getifp(ue);
		csum1 = 0;
		csum2 = 0;
		if ((ifp->if_capenable & IFCAP_TXCSUM) != 0)
			csum1 |= AXE_TXCSUM_IP | AXE_TXCSUM_TCP |
			    AXE_TXCSUM_UDP;
		axe_cmd(sc, AXE_772B_CMD_WRITE_TXCSUM, csum2, csum1, NULL);
		csum1 = 0;
		csum2 = 0;
		if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
			csum1 |= AXE_RXCSUM_IP | AXE_RXCSUM_IPVE |
			    AXE_RXCSUM_TCP | AXE_RXCSUM_UDP | AXE_RXCSUM_ICMP |
			    AXE_RXCSUM_IGMP;
		axe_cmd(sc, AXE_772B_CMD_WRITE_RXCSUM, csum2, csum1, NULL);
	}
}