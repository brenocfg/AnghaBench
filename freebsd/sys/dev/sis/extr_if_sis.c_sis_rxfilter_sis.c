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
struct sis_softc {scalar_t__ sis_rev; struct ifnet* sis_ifp; } ;
struct sis_hash_maddr_ctx {int* hashes; struct sis_softc* sc; } ;
struct ifnet {int if_flags; } ;

/* Variables and functions */
 int CSR_READ_4 (struct sis_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR_WRITE_4 (struct sis_softc*,int /*<<< orphan*/ ,int) ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 scalar_t__ SIS_REV_635 ; 
 scalar_t__ SIS_REV_900B ; 
 int SIS_RXFILTCTL_ALLMULTI ; 
 int SIS_RXFILTCTL_ALLPHYS ; 
 int SIS_RXFILTCTL_BROAD ; 
 int SIS_RXFILTCTL_ENABLE ; 
 int /*<<< orphan*/  SIS_RXFILT_CTL ; 
 int /*<<< orphan*/  SIS_RXFILT_DATA ; 
 int if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct sis_hash_maddr_ctx*) ; 
 int /*<<< orphan*/  sis_hash_maddr ; 

__attribute__((used)) static void
sis_rxfilter_sis(struct sis_softc *sc)
{
	struct ifnet		*ifp;
	struct sis_hash_maddr_ctx ctx;
	uint32_t		filter, i, n;

	ifp = sc->sis_ifp;

	/* hash table size */
	if (sc->sis_rev >= SIS_REV_635 || sc->sis_rev == SIS_REV_900B)
		n = 16;
	else
		n = 8;

	filter = CSR_READ_4(sc, SIS_RXFILT_CTL);
	if (filter & SIS_RXFILTCTL_ENABLE) {
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, filter & ~SIS_RXFILTCTL_ENABLE);
		CSR_READ_4(sc, SIS_RXFILT_CTL);
	}
	filter &= ~(SIS_RXFILTCTL_ALLPHYS | SIS_RXFILTCTL_BROAD |
	    SIS_RXFILTCTL_ALLMULTI);
	if (ifp->if_flags & IFF_BROADCAST)
		filter |= SIS_RXFILTCTL_BROAD;

	if (ifp->if_flags & (IFF_ALLMULTI | IFF_PROMISC)) {
		filter |= SIS_RXFILTCTL_ALLMULTI;
		if (ifp->if_flags & IFF_PROMISC)
			filter |= SIS_RXFILTCTL_ALLPHYS;
		for (i = 0; i < n; i++)
			ctx.hashes[i] = ~0;
	} else {
		for (i = 0; i < n; i++)
			ctx.hashes[i] = 0;
		ctx.sc = sc;
		if (if_foreach_llmaddr(ifp, sis_hash_maddr, &ctx) > n) {
			filter |= SIS_RXFILTCTL_ALLMULTI;
			for (i = 0; i < n; i++)
				ctx.hashes[i] = ~0;
		}
	}

	for (i = 0; i < n; i++) {
		CSR_WRITE_4(sc, SIS_RXFILT_CTL, (4 + i) << 16);
		CSR_WRITE_4(sc, SIS_RXFILT_DATA, ctx.hashes[i]);
	}

	/* Turn the receive filter on */
	CSR_WRITE_4(sc, SIS_RXFILT_CTL, filter | SIS_RXFILTCTL_ENABLE);
	CSR_READ_4(sc, SIS_RXFILT_CTL);
}