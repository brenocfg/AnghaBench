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
struct hn_tx_ring {int /*<<< orphan*/  hn_txeof_task; int /*<<< orphan*/  hn_tx_taskq; scalar_t__ hn_oactive; int /*<<< orphan*/  hn_tx_task; int /*<<< orphan*/  hn_tx_lock; int /*<<< orphan*/  hn_direct_tx_size; scalar_t__ hn_sched_tx; } ;

/* Variables and functions */
 int hn_xmit (struct hn_tx_ring*,int /*<<< orphan*/ ) ; 
 scalar_t__ mtx_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
hn_xmit_txeof(struct hn_tx_ring *txr)
{

	if (txr->hn_sched_tx)
		goto do_sched;

	if (mtx_trylock(&txr->hn_tx_lock)) {
		int sched;

		txr->hn_oactive = 0;
		sched = hn_xmit(txr, txr->hn_direct_tx_size);
		mtx_unlock(&txr->hn_tx_lock);
		if (sched) {
			taskqueue_enqueue(txr->hn_tx_taskq,
			    &txr->hn_tx_task);
		}
	} else {
do_sched:
		/*
		 * Release the oactive earlier, with the hope, that
		 * others could catch up.  The task will clear the
		 * oactive again with the hn_tx_lock to avoid possible
		 * races.
		 */
		txr->hn_oactive = 0;
		taskqueue_enqueue(txr->hn_tx_taskq, &txr->hn_txeof_task);
	}
}