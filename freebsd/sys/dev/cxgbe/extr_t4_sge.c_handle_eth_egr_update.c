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
struct sge_txq {int /*<<< orphan*/  tx_reclaim_task; int /*<<< orphan*/  r; } ;
struct sge_eq {int flags; size_t tx_chan; int /*<<< orphan*/  equiq; } ;
struct adapter {int /*<<< orphan*/ * tq; } ;

/* Variables and functions */
 int EQ_ETH ; 
 int EQ_TYPEMASK ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  atomic_readandclear_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_ring_check_drainage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_eth_egr_update(struct adapter *sc, struct sge_eq *eq)
{
	struct sge_txq *txq = (void *)eq;

	MPASS((eq->flags & EQ_TYPEMASK) == EQ_ETH);

	atomic_readandclear_int(&eq->equiq);
	mp_ring_check_drainage(txq->r, 0);
	taskqueue_enqueue(sc->tq[eq->tx_chan], &txq->tx_reclaim_task);
}