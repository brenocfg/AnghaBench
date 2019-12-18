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
struct usb_ether {int dummy; } ;
struct ifnet {int if_capenable; } ;
struct axge_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXGE_ACCESS_MAC ; 
 int /*<<< orphan*/  AXGE_CRCR ; 
 int /*<<< orphan*/  AXGE_CTCR ; 
 int /*<<< orphan*/  AXGE_LOCK_ASSERT (struct axge_softc*,int /*<<< orphan*/ ) ; 
 int CRCR_IP ; 
 int CRCR_TCP ; 
 int CRCR_UDP ; 
 int CTCR_IP ; 
 int CTCR_TCP ; 
 int CTCR_UDP ; 
 int IFCAP_RXCSUM ; 
 int IFCAP_TXCSUM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  axge_write_cmd_1 (struct axge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ifnet* uether_getifp (struct usb_ether*) ; 
 struct axge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
axge_csum_cfg(struct usb_ether *ue)
{
	struct axge_softc *sc;
	struct ifnet *ifp;
	uint8_t csum;

	sc = uether_getsc(ue);
	AXGE_LOCK_ASSERT(sc, MA_OWNED);
	ifp = uether_getifp(ue);

	csum = 0;
	if ((ifp->if_capenable & IFCAP_TXCSUM) != 0)
		csum |= CTCR_IP | CTCR_TCP | CTCR_UDP;
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CTCR, csum);

	csum = 0;
	if ((ifp->if_capenable & IFCAP_RXCSUM) != 0)
		csum |= CRCR_IP | CRCR_TCP | CRCR_UDP;
	axge_write_cmd_1(sc, AXGE_ACCESS_MAC, AXGE_CRCR, csum);
}