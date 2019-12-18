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
struct netfront_txq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_TX_LOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  XN_TX_UNLOCK (struct netfront_txq*) ; 
 int /*<<< orphan*/  xn_txq_start (struct netfront_txq*) ; 

__attribute__((used)) static void
xn_txq_tq_deferred(void *xtxq, int pending)
{
	struct netfront_txq *txq = xtxq;

	XN_TX_LOCK(txq);
	xn_txq_start(txq);
	XN_TX_UNLOCK(txq);
}