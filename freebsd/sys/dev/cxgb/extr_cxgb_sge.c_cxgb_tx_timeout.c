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
struct sge_txq {int in_use; int size; } ;
struct sge_qset {int coalescing; int /*<<< orphan*/  qs_flags; struct sge_txq* txq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QS_TIMEOUT ; 
 size_t TXQ_ETH ; 
 scalar_t__ TXQ_TRYLOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  TXQ_UNLOCK (struct sge_qset*) ; 
 int /*<<< orphan*/  cxgb_start_locked (struct sge_qset*) ; 

__attribute__((used)) static void
cxgb_tx_timeout(void *arg)
{
	struct sge_qset *qs = arg;
	struct sge_txq *txq = &qs->txq[TXQ_ETH];

	if (qs->coalescing == 0 && (txq->in_use >= (txq->size>>3)))
                qs->coalescing = 1;	
	if (TXQ_TRYLOCK(qs)) {
		qs->qs_flags |= QS_TIMEOUT;
		cxgb_start_locked(qs);
		qs->qs_flags &= ~QS_TIMEOUT;
		TXQ_UNLOCK(qs);
	}
}