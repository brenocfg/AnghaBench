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
typedef  size_t uint32_t ;
typedef  scalar_t__ uint16_t ;
struct bge_tx_bd {int bge_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/ ** bge_tx_chain; int /*<<< orphan*/ * bge_tx_dmamap; int /*<<< orphan*/  bge_tx_mtag; int /*<<< orphan*/  bge_tx_ring_map; int /*<<< orphan*/  bge_tx_ring_tag; } ;
struct TYPE_3__ {struct bge_tx_bd* bge_tx_ring; } ;
struct bge_softc {scalar_t__ bge_tx_saved_considx; scalar_t__ bge_txcnt; scalar_t__ bge_timer; TYPE_2__ bge_cdata; TYPE_1__ bge_ldata; int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_INC (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BGE_LOCK_ASSERT (struct bge_softc*) ; 
 int BGE_TXBDFLAG_END ; 
 int /*<<< orphan*/  BGE_TX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_inc_counter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  if_setdrvflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bge_txeof(struct bge_softc *sc, uint16_t tx_cons)
{
	struct bge_tx_bd *cur_tx;
	if_t ifp;

	BGE_LOCK_ASSERT(sc);

	/* Nothing to do. */
	if (sc->bge_tx_saved_considx == tx_cons)
		return;

	ifp = sc->bge_ifp;

	bus_dmamap_sync(sc->bge_cdata.bge_tx_ring_tag,
	    sc->bge_cdata.bge_tx_ring_map, BUS_DMASYNC_POSTWRITE);
	/*
	 * Go through our tx ring and free mbufs for those
	 * frames that have been sent.
	 */
	while (sc->bge_tx_saved_considx != tx_cons) {
		uint32_t		idx;

		idx = sc->bge_tx_saved_considx;
		cur_tx = &sc->bge_ldata.bge_tx_ring[idx];
		if (cur_tx->bge_flags & BGE_TXBDFLAG_END)
			if_inc_counter(ifp, IFCOUNTER_OPACKETS, 1);
		if (sc->bge_cdata.bge_tx_chain[idx] != NULL) {
			bus_dmamap_sync(sc->bge_cdata.bge_tx_mtag,
			    sc->bge_cdata.bge_tx_dmamap[idx],
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(sc->bge_cdata.bge_tx_mtag,
			    sc->bge_cdata.bge_tx_dmamap[idx]);
			m_freem(sc->bge_cdata.bge_tx_chain[idx]);
			sc->bge_cdata.bge_tx_chain[idx] = NULL;
		}
		sc->bge_txcnt--;
		BGE_INC(sc->bge_tx_saved_considx, BGE_TX_RING_CNT);
	}

	if_setdrvflagbits(ifp, 0, IFF_DRV_OACTIVE);
	if (sc->bge_txcnt == 0)
		sc->bge_timer = 0;
}