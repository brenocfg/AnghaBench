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
struct ib_qp {int /*<<< orphan*/  usecnt; TYPE_1__* device; int /*<<< orphan*/  open_list; struct ib_qp* real_qp; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_handler_lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct ib_qp*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int ib_close_qp(struct ib_qp *qp)
{
	struct ib_qp *real_qp;
	unsigned long flags;

	real_qp = qp->real_qp;
	if (real_qp == qp)
		return -EINVAL;

	spin_lock_irqsave(&real_qp->device->event_handler_lock, flags);
	list_del(&qp->open_list);
	spin_unlock_irqrestore(&real_qp->device->event_handler_lock, flags);

	atomic_dec(&real_qp->usecnt);
	kfree(qp);

	return 0;
}