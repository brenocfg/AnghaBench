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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct msk_softc {int dummy; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_port; struct ifnet* msk_ifp; struct msk_softc* msk_softc; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  mchash ;

/* Variables and functions */
 int GMAC_READ_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMAC_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GM_MC_ADDR_H1 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H2 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H3 ; 
 int /*<<< orphan*/  GM_MC_ADDR_H4 ; 
 int GM_RXCR_MCF_ENA ; 
 int GM_RXCR_UCF_ENA ; 
 int /*<<< orphan*/  GM_RX_CTRL ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  msk_hash_maddr ; 

__attribute__((used)) static void
msk_rxfilter(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	struct ifnet *ifp;
	uint32_t mchash[2];
	uint16_t mode;

	sc = sc_if->msk_softc;

	MSK_IF_LOCK_ASSERT(sc_if);

	ifp = sc_if->msk_ifp;

	bzero(mchash, sizeof(mchash));
	mode = GMAC_READ_2(sc, sc_if->msk_port, GM_RX_CTRL);
	if ((ifp->if_flags & IFF_PROMISC) != 0)
		mode &= ~(GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA);
	else if ((ifp->if_flags & IFF_ALLMULTI) != 0) {
		mode |= GM_RXCR_UCF_ENA | GM_RXCR_MCF_ENA;
		mchash[0] = 0xffff;
		mchash[1] = 0xffff;
	} else {
		mode |= GM_RXCR_UCF_ENA;
		if_foreach_llmaddr(ifp, msk_hash_maddr, mchash);
		if (mchash[0] != 0 || mchash[1] != 0)
			mode |= GM_RXCR_MCF_ENA;
	}

	GMAC_WRITE_2(sc, sc_if->msk_port, GM_MC_ADDR_H1,
	    mchash[0] & 0xffff);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_MC_ADDR_H2,
	    (mchash[0] >> 16) & 0xffff);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_MC_ADDR_H3,
	    mchash[1] & 0xffff);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_MC_ADDR_H4,
	    (mchash[1] >> 16) & 0xffff);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_RX_CTRL, mode);
}