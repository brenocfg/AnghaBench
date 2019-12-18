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
struct TYPE_2__ {int /*<<< orphan*/  tx_desc_map; int /*<<< orphan*/  tx_desc_tag; } ;
struct nfe_softc {scalar_t__ nfe_link; int rxtxctl; int nfe_watchdog_timer; TYPE_1__ txq; } ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NFE_LOCK_ASSERT (struct nfe_softc*) ; 
 int /*<<< orphan*/  NFE_RXTX_CTL ; 
 int NFE_RXTX_KICKTX ; 
 int /*<<< orphan*/  NFE_WRITE (struct nfe_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct mbuf* if_dequeue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_etherbpfmtap (int /*<<< orphan*/ ,struct mbuf*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 struct nfe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_prepend (int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ nfe_encap (struct nfe_softc*,struct mbuf**) ; 

__attribute__((used)) static void
nfe_start_locked(if_t ifp)
{
	struct nfe_softc *sc = if_getsoftc(ifp);
	struct mbuf *m0;
	int enq = 0;

	NFE_LOCK_ASSERT(sc);

	if ((if_getdrvflags(ifp) & (IFF_DRV_RUNNING | IFF_DRV_OACTIVE)) !=
	    IFF_DRV_RUNNING || sc->nfe_link == 0)
		return;

	while (!if_sendq_empty(ifp)) {
		m0 = if_dequeue(ifp);

		if (m0 == NULL)
			break;

		if (nfe_encap(sc, &m0) != 0) {
			if (m0 == NULL)
				break;
			if_sendq_prepend(ifp, m0);
			if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, 0);
			break;
		}
		enq++;
		if_etherbpfmtap(ifp, m0);
	}

	if (enq > 0) {
		bus_dmamap_sync(sc->txq.tx_desc_tag, sc->txq.tx_desc_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

		/* kick Tx */
		NFE_WRITE(sc, NFE_RXTX_CTL, NFE_RXTX_KICKTX | sc->rxtxctl);

		/*
		 * Set a timeout in case the chip goes out to lunch.
		 */
		sc->nfe_watchdog_timer = 5;
	}
}