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
struct TYPE_2__ {int /*<<< orphan*/  axq_q; } ;
struct ath_txq {int axq_qnum; TYPE_1__ fifo; int /*<<< orphan*/  axq_tidq; int /*<<< orphan*/  axq_q; struct ath_softc* axq_softc; int /*<<< orphan*/ * axq_link; scalar_t__ axq_intrcnt; scalar_t__ axq_aggr_depth; scalar_t__ axq_depth; scalar_t__ axq_ac; } ;
struct ath_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TXQ_LOCK_INIT (struct ath_softc*,struct ath_txq*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ath_txq_init(struct ath_softc *sc, struct ath_txq *txq, int qnum)
{
	txq->axq_qnum = qnum;
	txq->axq_ac = 0;
	txq->axq_depth = 0;
	txq->axq_aggr_depth = 0;
	txq->axq_intrcnt = 0;
	txq->axq_link = NULL;
	txq->axq_softc = sc;
	TAILQ_INIT(&txq->axq_q);
	TAILQ_INIT(&txq->axq_tidq);
	TAILQ_INIT(&txq->fifo.axq_q);
	ATH_TXQ_LOCK_INIT(sc, txq);
}