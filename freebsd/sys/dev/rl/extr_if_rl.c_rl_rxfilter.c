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
struct rl_softc {struct ifnet* rl_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct rl_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct rl_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  RL_LOCK_ASSERT (struct rl_softc*) ; 
 int /*<<< orphan*/  RL_MAR0 ; 
 int /*<<< orphan*/  RL_MAR4 ; 
 int /*<<< orphan*/  RL_RXCFG ; 
 int RL_RXCFG_RX_ALLPHYS ; 
 int RL_RXCFG_RX_BROAD ; 
 int RL_RXCFG_RX_INDIV ; 
 int RL_RXCFG_RX_MULTI ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rl_hash_maddr ; 

__attribute__((used)) static void
rl_rxfilter(struct rl_softc *sc)
{
	struct ifnet		*ifp = sc->rl_ifp;
	uint32_t		hashes[2] = { 0, 0 };
	uint32_t		rxfilt;

	RL_LOCK_ASSERT(sc);

	rxfilt = CSR_READ_4(sc, RL_RXCFG);
	rxfilt &= ~(RL_RXCFG_RX_ALLPHYS | RL_RXCFG_RX_BROAD |
	    RL_RXCFG_RX_MULTI);
	/* Always accept frames destined for this host. */
	rxfilt |= RL_RXCFG_RX_INDIV;
	/* Set capture broadcast bit to capture broadcast frames. */
	if (ifp->if_flags & IFF_BROADCAST)
		rxfilt |= RL_RXCFG_RX_BROAD;
	if (ifp->if_flags & IFF_ALLMULTI || ifp->if_flags & IFF_PROMISC) {
		rxfilt |= RL_RXCFG_RX_MULTI;
		if (ifp->if_flags & IFF_PROMISC)
			rxfilt |= RL_RXCFG_RX_ALLPHYS;
		hashes[0] = 0xFFFFFFFF;
		hashes[1] = 0xFFFFFFFF;
	} else {
		/* Now program new ones. */
		if_foreach_llmaddr(ifp, rl_hash_maddr, hashes);
		if (hashes[0] != 0 || hashes[1] != 0)
			rxfilt |= RL_RXCFG_RX_MULTI;
	}

	CSR_WRITE_4(sc, RL_MAR0, hashes[0]);
	CSR_WRITE_4(sc, RL_MAR4, hashes[1]);
	CSR_WRITE_4(sc, RL_RXCFG, rxfilt);
}