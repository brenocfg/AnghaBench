#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  bge_status_map; int /*<<< orphan*/  bge_status_tag; } ;
struct TYPE_7__ {TYPE_2__* bge_status_block; } ;
struct bge_softc {int bge_flags; scalar_t__ bge_rx_saved_considx; TYPE_4__ bge_cdata; TYPE_3__ bge_ldata; int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_6__ {int bge_status; int bge_status_tag; TYPE_1__* bge_idx; } ;
struct TYPE_5__ {scalar_t__ bge_rx_prod_idx; scalar_t__ bge_tx_cons_idx; } ;

/* Variables and functions */
 int BGE_FLAG_TAGGED_STATUS ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int /*<<< orphan*/  BGE_MBX_IRQ0_LO ; 
 int BGE_STATFLAG_LINKSTATE_CHANGED ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bge_link_upd (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_rxeof (struct bge_softc*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_start_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_txeof (struct bge_softc*,scalar_t__) ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_intr_task(void *arg, int pending)
{
	struct bge_softc *sc;
	if_t ifp;
	uint32_t status, status_tag;
	uint16_t rx_prod, tx_cons;

	sc = (struct bge_softc *)arg;
	ifp = sc->bge_ifp;

	BGE_LOCK(sc);
	if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) == 0) {
		BGE_UNLOCK(sc);
		return;
	}

	/* Get updated status block. */
	bus_dmamap_sync(sc->bge_cdata.bge_status_tag,
	    sc->bge_cdata.bge_status_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);

	/* Save producer/consumer indices. */
	rx_prod = sc->bge_ldata.bge_status_block->bge_idx[0].bge_rx_prod_idx;
	tx_cons = sc->bge_ldata.bge_status_block->bge_idx[0].bge_tx_cons_idx;
	status = sc->bge_ldata.bge_status_block->bge_status;
	status_tag = sc->bge_ldata.bge_status_block->bge_status_tag << 24;
	/* Dirty the status flag. */
	sc->bge_ldata.bge_status_block->bge_status = 0;
	bus_dmamap_sync(sc->bge_cdata.bge_status_tag,
	    sc->bge_cdata.bge_status_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	if ((sc->bge_flags & BGE_FLAG_TAGGED_STATUS) == 0)
		status_tag = 0;

	if ((status & BGE_STATFLAG_LINKSTATE_CHANGED) != 0)
		bge_link_upd(sc);

	/* Let controller work. */
	bge_writembx(sc, BGE_MBX_IRQ0_LO, status_tag);

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING &&
	    sc->bge_rx_saved_considx != rx_prod) {
		/* Check RX return ring producer/consumer. */
		BGE_UNLOCK(sc);
		bge_rxeof(sc, rx_prod, 0);
		BGE_LOCK(sc);
	}
	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
		/* Check TX ring producer/consumer. */
		bge_txeof(sc, tx_cons);
		if (!if_sendq_empty(ifp))
			bge_start_locked(ifp);
	}
	BGE_UNLOCK(sc);
}