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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int /*<<< orphan*/  bge_status_map; int /*<<< orphan*/  bge_status_tag; } ;
struct TYPE_7__ {TYPE_2__* bge_status_block; } ;
struct bge_softc {scalar_t__ bge_asicrev; scalar_t__ bge_chipid; scalar_t__ bge_link_evt; TYPE_4__ bge_cdata; TYPE_3__ bge_ldata; int /*<<< orphan*/  bge_ifp; } ;
typedef  int /*<<< orphan*/  if_t ;
struct TYPE_6__ {scalar_t__ bge_status; TYPE_1__* bge_idx; } ;
struct TYPE_5__ {int /*<<< orphan*/  bge_tx_cons_idx; int /*<<< orphan*/  bge_rx_prod_idx; } ;

/* Variables and functions */
 scalar_t__ BGE_ASICREV_BCM5700 ; 
 scalar_t__ BGE_CHIPID_BCM5700_B2 ; 
 int /*<<< orphan*/  BGE_LOCK (struct bge_softc*) ; 
 int BGE_MACSTAT_LINK_CHANGED ; 
 int /*<<< orphan*/  BGE_MAC_STS ; 
 int /*<<< orphan*/  BGE_MBX_IRQ0_LO ; 
 int /*<<< orphan*/  BGE_UNLOCK (struct bge_softc*) ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int CSR_READ_4 (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int IFCAP_POLLING ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  bge_link_upd (struct bge_softc*) ; 
 int /*<<< orphan*/  bge_rxeof (struct bge_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bge_start_locked (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_txeof (struct bge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_sendq_empty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_intr(void *xsc)
{
	struct bge_softc *sc;
	if_t ifp;
	uint32_t statusword;
	uint16_t rx_prod, tx_cons;

	sc = xsc;

	BGE_LOCK(sc);

	ifp = sc->bge_ifp;

#ifdef DEVICE_POLLING
	if (if_getcapenable(ifp) & IFCAP_POLLING) {
		BGE_UNLOCK(sc);
		return;
	}
#endif

	/*
	 * Ack the interrupt by writing something to BGE_MBX_IRQ0_LO.  Don't
	 * disable interrupts by writing nonzero like we used to, since with
	 * our current organization this just gives complications and
	 * pessimizations for re-enabling interrupts.  We used to have races
	 * instead of the necessary complications.  Disabling interrupts
	 * would just reduce the chance of a status update while we are
	 * running (by switching to the interrupt-mode coalescence
	 * parameters), but this chance is already very low so it is more
	 * efficient to get another interrupt than prevent it.
	 *
	 * We do the ack first to ensure another interrupt if there is a
	 * status update after the ack.  We don't check for the status
	 * changing later because it is more efficient to get another
	 * interrupt than prevent it, not quite as above (not checking is
	 * a smaller optimization than not toggling the interrupt enable,
	 * since checking doesn't involve PCI accesses and toggling require
	 * the status check).  So toggling would probably be a pessimization
	 * even with MSI.  It would only be needed for using a task queue.
	 */
	bge_writembx(sc, BGE_MBX_IRQ0_LO, 0);

	/*
	 * Do the mandatory PCI flush as well as get the link status.
	 */
	statusword = CSR_READ_4(sc, BGE_MAC_STS) & BGE_MACSTAT_LINK_CHANGED;

	/* Make sure the descriptor ring indexes are coherent. */
	bus_dmamap_sync(sc->bge_cdata.bge_status_tag,
	    sc->bge_cdata.bge_status_map,
	    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	rx_prod = sc->bge_ldata.bge_status_block->bge_idx[0].bge_rx_prod_idx;
	tx_cons = sc->bge_ldata.bge_status_block->bge_idx[0].bge_tx_cons_idx;
	sc->bge_ldata.bge_status_block->bge_status = 0;
	bus_dmamap_sync(sc->bge_cdata.bge_status_tag,
	    sc->bge_cdata.bge_status_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	if ((sc->bge_asicrev == BGE_ASICREV_BCM5700 &&
	    sc->bge_chipid != BGE_CHIPID_BCM5700_B2) ||
	    statusword || sc->bge_link_evt)
		bge_link_upd(sc);

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
		/* Check RX return ring producer/consumer. */
		bge_rxeof(sc, rx_prod, 1);
	}

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING) {
		/* Check TX ring producer/consumer. */
		bge_txeof(sc, tx_cons);
	}

	if (if_getdrvflags(ifp) & IFF_DRV_RUNNING &&
	    !if_sendq_empty(ifp))
		bge_start_locked(ifp);

	BGE_UNLOCK(sc);
}