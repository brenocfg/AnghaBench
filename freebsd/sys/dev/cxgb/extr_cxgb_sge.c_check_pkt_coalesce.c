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
typedef  int uint8_t ;
typedef  int uint64_t ;
struct sge_txq {scalar_t__ in_use; } ;
struct sge_qset {size_t idx; scalar_t__ coalescing; TYPE_1__* port; struct sge_txq* txq; } ;
struct adapter {int* tunq_fill; int tunq_coalesce; } ;
struct TYPE_2__ {struct adapter* adapter; } ;

/* Variables and functions */
 scalar_t__ COALESCE_START_MAX ; 
 scalar_t__ COALESCE_STOP_MIN ; 
 size_t TXQ_ETH ; 
 scalar_t__ TXQ_RING_EMPTY (struct sge_qset*) ; 
 scalar_t__ __predict_false (int /*<<< orphan*/ ) ; 
 scalar_t__ cxgb_tx_coalesce_enable_start ; 
 scalar_t__ cxgb_tx_coalesce_enable_stop ; 
 int /*<<< orphan*/  cxgb_tx_coalesce_force ; 

__attribute__((used)) static __inline uint64_t
check_pkt_coalesce(struct sge_qset *qs) 
{ 
        struct adapter *sc; 
        struct sge_txq *txq; 
	uint8_t *fill;

	if (__predict_false(cxgb_tx_coalesce_force))
		return (1);
	txq = &qs->txq[TXQ_ETH]; 
        sc = qs->port->adapter; 
	fill = &sc->tunq_fill[qs->idx];

	if (cxgb_tx_coalesce_enable_start > COALESCE_START_MAX)
		cxgb_tx_coalesce_enable_start = COALESCE_START_MAX;
	if (cxgb_tx_coalesce_enable_stop < COALESCE_STOP_MIN)
		cxgb_tx_coalesce_enable_start = COALESCE_STOP_MIN;
	/*
	 * if the hardware transmit queue is more than 1/8 full
	 * we mark it as coalescing - we drop back from coalescing
	 * when we go below 1/32 full and there are no packets enqueued, 
	 * this provides us with some degree of hysteresis
	 */
        if (*fill != 0 && (txq->in_use <= cxgb_tx_coalesce_enable_stop) &&
	    TXQ_RING_EMPTY(qs) && (qs->coalescing == 0))
                *fill = 0; 
        else if (*fill == 0 && (txq->in_use >= cxgb_tx_coalesce_enable_start))
                *fill = 1; 

	return (sc->tunq_coalesce);
}