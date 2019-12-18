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
struct ifnet {int if_drv_flags; } ;
struct ffec_softc {int tx_idx_tail; int tx_idx_head; struct ffec_hwdesc* rxdesc_ring; int /*<<< orphan*/  txbuf_tag; struct ffec_bufmap* txbuf_map; struct ffec_hwdesc* txdesc_ring; int /*<<< orphan*/  ffec_callout; scalar_t__ tx_watchdog_count; struct ifnet* ifp; } ;
struct ffec_hwdesc {scalar_t__ buf_paddr; } ;
struct ffec_bufmap {int /*<<< orphan*/ * mbuf; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int FEC_ECR_ETHEREN ; 
 int /*<<< orphan*/  FEC_ECR_REG ; 
 int /*<<< orphan*/  FEC_IEM_REG ; 
 int /*<<< orphan*/  FEC_IER_REG ; 
 int /*<<< orphan*/  FFEC_ASSERT_LOCKED (struct ffec_softc*) ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int RD4 (struct ffec_softc*,int /*<<< orphan*/ ) ; 
 int RX_DESC_COUNT ; 
 int /*<<< orphan*/  WR4 (struct ffec_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ffec_setup_rxdesc (struct ffec_softc*,int,scalar_t__) ; 
 int /*<<< orphan*/  ffec_setup_txdesc (struct ffec_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int next_txidx (struct ffec_softc*,int) ; 

__attribute__((used)) static void
ffec_stop_locked(struct ffec_softc *sc)
{
	struct ifnet *ifp;
	struct ffec_hwdesc *desc;
	struct ffec_bufmap *bmap;
	int idx;

	FFEC_ASSERT_LOCKED(sc);

	ifp = sc->ifp;
	ifp->if_drv_flags &= ~(IFF_DRV_RUNNING | IFF_DRV_OACTIVE);
	sc->tx_watchdog_count = 0;

	/* 
	 * Stop the hardware, mask all interrupts, and clear all current
	 * interrupt status bits.
	 */
	WR4(sc, FEC_ECR_REG, RD4(sc, FEC_ECR_REG) & ~FEC_ECR_ETHEREN);
	WR4(sc, FEC_IEM_REG, 0x00000000);
	WR4(sc, FEC_IER_REG, 0xffffffff);

	/*
	 * Stop the media-check callout.  Do not use callout_drain() because
	 * we're holding a mutex the callout acquires, and if it's currently
	 * waiting to acquire it, we'd deadlock.  If it is waiting now, the
	 * ffec_tick() routine will return without doing anything when it sees
	 * that IFF_DRV_RUNNING is not set, so avoiding callout_drain() is safe.
	 */
	callout_stop(&sc->ffec_callout);

	/*
	 * Discard all untransmitted buffers.  Each buffer is simply freed;
	 * it's as if the bits were transmitted and then lost on the wire.
	 *
	 * XXX Is this right?  Or should we use IFQ_DRV_PREPEND() to put them
	 * back on the queue for when we get restarted later?
	 */
	idx = sc->tx_idx_tail;
	while (idx != sc->tx_idx_head) {
		desc = &sc->txdesc_ring[idx];
		bmap = &sc->txbuf_map[idx];
		if (desc->buf_paddr != 0) {
			bus_dmamap_unload(sc->txbuf_tag, bmap->map);
			m_freem(bmap->mbuf);
			bmap->mbuf = NULL;
			ffec_setup_txdesc(sc, idx, 0, 0);
		}
		idx = next_txidx(sc, idx);
	}

	/*
	 * Discard all unprocessed receive buffers.  This amounts to just
	 * pretending that nothing ever got received into them.  We reuse the
	 * mbuf already mapped for each desc, simply turning the EMPTY flags
	 * back on so they'll get reused when we start up again.
	 */
	for (idx = 0; idx < RX_DESC_COUNT; ++idx) {
		desc = &sc->rxdesc_ring[idx];
		ffec_setup_rxdesc(sc, idx, desc->buf_paddr);
	}
}