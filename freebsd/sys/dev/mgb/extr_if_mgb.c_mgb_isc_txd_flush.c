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
typedef  scalar_t__ uint16_t ;
struct mgb_ring_data {scalar_t__ last_tail; } ;
struct mgb_softc {struct mgb_ring_data tx_ring_data; } ;
typedef  scalar_t__ qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MGB_DMA_TX_TAIL (scalar_t__) ; 

__attribute__((used)) static void
mgb_isc_txd_flush(void *xsc, uint16_t txqid, qidx_t pidx)
{
	struct mgb_softc *sc;
	struct mgb_ring_data *rdata;

	KASSERT(txqid == 0, ("tried to flush TX Channel %d.\n", txqid));
	sc = xsc;
	rdata = &sc->tx_ring_data;

	if (rdata->last_tail != pidx) {
		rdata->last_tail = pidx;
		CSR_WRITE_REG(sc, MGB_DMA_TX_TAIL(txqid), rdata->last_tail);
	}
}