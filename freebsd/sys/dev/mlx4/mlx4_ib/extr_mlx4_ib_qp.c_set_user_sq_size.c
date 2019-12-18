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
struct TYPE_8__ {int wqe_cnt; scalar_t__ wqe_shift; } ;
struct TYPE_7__ {int wqe_cnt; int wqe_shift; } ;
struct mlx4_ib_qp {int buf_size; TYPE_4__ sq; TYPE_3__ rq; } ;
struct mlx4_ib_dev {TYPE_2__* dev; } ;
struct mlx4_ib_create_qp {int log_sq_bb_count; scalar_t__ log_sq_stride; } ;
struct TYPE_5__ {int max_wqes; int /*<<< orphan*/  max_sq_desc_sz; } ;
struct TYPE_6__ {TYPE_1__ caps; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLX4_IB_MIN_SQ_STRIDE ; 
 scalar_t__ ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  roundup_pow_of_two (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_user_sq_size(struct mlx4_ib_dev *dev,
			    struct mlx4_ib_qp *qp,
			    struct mlx4_ib_create_qp *ucmd)
{
	/* Sanity check SQ size before proceeding */
	if ((1 << ucmd->log_sq_bb_count) > dev->dev->caps.max_wqes	 ||
	    ucmd->log_sq_stride >
		ilog2(roundup_pow_of_two(dev->dev->caps.max_sq_desc_sz)) ||
	    ucmd->log_sq_stride < MLX4_IB_MIN_SQ_STRIDE)
		return -EINVAL;

	qp->sq.wqe_cnt   = 1 << ucmd->log_sq_bb_count;
	qp->sq.wqe_shift = ucmd->log_sq_stride;

	qp->buf_size = (qp->rq.wqe_cnt << qp->rq.wqe_shift) +
		(qp->sq.wqe_cnt << qp->sq.wqe_shift);

	return 0;
}