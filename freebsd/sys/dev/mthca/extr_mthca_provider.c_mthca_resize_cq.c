#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mthca_resize_cq {int /*<<< orphan*/  lkey; } ;
struct TYPE_6__ {int max_cqes; } ;
struct mthca_dev {TYPE_1__ limits; } ;
struct TYPE_7__ {int /*<<< orphan*/  lkey; } ;
struct TYPE_8__ {TYPE_2__ ibmr; } ;
struct mthca_cq_buf {TYPE_3__ mr; } ;
struct TYPE_9__ {int cqe; } ;
struct mthca_cq {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; TYPE_5__* resize_buf; TYPE_4__ ibcq; struct mthca_cq_buf buf; scalar_t__ is_kernel; int /*<<< orphan*/  cqn; } ;
struct ib_udata {int dummy; } ;
struct ib_cq {int cqe; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int cqe; scalar_t__ state; struct mthca_cq_buf buf; } ;

/* Variables and functions */
 scalar_t__ CQ_RESIZE_READY ; 
 int EFAULT ; 
 int EINVAL ; 
 scalar_t__ ib_copy_from_udata (struct mthca_resize_cq*,struct ib_udata*,int) ; 
 int /*<<< orphan*/  ilog2 (int) ; 
 int /*<<< orphan*/  kfree (TYPE_5__*) ; 
 int mthca_RESIZE_CQ (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mthca_alloc_resize_buf (struct mthca_dev*,struct mthca_cq*,int) ; 
 int /*<<< orphan*/  mthca_cq_resize_copy_cqes (struct mthca_cq*) ; 
 int /*<<< orphan*/  mthca_free_cq_buf (struct mthca_dev*,struct mthca_cq_buf*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 struct mthca_cq* to_mcq (struct ib_cq*) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_resize_cq(struct ib_cq *ibcq, int entries, struct ib_udata *udata)
{
	struct mthca_dev *dev = to_mdev(ibcq->device);
	struct mthca_cq *cq = to_mcq(ibcq);
	struct mthca_resize_cq ucmd;
	u32 lkey;
	int ret;

	if (entries < 1 || entries > dev->limits.max_cqes)
		return -EINVAL;

	mutex_lock(&cq->mutex);

	entries = roundup_pow_of_two(entries + 1);
	if (entries == ibcq->cqe + 1) {
		ret = 0;
		goto out;
	}

	if (cq->is_kernel) {
		ret = mthca_alloc_resize_buf(dev, cq, entries);
		if (ret)
			goto out;
		lkey = cq->resize_buf->buf.mr.ibmr.lkey;
	} else {
		if (ib_copy_from_udata(&ucmd, udata, sizeof ucmd)) {
			ret = -EFAULT;
			goto out;
		}
		lkey = ucmd.lkey;
	}

	ret = mthca_RESIZE_CQ(dev, cq->cqn, lkey, ilog2(entries));

	if (ret) {
		if (cq->resize_buf) {
			mthca_free_cq_buf(dev, &cq->resize_buf->buf,
					  cq->resize_buf->cqe);
			kfree(cq->resize_buf);
			spin_lock_irq(&cq->lock);
			cq->resize_buf = NULL;
			spin_unlock_irq(&cq->lock);
		}
		goto out;
	}

	if (cq->is_kernel) {
		struct mthca_cq_buf tbuf;
		int tcqe;

		spin_lock_irq(&cq->lock);
		if (cq->resize_buf->state == CQ_RESIZE_READY) {
			mthca_cq_resize_copy_cqes(cq);
			tbuf         = cq->buf;
			tcqe         = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;
		} else {
			tbuf = cq->resize_buf->buf;
			tcqe = cq->resize_buf->cqe;
		}

		kfree(cq->resize_buf);
		cq->resize_buf = NULL;
		spin_unlock_irq(&cq->lock);

		mthca_free_cq_buf(dev, &tbuf, tcqe);
	} else
		ibcq->cqe = entries - 1;

out:
	mutex_unlock(&cq->mutex);

	return ret;
}