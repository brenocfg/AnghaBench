#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  txdesc ;
struct ti_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct ti_tx_desc {int ti_flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  ti_txbusyq; int /*<<< orphan*/  ti_txfreeq; int /*<<< orphan*/  ti_tx_tag; int /*<<< orphan*/  ti_tx_ring_map; int /*<<< orphan*/  ti_tx_ring_tag; } ;
struct TYPE_5__ {struct ti_tx_desc* ti_tx_ring; } ;
struct TYPE_4__ {int ti_idx; } ;
struct ti_softc {int ti_tx_saved_considx; scalar_t__ ti_hwrev; scalar_t__ ti_txcnt; scalar_t__ ti_timer; TYPE_3__ ti_cdata; TYPE_2__ ti_rdata; TYPE_1__ ti_tx_considx; struct ifnet* ti_ifp; } ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 struct ti_txdesc* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct ti_txdesc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TI_BDFLAG_END ; 
 scalar_t__ TI_HWREV_TIGON ; 
 int /*<<< orphan*/  TI_INC (int,int /*<<< orphan*/ ) ; 
 scalar_t__ TI_TX_RING_BASE ; 
 int /*<<< orphan*/  TI_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ti_mem_read (struct ti_softc*,scalar_t__,int,struct ti_tx_desc*) ; 
 int /*<<< orphan*/  tx_q ; 

__attribute__((used)) static void
ti_txeof(struct ti_softc *sc)
{
	struct ti_txdesc *txd;
	struct ti_tx_desc txdesc;
	struct ti_tx_desc *cur_tx = NULL;
	struct ifnet *ifp;
	int idx;

	ifp = sc->ti_ifp;

	txd = STAILQ_FIRST(&sc->ti_cdata.ti_txbusyq);
	if (txd == NULL)
		return;

	if (sc->ti_rdata.ti_tx_ring != NULL)
		bus_dmamap_sync(sc->ti_cdata.ti_tx_ring_tag,
		    sc->ti_cdata.ti_tx_ring_map, BUS_DMASYNC_POSTWRITE);
	/*
	 * Go through our tx ring and free mbufs for those
	 * frames that have been sent.
	 */
	for (idx = sc->ti_tx_saved_considx; idx != sc->ti_tx_considx.ti_idx;
	    TI_INC(idx, TI_TX_RING_CNT)) {
		if (sc->ti_hwrev == TI_HWREV_TIGON) {
			ti_mem_read(sc, TI_TX_RING_BASE + idx * sizeof(txdesc),
			    sizeof(txdesc), &txdesc);
			cur_tx = &txdesc;
		} else
			cur_tx = &sc->ti_rdata.ti_tx_ring[idx];
		sc->ti_txcnt--;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
		if ((cur_tx->ti_flags & TI_BDFLAG_END) == 0)
			continue;
		bus_dmamap_sync(sc->ti_cdata.ti_tx_tag, txd->tx_dmamap,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->ti_cdata.ti_tx_tag, txd->tx_dmamap);

		if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		m_freem(txd->tx_m);
		txd->tx_m = NULL;
		STAILQ_REMOVE_HEAD(&sc->ti_cdata.ti_txbusyq, tx_q);
		STAILQ_INSERT_TAIL(&sc->ti_cdata.ti_txfreeq, txd, tx_q);
		txd = STAILQ_FIRST(&sc->ti_cdata.ti_txbusyq);
	}
	sc->ti_tx_saved_considx = idx;
	if (sc->ti_txcnt == 0)
		sc->ti_timer = 0;
}