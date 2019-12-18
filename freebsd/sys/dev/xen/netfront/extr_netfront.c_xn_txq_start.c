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
struct netfront_txq {int /*<<< orphan*/  br; struct netfront_info* info; } ;
struct netfront_info {struct ifnet* xn_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XN_TX_LOCK_ASSERT (struct netfront_txq*) ; 
 int /*<<< orphan*/  drbr_empty (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xn_txq_mq_start_locked (struct netfront_txq*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
xn_txq_start(struct netfront_txq *txq)
{
	struct netfront_info *np = txq->info;
	struct ifnet *ifp = np->xn_ifp;

	XN_TX_LOCK_ASSERT(txq);
	if (!drbr_empty(ifp, txq->br))
		xn_txq_mq_start_locked(txq, NULL);
}