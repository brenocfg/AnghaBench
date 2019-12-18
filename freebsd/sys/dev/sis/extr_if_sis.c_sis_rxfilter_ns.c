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
struct sis_softc {struct ifnet* sis_ifp; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int NS_FILTADDR_FMEM_LO ; 
 int NS_RXFILTCTL_ARP ; 
 int NS_RXFILTCTL_MCHASH ; 
 int NS_RXFILTCTL_PERFECT ; 
 int SIS_RXFILTCTL_ALLMULTI ; 
 int SIS_RXFILTCTL_ALLPHYS ; 
 int SIS_RXFILTCTL_BROAD ; 
 int SIS_RXFILTCTL_ENABLE ; 
 int /*<<< orphan*/  SIS_RXFILT_CTL ; 
 int /*<<< orphan*/  SIS_RXFILT_DATA ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct sis_softc*) ; 
 int /*<<< orphan*/  sis_write_maddr ; 

__attribute__((used)) static void
sis_rxfilter_ns(struct sis_softc *sc)
{
	struct ifnet		*ifp;
	uint32_t		i, filter;

	ifp = sc->sis_ifp;
	filter = CSR_READ_4(sc, SIS_RXFILT_CTL);
	if (filter & SIS_RXFILTCTL_ENABLE) {
		/*
		 * Filter should be disabled to program other bits.
		 */
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, filter & ~SIS_RXFILTCTL_ENABLE);
		CSR_READ_4(sc, SIS_RXFILT_CTL);
	}
	filter &= ~(NS_RXFILTCTL_ARP | NS_RXFILTCTL_PERFECT |
	    NS_RXFILTCTL_MCHASH | SIS_RXFILTCTL_ALLPHYS | SIS_RXFILTCTL_BROAD |
	    SIS_RXFILTCTL_ALLMULTI);

	if (ifp->if_flags & IFF_BROADCAST)
		filter |= SIS_RXFILTCTL_BROAD;
	/*
	 * For the NatSemi chip, we have to explicitly enable the
	 * reception of ARP frames, as well as turn on the 'perfect
	 * match' filter where we store the station address, otherwise
	 * we won't receive unicasts meant for this host.
	 */
	filter |= NS_RXFILTCTL_ARP | NS_RXFILTCTL_PERFECT;

	if (ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) {
		filter |= SIS_RXFILTCTL_ALLMULTI;
		if (ifp->if_flags & IFF_PROMISC)
			filter |= SIS_RXFILTCTL_ALLPHYS;
	} else {
		/*
		 * We have to explicitly enable the multicast hash table
		 * on the NatSemi chip if we want to use it, which we do.
		 */
		filter |= NS_RXFILTCTL_MCHASH;

		/* first, zot all the existing hash bits */
		for (i = 0; i < 32; i++) {
			CSR_WRITE_4(sc, SIS_RXFILT_CTL, NS_FILTADDR_FMEM_LO +
			    (i * 2));
			CSR_WRITE_4(sc, SIS_RXFILT_DATA, 0);
		}

		if_foreach_llmaddr(ifp, sis_write_maddr, sc);
	}

	/* Turn the receive filter on */
	CSR_WRITE_4(sc, SIS_RXFILT_CTL, filter | SIS_RXFILTCTL_ENABLE);
	CSR_READ_4(sc, SIS_RXFILT_CTL);
}