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
struct TYPE_2__ {int /*<<< orphan*/  flushed; } ;
struct c4iw_qp {int /*<<< orphan*/  lock; TYPE_1__ wq; } ;
struct c4iw_dev {int max_qp; int /*<<< orphan*/  lock; struct c4iw_qp** qpid2ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  c4iw_flush_qp (struct c4iw_qp*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ t4_wq_in_error (TYPE_1__*) ; 

void c4iw_flush_qps(struct c4iw_dev *dev)
{
	int i;

	pthread_spin_lock(&dev->lock);
	for (i=0; i < dev->max_qp; i++) {
		struct c4iw_qp *qhp = dev->qpid2ptr[i];
		if (qhp) {
			if (!qhp->wq.flushed && t4_wq_in_error(&qhp->wq)) {
				pthread_spin_lock(&qhp->lock);
				c4iw_flush_qp(qhp);
				pthread_spin_unlock(&qhp->lock);
			}
		}
	}
	pthread_spin_unlock(&dev->lock);
}