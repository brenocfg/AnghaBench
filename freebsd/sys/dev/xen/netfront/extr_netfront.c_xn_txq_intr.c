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
struct netfront_txq {int /*<<< orphan*/  ring; } ;

/* Variables and functions */
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XN_TX_LOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  xn_txeof (struct netfront_txq*) ; 
 int /*<<< orphan*/  xn_txq_start (struct netfront_txq*) ; 

__attribute__((used)) static void
xn_txq_intr(struct netfront_txq *txq)
{

	XN_TX_LOCK(txq);
	if (RING_HAS_UNCONSUMED_RESPONSES(&txq->ring))
		xn_txeof(txq);
	xn_txq_start(txq);
	XN_TX_UNLOCK(txq);
}