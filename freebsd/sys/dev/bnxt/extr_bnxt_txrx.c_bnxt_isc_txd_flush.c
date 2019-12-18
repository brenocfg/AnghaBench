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
typedef  size_t uint16_t ;
struct bnxt_softc {struct bnxt_ring* tx_rings; } ;
struct bnxt_ring {int dummy; } ;
typedef  int /*<<< orphan*/  qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  BNXT_TX_DB (struct bnxt_ring*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bnxt_isc_txd_flush(void *sc, uint16_t txqid, qidx_t pidx)
{
	struct bnxt_softc *softc = (struct bnxt_softc *)sc;
	struct bnxt_ring *tx_ring = &softc->tx_rings[txqid];

	/* pidx is what we last set ipi_new_pidx to */
	BNXT_TX_DB(tx_ring, pidx);
	/* TODO: Cumulus+ doesn't need the double doorbell */
	BNXT_TX_DB(tx_ring, pidx);
	return;
}