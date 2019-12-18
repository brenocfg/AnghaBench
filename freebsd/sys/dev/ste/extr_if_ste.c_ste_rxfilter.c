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
struct ste_softc {struct ifnet* ste_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_1 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_1 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CSR_WRITE_2 (struct ste_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_MAR0 ; 
 int /*<<< orphan*/  STE_MAR1 ; 
 int /*<<< orphan*/  STE_MAR2 ; 
 int /*<<< orphan*/  STE_MAR3 ; 
 int STE_RXMODE_ALLMULTI ; 
 int STE_RXMODE_BROADCAST ; 
 int STE_RXMODE_MULTIHASH ; 
 int STE_RXMODE_PROMISC ; 
 int STE_RXMODE_UNICAST ; 
 int /*<<< orphan*/  STE_RX_MODE ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ste_hash_maddr ; 

__attribute__((used)) static void
ste_rxfilter(struct ste_softc *sc)
{
	struct ifnet *ifp;
	uint32_t hashes[2] = { 0, 0 };
	uint8_t rxcfg;

	STE_LOCK_ASSERT(sc);

	ifp = sc->ste_ifp;
	rxcfg = CSR_READ_1(sc, STE_RX_MODE);
	rxcfg |= STE_RXMODE_UNICAST;
	rxcfg &= ~(STE_RXMODE_ALLMULTI | STE_RXMODE_MULTIHASH |
	    STE_RXMODE_BROADCAST | STE_RXMODE_PROMISC);
	if (ifp->if_flags & IFF_BROADCAST)
		rxcfg |= STE_RXMODE_BROADCAST;
	if ((ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) != 0) {
		if ((ifp->if_flags & IFF_ALLMULTI) != 0)
			rxcfg |= STE_RXMODE_ALLMULTI;
		if ((ifp->if_flags & IFF_PROMISC) != 0)
			rxcfg |= STE_RXMODE_PROMISC;
		goto chipit;
	}

	rxcfg |= STE_RXMODE_MULTIHASH;
	/* Now program new ones. */
	if_foreach_llmaddr(ifp, ste_hash_maddr, hashes);

chipit:
	CSR_WRITE_2(sc, STE_MAR0, hashes[0] & 0xFFFF);
	CSR_WRITE_2(sc, STE_MAR1, (hashes[0] >> 16) & 0xFFFF);
	CSR_WRITE_2(sc, STE_MAR2, hashes[1] & 0xFFFF);
	CSR_WRITE_2(sc, STE_MAR3, (hashes[1] >> 16) & 0xFFFF);
	CSR_WRITE_1(sc, STE_RX_MODE, rxcfg);
	CSR_READ_1(sc, STE_RX_MODE);
}