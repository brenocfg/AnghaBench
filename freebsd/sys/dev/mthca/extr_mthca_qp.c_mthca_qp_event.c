#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int /*<<< orphan*/  qp_context; int /*<<< orphan*/  (* event_handler ) (struct ib_event*,int /*<<< orphan*/ ) ;} ;
struct mthca_qp {int /*<<< orphan*/  wait; int /*<<< orphan*/  refcount; TYPE_3__ ibqp; int /*<<< orphan*/  alt_port; int /*<<< orphan*/  port; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  qp; } ;
struct TYPE_5__ {int num_qps; } ;
struct mthca_dev {TYPE_4__ qp_table; int /*<<< orphan*/  ib_dev; TYPE_1__ limits; } ;
struct TYPE_6__ {TYPE_3__* qp; } ;
struct ib_event {int event; TYPE_2__ element; int /*<<< orphan*/ * device; } ;
typedef  enum ib_event_type { ____Placeholder_ib_event_type } ib_event_type ;

/* Variables and functions */
 int IB_EVENT_PATH_MIG ; 
 struct mthca_qp* mthca_array_get (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mthca_warn (struct mthca_dev*,char*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ib_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void mthca_qp_event(struct mthca_dev *dev, u32 qpn,
		    enum ib_event_type event_type)
{
	struct mthca_qp *qp;
	struct ib_event event;

	spin_lock(&dev->qp_table.lock);
	qp = mthca_array_get(&dev->qp_table.qp, qpn & (dev->limits.num_qps - 1));
	if (qp)
		++qp->refcount;
	spin_unlock(&dev->qp_table.lock);

	if (!qp) {
		mthca_warn(dev, "Async event %d for bogus QP %08x\n",
			   event_type, qpn);
		return;
	}

	if (event_type == IB_EVENT_PATH_MIG)
		qp->port = qp->alt_port;

	event.device      = &dev->ib_dev;
	event.event       = event_type;
	event.element.qp  = &qp->ibqp;
	if (qp->ibqp.event_handler)
		qp->ibqp.event_handler(&event, qp->ibqp.qp_context);

	spin_lock(&dev->qp_table.lock);
	if (!--qp->refcount)
		wake_up(&qp->wait);
	spin_unlock(&dev->qp_table.lock);
}