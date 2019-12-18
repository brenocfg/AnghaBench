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
struct mbuf {int dummy; } ;
struct ifnet {int if_drv_flags; int /*<<< orphan*/  if_snd; } ;
struct ffec_softc {int txcount; int /*<<< orphan*/  tx_watchdog_count; int /*<<< orphan*/  txdesc_map; int /*<<< orphan*/  txdesc_tag; int /*<<< orphan*/  tx_idx_head; struct ifnet* ifp; int /*<<< orphan*/  link_is_up; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (struct ifnet*,struct mbuf*) ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  FEC_TDAR_REG ; 
 int /*<<< orphan*/  FEC_TDAR_TDAR ; 
 int /*<<< orphan*/  FFEC_ASSERT_LOCKED (struct ffec_softc*) ; 
 int IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFQ_DRV_DEQUEUE (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  IFQ_DRV_PREPEND (int /*<<< orphan*/ *,struct mbuf*) ; 
 int TX_DESC_COUNT ; 
 int /*<<< orphan*/  WATCHDOG_TIMEOUT_SECS ; 
 int /*<<< orphan*/  WR4 (struct ffec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ffec_setup_txbuf (struct ffec_softc*,int /*<<< orphan*/ ,struct mbuf**) ; 
 int /*<<< orphan*/  next_txidx (struct ffec_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ffec_txstart_locked(struct ffec_softc *sc)
{
	struct ifnet *ifp;
	struct mbuf *m;
	int enqueued;

	FFEC_ASSERT_LOCKED(sc);

	if (!sc->link_is_up)
		return;

	ifp = sc->ifp;

	if (ifp->if_drv_flags & IFF_DRV_OACTIVE)
		return;

	enqueued = 0;

	for (;;) {
		if (sc->txcount == (TX_DESC_COUNT-1)) {
			ifp->if_drv_flags |= IFF_DRV_OACTIVE;
			break;
		}
		IFQ_DRV_DEQUEUE(&ifp->if_snd, m);
		if (m == NULL)
			break;
		if (ffec_setup_txbuf(sc, sc->tx_idx_head, &m) != 0) {
			IFQ_DRV_PREPEND(&ifp->if_snd, m);
			break;
		}
		BPF_MTAP(ifp, m);
		sc->tx_idx_head = next_txidx(sc, sc->tx_idx_head);
		++enqueued;
	}

	if (enqueued != 0) {
		bus_dmamap_sync(sc->txdesc_tag, sc->txdesc_map, BUS_DMASYNC_PREWRITE);
		WR4(sc, FEC_TDAR_REG, FEC_TDAR_TDAR);
		bus_dmamap_sync(sc->txdesc_tag, sc->txdesc_map, BUS_DMASYNC_POSTWRITE);
		sc->tx_watchdog_count = WATCHDOG_TIMEOUT_SECS;
	}
}