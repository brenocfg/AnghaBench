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
struct TYPE_2__ {int max; int wqe_shift; } ;
struct mthca_qp {int /*<<< orphan*/  wrid; int /*<<< orphan*/  mr; int /*<<< orphan*/  is_direct; int /*<<< orphan*/  queue; TYPE_1__ sq; scalar_t__ send_wqe_offset; } ;
struct mthca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_ALIGN (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mthca_buf_free (struct mthca_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mthca_free_wqe_buf(struct mthca_dev *dev,
			       struct mthca_qp *qp)
{
	mthca_buf_free(dev, PAGE_ALIGN(qp->send_wqe_offset +
				       (qp->sq.max << qp->sq.wqe_shift)),
		       &qp->queue, qp->is_direct, &qp->mr);
	kfree(qp->wrid);
}