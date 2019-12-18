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
struct TYPE_6__ {int /*<<< orphan*/  c_cpu; } ;
struct sge_txq {scalar_t__ in_use; TYPE_3__ txq_watchdog; } ;
struct sge_qset {int coalescing; TYPE_2__* port; int /*<<< orphan*/  qs_flags; struct sge_txq* txq; } ;
struct TYPE_5__ {TYPE_1__* ifp; } ;
struct TYPE_4__ {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  QS_FLUSHING ; 
 size_t TXQ_ETH ; 
 scalar_t__ TXQ_RING_EMPTY (struct sge_qset*) ; 
 scalar_t__ TXQ_TRYLOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  callout_reset_on (TYPE_3__*,int,void (*) (void*),struct sge_qset*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxgb_start_locked (struct sge_qset*) ; 
 scalar_t__ cxgb_tx_coalesce_enable_start ; 
 scalar_t__ cxgb_tx_coalesce_enable_stop ; 
 int hz ; 

void
cxgb_tx_watchdog(void *arg)
{
	struct sge_qset *qs = arg;
	struct sge_txq *txq = &qs->txq[TXQ_ETH];

        if (qs->coalescing != 0 &&
	    (txq->in_use <= cxgb_tx_coalesce_enable_stop) &&
	    TXQ_RING_EMPTY(qs))
                qs->coalescing = 0; 
        else if (qs->coalescing == 0 &&
	    (txq->in_use >= cxgb_tx_coalesce_enable_start))
                qs->coalescing = 1;
	if (TXQ_TRYLOCK(qs)) {
		qs->qs_flags |= QS_FLUSHING;
		cxgb_start_locked(qs);
		qs->qs_flags &= ~QS_FLUSHING;
		TXQ_UNLOCK(qs);
	}
	if (qs->port->ifp->if_drv_flags & IFF_DRV_RUNNING)
		callout_reset_on(&txq->txq_watchdog, hz/4, cxgb_tx_watchdog,
		    qs, txq->txq_watchdog.c_cpu);
}