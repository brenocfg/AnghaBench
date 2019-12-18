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
typedef  int uint8_t ;
typedef  size_t uint16_t ;
struct tx_ring {size_t tx_rs_cidx; size_t tx_rs_pidx; size_t* tx_rsq; size_t tx_cidx_processed; TYPE_2__* tx_base; } ;
struct ix_tx_queue {struct tx_ring txr; } ;
struct adapter {struct ix_tx_queue* tx_queues; TYPE_3__* shared; } ;
typedef  size_t qidx_t ;
typedef  scalar_t__ int32_t ;
typedef  TYPE_3__* if_softc_ctx_t ;
struct TYPE_6__ {size_t* isc_ntxd; } ;
struct TYPE_4__ {int status; } ;
struct TYPE_5__ {TYPE_1__ wb; } ;

/* Variables and functions */
 int IXGBE_TXD_STAT_DD ; 
 int /*<<< orphan*/  MPASS (int) ; 

__attribute__((used)) static int
ixgbe_isc_txd_credits_update(void *arg, uint16_t txqid, bool clear)
{
	struct adapter     *sc = arg;
	if_softc_ctx_t     scctx = sc->shared;
	struct ix_tx_queue *que = &sc->tx_queues[txqid];
	struct tx_ring     *txr = &que->txr;
	qidx_t             processed = 0;
	int                updated;
	qidx_t             cur, prev, ntxd, rs_cidx;
	int32_t            delta;
	uint8_t            status;

	rs_cidx = txr->tx_rs_cidx;
	if (rs_cidx == txr->tx_rs_pidx)
		return (0);

	cur = txr->tx_rsq[rs_cidx];
	status = txr->tx_base[cur].wb.status;
	updated = !!(status & IXGBE_TXD_STAT_DD);

	if (!updated)
		return (0);

	/* If clear is false just let caller know that there
	 * are descriptors to reclaim */
	if (!clear)
		return (1);

	prev = txr->tx_cidx_processed;
	ntxd = scctx->isc_ntxd[0];
	do {
		MPASS(prev != cur);
		delta = (int32_t)cur - (int32_t)prev;
		if (delta < 0)
			delta += ntxd;
		MPASS(delta > 0);

		processed += delta;
		prev = cur;
		rs_cidx = (rs_cidx + 1) & (ntxd - 1);
		if (rs_cidx == txr->tx_rs_pidx)
			break;

		cur = txr->tx_rsq[rs_cidx];
		status = txr->tx_base[cur].wb.status;
	} while ((status & IXGBE_TXD_STAT_DD));

	txr->tx_rs_cidx = rs_cidx;
	txr->tx_cidx_processed = prev;

	return (processed);
}