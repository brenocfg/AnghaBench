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
struct mthca_srq {int first_free; int max_gs; int counter; int /*<<< orphan*/  lock; int /*<<< orphan*/ * db; int /*<<< orphan*/ * wrid; int /*<<< orphan*/  srqn; } ;
struct mthca_next_seg {scalar_t__ ee_nds; } ;
struct mthca_dev {int dummy; } ;
struct mthca_data_seg {int dummy; } ;
struct ib_srq {int /*<<< orphan*/  device; } ;
struct ib_recv_wr {int num_sge; int /*<<< orphan*/  wr_id; scalar_t__ sg_list; struct ib_recv_wr* next; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 void* get_wqe (struct mthca_srq*,int) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  mthca_err (struct mthca_dev*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_set_data_seg (void*,scalar_t__) ; 
 int /*<<< orphan*/  mthca_set_data_seg_inval (void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct mthca_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mthca_srq* to_msrq (struct ib_srq*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 
 int* wqe_to_link (void*) ; 

int mthca_arbel_post_srq_recv(struct ib_srq *ibsrq, struct ib_recv_wr *wr,
			      struct ib_recv_wr **bad_wr)
{
	struct mthca_dev *dev = to_mdev(ibsrq->device);
	struct mthca_srq *srq = to_msrq(ibsrq);
	unsigned long flags;
	int err = 0;
	int ind;
	int next_ind;
	int nreq;
	int i;
	void *wqe;

	spin_lock_irqsave(&srq->lock, flags);

	for (nreq = 0; wr; ++nreq, wr = wr->next) {
		ind       = srq->first_free;
		wqe       = get_wqe(srq, ind);
		next_ind  = *wqe_to_link(wqe);

		if (unlikely(next_ind < 0)) {
			mthca_err(dev, "SRQ %06x full\n", srq->srqn);
			err = -ENOMEM;
			*bad_wr = wr;
			break;
		}

		((struct mthca_next_seg *) wqe)->ee_nds = 0;
		/* flags field will always remain 0 */

		wqe += sizeof (struct mthca_next_seg);

		if (unlikely(wr->num_sge > srq->max_gs)) {
			err = -EINVAL;
			*bad_wr = wr;
			break;
		}

		for (i = 0; i < wr->num_sge; ++i) {
			mthca_set_data_seg(wqe, wr->sg_list + i);
			wqe += sizeof (struct mthca_data_seg);
		}

		if (i < srq->max_gs)
			mthca_set_data_seg_inval(wqe);

		srq->wrid[ind]  = wr->wr_id;
		srq->first_free = next_ind;
	}

	if (likely(nreq)) {
		srq->counter += nreq;

		/*
		 * Make sure that descriptors are written before
		 * we write doorbell record.
		 */
		wmb();
		*srq->db = cpu_to_be32(srq->counter);
	}

	spin_unlock_irqrestore(&srq->lock, flags);
	return err;
}