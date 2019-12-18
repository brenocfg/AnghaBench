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
struct jme_softc {struct ifnet* jme_ifp; } ;
struct ifnet {int if_flags; } ;
typedef  int /*<<< orphan*/  mchash ;

/* Variables and functions */
 int CSR_READ_4 (struct jme_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct jme_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  JME_LOCK_ASSERT (struct jme_softc*) ; 
 int /*<<< orphan*/  JME_MAR0 ; 
 int /*<<< orphan*/  JME_MAR1 ; 
 int /*<<< orphan*/  JME_RXMAC ; 
 int RXMAC_ALLMULTI ; 
 int RXMAC_BROADCAST ; 
 int RXMAC_MULTICAST ; 
 int RXMAC_PROMISC ; 
 int RXMAC_UNICAST ; 
 int /*<<< orphan*/  bzero (int*,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int**) ; 
 int /*<<< orphan*/  jme_hash_maddr ; 

__attribute__((used)) static void
jme_set_filter(struct jme_softc *sc)
{
	struct ifnet *ifp;
	uint32_t mchash[2];
	uint32_t rxcfg;

	JME_LOCK_ASSERT(sc);

	ifp = sc->jme_ifp;

	rxcfg = CSR_READ_4(sc, JME_RXMAC);
	rxcfg &= ~ (RXMAC_BROADCAST | RXMAC_PROMISC | RXMAC_MULTICAST |
	    RXMAC_ALLMULTI);
	/* Always accept frames destined to our station address. */
	rxcfg |= RXMAC_UNICAST;
	if ((ifp->if_flags & IFF_BROADCAST) != 0)
		rxcfg |= RXMAC_BROADCAST;
	if ((ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI)) != 0) {
		if ((ifp->if_flags & IFF_PROMISC) != 0)
			rxcfg |= RXMAC_PROMISC;
		if ((ifp->if_flags & IFF_ALLMULTI) != 0)
			rxcfg |= RXMAC_ALLMULTI;
		CSR_WRITE_4(sc, JME_MAR0, 0xFFFFFFFF);
		CSR_WRITE_4(sc, JME_MAR1, 0xFFFFFFFF);
		CSR_WRITE_4(sc, JME_RXMAC, rxcfg);
		return;
	}

	/*
	 * Set up the multicast address filter by passing all multicast
	 * addresses through a CRC generator, and then using the low-order
	 * 6 bits as an index into the 64 bit multicast hash table.  The
	 * high order bits select the register, while the rest of the bits
	 * select the bit within the register.
	 */
	rxcfg |= RXMAC_MULTICAST;
	bzero(mchash, sizeof(mchash));
	if_foreach_llmaddr(ifp, jme_hash_maddr, &mchash);

	CSR_WRITE_4(sc, JME_MAR0, mchash[0]);
	CSR_WRITE_4(sc, JME_MAR1, mchash[1]);
	CSR_WRITE_4(sc, JME_RXMAC, rxcfg);
}