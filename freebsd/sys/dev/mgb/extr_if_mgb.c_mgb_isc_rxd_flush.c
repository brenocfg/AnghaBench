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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  last_tail; } ;
struct mgb_softc {TYPE_1__ rx_ring_data; } ;
typedef  int /*<<< orphan*/  qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_WRITE_REG (struct mgb_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MGB_DMA_RX_TAIL (scalar_t__) ; 

__attribute__((used)) static void
mgb_isc_rxd_flush(void *xsc, uint16_t rxqid, uint8_t flid, qidx_t pidx)
{
	struct mgb_softc *sc;

	sc = xsc;

	KASSERT(rxqid == 0, ("tried to flush RX Channel %d.\n", rxqid));
	sc->rx_ring_data.last_tail = pidx;
	CSR_WRITE_REG(sc, MGB_DMA_RX_TAIL(rxqid), sc->rx_ring_data.last_tail);
	return;
}