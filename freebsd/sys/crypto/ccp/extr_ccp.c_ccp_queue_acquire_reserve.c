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
struct ccp_queue {int /*<<< orphan*/  cq_lock; int /*<<< orphan*/  cq_tail; int /*<<< orphan*/  cq_acq_tail; } ;

/* Variables and functions */
 int ccp_queue_reserve_space (struct ccp_queue*,unsigned int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

int
ccp_queue_acquire_reserve(struct ccp_queue *qp, unsigned n, int mflags)
{
	int error;

	mtx_lock(&qp->cq_lock);
	qp->cq_acq_tail = qp->cq_tail;
	error = ccp_queue_reserve_space(qp, n, mflags);
	if (error != 0)
		mtx_unlock(&qp->cq_lock);
	return (error);
}