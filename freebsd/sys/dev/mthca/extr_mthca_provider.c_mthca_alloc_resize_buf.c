#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mthca_dev {int dummy; } ;
struct mthca_cq {int /*<<< orphan*/  lock; TYPE_1__* resize_buf; } ;
struct TYPE_3__ {int cqe; int /*<<< orphan*/  state; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQ_RESIZE_ALLOC ; 
 int /*<<< orphan*/  CQ_RESIZE_READY ; 
 int EBUSY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int mthca_alloc_cq_buf (struct mthca_dev*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mthca_alloc_resize_buf(struct mthca_dev *dev, struct mthca_cq *cq,
				  int entries)
{
	int ret;

	spin_lock_irq(&cq->lock);
	if (cq->resize_buf) {
		ret = -EBUSY;
		goto unlock;
	}

	cq->resize_buf = kmalloc(sizeof *cq->resize_buf, GFP_ATOMIC);
	if (!cq->resize_buf) {
		ret = -ENOMEM;
		goto unlock;
	}

	cq->resize_buf->state = CQ_RESIZE_ALLOC;

	ret = 0;

unlock:
	spin_unlock_irq(&cq->lock);

	if (ret)
		return ret;

	ret = mthca_alloc_cq_buf(dev, &cq->resize_buf->buf, entries);
	if (ret) {
		spin_lock_irq(&cq->lock);
		kfree(cq->resize_buf);
		cq->resize_buf = NULL;
		spin_unlock_irq(&cq->lock);
		return ret;
	}

	cq->resize_buf->cqe = entries - 1;

	spin_lock_irq(&cq->lock);
	cq->resize_buf->state = CQ_RESIZE_READY;
	spin_unlock_irq(&cq->lock);

	return 0;
}