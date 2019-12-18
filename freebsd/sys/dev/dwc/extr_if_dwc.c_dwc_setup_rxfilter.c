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
typedef  int uint32_t ;
struct ifnet {int if_flags; } ;
struct dwc_softc {scalar_t__ mactype; struct ifnet* ifp; } ;
struct dwc_hash_maddr_ctx {int* hash; struct dwc_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DWC_ASSERT_LOCKED (struct dwc_softc*) ; 
 scalar_t__ DWC_GMAC_ALT_DESC ; 
 int FRAME_FILTER_HMC ; 
 int FRAME_FILTER_PM ; 
 int FRAME_FILTER_PR ; 
 int /*<<< orphan*/  GMAC_MAC_HTHIGH ; 
 int /*<<< orphan*/  GMAC_MAC_HTLOW ; 
 int /*<<< orphan*/  HASH_TABLE_REG (int) ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int* IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  MAC_ADDRESS_HIGH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_ADDRESS_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAC_FRAME_FILTER ; 
 int /*<<< orphan*/  WRITE4 (struct dwc_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dwc_hash_maddr ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct dwc_hash_maddr_ctx*) ; 

__attribute__((used)) static void
dwc_setup_rxfilter(struct dwc_softc *sc)
{
	struct dwc_hash_maddr_ctx ctx;
	struct ifnet *ifp;
	uint8_t *eaddr;
	uint32_t ffval, hi, lo;
	int nhash, i;

	DWC_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	nhash = sc->mactype == DWC_GMAC_ALT_DESC ? 2 : 8;

	/*
	 * Set the multicast (group) filter hash.
	 */
	if ((ifp->if_flags & IFF_ALLMULTI) != 0) {
		ffval = (FRAME_FILTER_PM);
		for (i = 0; i < nhash; i++)
			ctx.hash[i] = ~0;
	} else {
		ffval = (FRAME_FILTER_HMC);
		for (i = 0; i < nhash; i++)
			ctx.hash[i] = 0;
		ctx.sc = sc;
		if_foreach_llmaddr(ifp, dwc_hash_maddr, &ctx);
	}

	/*
	 * Set the individual address filter hash.
	 */
	if (ifp->if_flags & IFF_PROMISC)
		ffval |= (FRAME_FILTER_PR);

	/*
	 * Set the primary address.
	 */
	eaddr = IF_LLADDR(ifp);
	lo = eaddr[0] | (eaddr[1] << 8) | (eaddr[2] << 16) |
	    (eaddr[3] << 24);
	hi = eaddr[4] | (eaddr[5] << 8);
	WRITE4(sc, MAC_ADDRESS_LOW(0), lo);
	WRITE4(sc, MAC_ADDRESS_HIGH(0), hi);
	WRITE4(sc, MAC_FRAME_FILTER, ffval);
	if (sc->mactype == DWC_GMAC_ALT_DESC) {
		WRITE4(sc, GMAC_MAC_HTLOW, ctx.hash[0]);
		WRITE4(sc, GMAC_MAC_HTHIGH, ctx.hash[1]);
	} else {
		for (i = 0; i < nhash; i++)
			WRITE4(sc, HASH_TABLE_REG(i), ctx.hash[i]);
	}
}