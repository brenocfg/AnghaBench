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
struct sge_wrq {int /*<<< orphan*/  wrq_tx_task; } ;
struct sge_eq {size_t tx_chan; int /*<<< orphan*/  equiq; } ;
struct adapter {int /*<<< orphan*/ * tq; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_readandclear_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
handle_wrq_egr_update(struct adapter *sc, struct sge_eq *eq)
{
	struct sge_wrq *wrq = (void *)eq;

	atomic_readandclear_int(&eq->equiq);
	taskqueue_enqueue(sc->tq[eq->tx_chan], &wrq->wrq_tx_task);
}