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
struct TYPE_4__ {int cqe; int /*<<< orphan*/  device; } ;
struct mthca_cq {int cons_index; TYPE_2__ ibcq; TYPE_1__* resize_buf; } ;
struct TYPE_3__ {int cqe; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTHCA_CQ_ENTRY_SIZE ; 
 scalar_t__ cqe_sw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_cqe (struct mthca_cq*,int) ; 
 int /*<<< orphan*/  get_cqe_from_buf (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_is_memfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 

void mthca_cq_resize_copy_cqes(struct mthca_cq *cq)
{
	int i;

	/*
	 * In Tavor mode, the hardware keeps the consumer and producer
	 * indices mod the CQ size.  Since we might be making the CQ
	 * bigger, we need to deal with the case where the producer
	 * index wrapped around before the CQ was resized.
	 */
	if (!mthca_is_memfree(to_mdev(cq->ibcq.device)) &&
	    cq->ibcq.cqe < cq->resize_buf->cqe) {
		cq->cons_index &= cq->ibcq.cqe;
		if (cqe_sw(get_cqe(cq, cq->ibcq.cqe)))
			cq->cons_index -= cq->ibcq.cqe + 1;
	}

	for (i = cq->cons_index; cqe_sw(get_cqe(cq, i & cq->ibcq.cqe)); ++i)
		memcpy(get_cqe_from_buf(&cq->resize_buf->buf,
					i & cq->resize_buf->cqe),
		       get_cqe(cq, i & cq->ibcq.cqe), MTHCA_CQ_ENTRY_SIZE);
}