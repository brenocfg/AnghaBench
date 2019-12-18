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
struct ccp_queue {scalar_t__ cq_tail; scalar_t__ cq_acq_tail; int /*<<< orphan*/  cq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  ccp_queue_write_tail (struct ccp_queue*) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

void
ccp_queue_release(struct ccp_queue *qp)
{

	mtx_assert(&qp->cq_lock, MA_OWNED);
	if (qp->cq_tail != qp->cq_acq_tail) {
		wmb();
		ccp_queue_write_tail(qp);
	}
	mtx_unlock(&qp->cq_lock);
}