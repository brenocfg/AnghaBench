#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ifnet {int /*<<< orphan*/  if_drv_flags; } ;
struct are_txdesc {int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct TYPE_4__ {int are_tx_cons; int are_tx_prod; int /*<<< orphan*/  are_tx_ring_map; int /*<<< orphan*/  are_tx_ring_tag; int /*<<< orphan*/  are_tx_tag; struct are_txdesc* are_txdesc; int /*<<< orphan*/  are_tx_cnt; } ;
struct TYPE_3__ {struct are_desc* are_tx_ring; } ;
struct are_softc {TYPE_2__ are_cdata; TYPE_1__ are_rdata; struct ifnet* are_ifp; } ;
struct are_desc {int are_stat; int are_devcs; scalar_t__ are_addr; } ;

/* Variables and functions */
 int ADSTAT_Tx_ES ; 
 scalar_t__ ARE_DMASIZE (int) ; 
 int /*<<< orphan*/  ARE_INC (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARE_LOCK_ASSERT (struct are_softc*) ; 
 int /*<<< orphan*/  ARE_TX_RING_CNT ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
are_tx(struct are_softc *sc)
{
	struct are_txdesc	*txd;
	struct are_desc		*cur_tx;
	struct ifnet		*ifp;
	uint32_t		ctl, devcs;
	int			cons, prod;

	ARE_LOCK_ASSERT(sc);

	cons = sc->are_cdata.are_tx_cons;
	prod = sc->are_cdata.are_tx_prod;
	if (cons == prod)
		return;

	bus_dmamap_sync(sc->are_cdata.are_tx_ring_tag,
	    sc->are_cdata.are_tx_ring_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	ifp = sc->are_ifp;
	/*
	 * Go through our tx list and free mbufs for those
	 * frames that have been transmitted.
	 */
	for (; cons != prod; ARE_INC(cons, ARE_TX_RING_CNT)) {
		cur_tx = &sc->are_rdata.are_tx_ring[cons];
		ctl = cur_tx->are_stat;
		devcs = cur_tx->are_devcs;
		/* Check if descriptor has "finished" flag */
		if (ARE_DMASIZE(devcs) == 0)
			break;

		sc->are_cdata.are_tx_cnt--;
		ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

		txd = &sc->are_cdata.are_txdesc[cons];

		if ((ctl & ADSTAT_Tx_ES) == 0)
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		else {
			if_inc_counter(ifp, IFCOUNTER_OERRORS, 1);
		}

		bus_dmamap_sync(sc->are_cdata.are_tx_tag, txd->tx_dmamap,
		    BUS_DMASYNC_POSTWRITE);
		bus_dmamap_unload(sc->are_cdata.are_tx_tag, txd->tx_dmamap);

		/* Free only if it's first descriptor in list */
		if (txd->tx_m)
			m_freem(txd->tx_m);
		txd->tx_m = NULL;

		/* reset descriptor */
		cur_tx->are_stat = 0;
		cur_tx->are_devcs = 0;
		cur_tx->are_addr = 0;
	}

	sc->are_cdata.are_tx_cons = cons;

	bus_dmamap_sync(sc->are_cdata.are_tx_ring_tag,
	    sc->are_cdata.are_tx_ring_map, BUS_DMASYNC_PREWRITE);
}