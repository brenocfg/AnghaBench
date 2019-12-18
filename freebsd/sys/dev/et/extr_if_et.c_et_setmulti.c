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
struct et_softc {struct ifnet* ifp; } ;

/* Variables and functions */
 int CSR_READ_4 (struct et_softc*,scalar_t__) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct et_softc*,scalar_t__,int) ; 
 int /*<<< orphan*/  ET_LOCK_ASSERT (struct et_softc*) ; 
 scalar_t__ ET_MULTI_HASH ; 
 scalar_t__ ET_PKTFILT ; 
 int ET_PKTFILT_BCAST ; 
 int ET_PKTFILT_MCAST ; 
 int ET_PKTFILT_UCAST ; 
 scalar_t__ ET_RXMAC_CTRL ; 
 int ET_RXMAC_CTRL_NO_PKTFILT ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  et_hash_maddr ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,int**) ; 

__attribute__((used)) static void
et_setmulti(struct et_softc *sc)
{
	struct ifnet *ifp;
	uint32_t hash[4] = { 0, 0, 0, 0 };
	uint32_t rxmac_ctrl, pktfilt;
	int i, count;

	ET_LOCK_ASSERT(sc);
	ifp = sc->ifp;

	pktfilt = CSR_READ_4(sc, ET_PKTFILT);
	rxmac_ctrl = CSR_READ_4(sc, ET_RXMAC_CTRL);

	pktfilt &= ~(ET_PKTFILT_BCAST | ET_PKTFILT_MCAST | ET_PKTFILT_UCAST);
	if (ifp->if_flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		rxmac_ctrl |= ET_RXMAC_CTRL_NO_PKTFILT;
		goto back;
	}

	count = if_foreach_llmaddr(ifp, et_hash_maddr, &hash);

	for (i = 0; i < 4; ++i)
		CSR_WRITE_4(sc, ET_MULTI_HASH + (i * 4), hash[i]);

	if (count > 0)
		pktfilt |= ET_PKTFILT_MCAST;
	rxmac_ctrl &= ~ET_RXMAC_CTRL_NO_PKTFILT;
back:
	CSR_WRITE_4(sc, ET_PKTFILT, pktfilt);
	CSR_WRITE_4(sc, ET_RXMAC_CTRL, rxmac_ctrl);
}