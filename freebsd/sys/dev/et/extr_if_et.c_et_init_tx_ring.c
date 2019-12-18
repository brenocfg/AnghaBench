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
typedef  int /*<<< orphan*/  uint32_t ;
struct et_txstatus_data {int /*<<< orphan*/  txsd_dmap; int /*<<< orphan*/  txsd_dtag; int /*<<< orphan*/  txsd_status; } ;
struct et_txdesc_ring {int /*<<< orphan*/  tr_dmap; int /*<<< orphan*/  tr_dtag; int /*<<< orphan*/  tr_desc; } ;
struct et_txbuf_data {scalar_t__ tbd_used; scalar_t__ tbd_start_wrap; scalar_t__ tbd_start_index; } ;
struct et_softc {struct et_txstatus_data sc_tx_status; struct et_txbuf_data sc_tx_data; struct et_txdesc_ring sc_tx_ring; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ET_TX_RING_SIZE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
et_init_tx_ring(struct et_softc *sc)
{
	struct et_txdesc_ring *tx_ring;
	struct et_txbuf_data *tbd;
	struct et_txstatus_data *txsd;

	tx_ring = &sc->sc_tx_ring;
	bzero(tx_ring->tr_desc, ET_TX_RING_SIZE);
	bus_dmamap_sync(tx_ring->tr_dtag, tx_ring->tr_dmap,
	    BUS_DMASYNC_PREWRITE);

	tbd = &sc->sc_tx_data;
	tbd->tbd_start_index = 0;
	tbd->tbd_start_wrap = 0;
	tbd->tbd_used = 0;

	txsd = &sc->sc_tx_status;
	bzero(txsd->txsd_status, sizeof(uint32_t));
	bus_dmamap_sync(txsd->txsd_dtag, txsd->txsd_dmap,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}