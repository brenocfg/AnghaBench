#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mthca_qp {int dummy; } ;
struct mthca_dev {int dummy; } ;
struct mthca_cq_buf {int dummy; } ;
struct TYPE_3__ {int cqe; } ;
struct mthca_cq {int cons_index; int /*<<< orphan*/  lock; TYPE_2__* resize_buf; TYPE_1__ ibcq; struct mthca_cq_buf buf; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {scalar_t__ state; int cqe; struct mthca_cq_buf buf; } ;

/* Variables and functions */
 scalar_t__ CQ_RESIZE_READY ; 
 scalar_t__ CQ_RESIZE_SWAPPED ; 
 int EAGAIN ; 
 scalar_t__ cqe_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cqe_from_buf (struct mthca_cq_buf*,int) ; 
 int /*<<< orphan*/  mthca_is_memfree (struct mthca_dev*) ; 
 int mthca_poll_one (struct mthca_dev*,struct mthca_cq*,struct mthca_qp**,int*,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mthca_cq* to_mcq (struct ib_cq*) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  update_cons_index (struct mthca_dev*,struct mthca_cq*,int) ; 
 int /*<<< orphan*/  wmb () ; 

int mthca_poll_cq(struct ib_cq *ibcq, int num_entries,
		  struct ib_wc *entry)
{
	struct mthca_dev *dev = to_mdev(ibcq->device);
	struct mthca_cq *cq = to_mcq(ibcq);
	struct mthca_qp *qp = NULL;
	unsigned long flags;
	int err = 0;
	int freed = 0;
	int npolled;

	spin_lock_irqsave(&cq->lock, flags);

	npolled = 0;
repoll:
	while (npolled < num_entries) {
		err = mthca_poll_one(dev, cq, &qp,
				     &freed, entry + npolled);
		if (err)
			break;
		++npolled;
	}

	if (freed) {
		wmb();
		update_cons_index(dev, cq, freed);
	}

	/*
	 * If a CQ resize is in progress and we discovered that the
	 * old buffer is empty, then peek in the new buffer, and if
	 * it's not empty, switch to the new buffer and continue
	 * polling there.
	 */
	if (unlikely(err == -EAGAIN && cq->resize_buf &&
		     cq->resize_buf->state == CQ_RESIZE_READY)) {
		/*
		 * In Tavor mode, the hardware keeps the producer
		 * index modulo the CQ size.  Since we might be making
		 * the CQ bigger, we need to mask our consumer index
		 * using the size of the old CQ buffer before looking
		 * in the new CQ buffer.
		 */
		if (!mthca_is_memfree(dev))
			cq->cons_index &= cq->ibcq.cqe;

		if (cqe_sw(get_cqe_from_buf(&cq->resize_buf->buf,
					    cq->cons_index & cq->resize_buf->cqe))) {
			struct mthca_cq_buf tbuf;
			int tcqe;

			tbuf         = cq->buf;
			tcqe         = cq->ibcq.cqe;
			cq->buf      = cq->resize_buf->buf;
			cq->ibcq.cqe = cq->resize_buf->cqe;

			cq->resize_buf->buf   = tbuf;
			cq->resize_buf->cqe   = tcqe;
			cq->resize_buf->state = CQ_RESIZE_SWAPPED;

			goto repoll;
		}
	}

	spin_unlock_irqrestore(&cq->lock, flags);

	return err == 0 || err == -EAGAIN ? npolled : err;
}