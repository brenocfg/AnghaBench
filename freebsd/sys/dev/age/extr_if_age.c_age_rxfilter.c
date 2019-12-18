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
struct ifnet {int if_flags; } ;
struct age_softc {struct ifnet* age_ifp; } ;
typedef  int /*<<< orphan*/  mchash ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_LOCK_ASSERT (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_MAC_CFG ; 
 int /*<<< orphan*/  AGE_MAR0 ; 
 int /*<<< orphan*/  AGE_MAR1 ; 
 int CSR_READ_4 (struct age_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct age_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int MAC_CFG_ALLMULTI ; 
 int MAC_CFG_BCAST ; 
 int MAC_CFG_PROMISC ; 
 int /*<<< orphan*/  age_hash_maddr ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
age_rxfilter(struct age_softc *sc)
{
	struct ifnet *ifp;
	uint32_t mchash[2];
	uint32_t rxcfg;

	AGE_LOCK_ASSERT(sc);

	ifp = sc->age_ifp;

	rxcfg = CSR_READ_4(sc, AGE_MAC_CFG);
	rxcfg &= ~(MAC_CFG_ALLMULTI | MAC_CFG_BCAST | MAC_CFG_PROMISC);
	if ((ifp->if_flags & IFF_BROADCAST) != 0)
		rxcfg |= MAC_CFG_BCAST;
	if ((ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI)) != 0) {
		if ((ifp->if_flags & IFF_PROMISC) != 0)
			rxcfg |= MAC_CFG_PROMISC;
		if ((ifp->if_flags & IFF_ALLMULTI) != 0)
			rxcfg |= MAC_CFG_ALLMULTI;
		CSR_WRITE_4(sc, AGE_MAR0, 0xFFFFFFFF);
		CSR_WRITE_4(sc, AGE_MAR1, 0xFFFFFFFF);
		CSR_WRITE_4(sc, AGE_MAC_CFG, rxcfg);
		return;
	}

	/* Program new filter. */
	bzero(mchash, sizeof(mchash));
	if_foreach_llmaddr(ifp, age_hash_maddr, mchash);

	CSR_WRITE_4(sc, AGE_MAR0, mchash[0]);
	CSR_WRITE_4(sc, AGE_MAR1, mchash[1]);
	CSR_WRITE_4(sc, AGE_MAC_CFG, rxcfg);
}