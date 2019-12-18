#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct mbuf {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_map; int /*<<< orphan*/  desc_tag; } ;
struct awg_softc {TYPE_1__ tx; int /*<<< orphan*/  ifp; int /*<<< orphan*/  link; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWG_ASSERT_LOCKED (struct awg_softc*) ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  EMAC_TX_CTL_1 ; 
 int ENOBUFS ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RD4 (struct awg_softc*,int /*<<< orphan*/ ) ; 
 int TX_DMA_START ; 
 int /*<<< orphan*/  WR4 (struct awg_softc*,int /*<<< orphan*/ ,int) ; 
 int awg_encap (struct awg_softc*,struct mbuf**) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_bpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 struct mbuf* if_dequeue (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_prepend (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
awg_start_locked(struct awg_softc *sc)
{
	struct mbuf *m;
	uint32_t val;
	if_t ifp;
	int cnt, err;

	AWG_ASSERT_LOCKED(sc);

	if (!sc->link)
		return;

	ifp = sc->ifp;

	if ((if_getdrvflags(ifp) & (IFF_DRV_RUNNING|IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING)
		return;

	for (cnt = 0; ; cnt++) {
		m = if_dequeue(ifp);
		if (m == NULL)
			break;

		err = awg_encap(sc, &m);
		if (err != 0) {
			if (err == ENOBUFS)
				if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
			if (m != NULL)
				if_sendq_prepend(ifp, m);
			break;
		}
		if_bpfmtap(ifp, m);
	}

	if (cnt != 0) {
		bus_dmamap_sync(sc->tx.desc_tag, sc->tx.desc_map,
		    BUS_DMASYNC_PREREAD|BUS_DMASYNC_PREWRITE);

		/* Start and run TX DMA */
		val = RD4(sc, EMAC_TX_CTL_1);
		WR4(sc, EMAC_TX_CTL_1, val | TX_DMA_START);
	}
}