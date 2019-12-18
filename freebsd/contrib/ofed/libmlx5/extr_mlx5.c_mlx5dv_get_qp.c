#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  size; int /*<<< orphan*/  reg; } ;
struct TYPE_13__ {int stride; int /*<<< orphan*/  wqe_cnt; void* buf; } ;
struct TYPE_10__ {int stride; int /*<<< orphan*/  wqe_cnt; void* buf; } ;
struct mlx5dv_qp {TYPE_8__ bf; TYPE_5__ rq; TYPE_2__ sq; int /*<<< orphan*/  dbrec; scalar_t__ comp_mask; } ;
struct TYPE_14__ {int wqe_shift; int /*<<< orphan*/  wqe_cnt; scalar_t__ offset; } ;
struct TYPE_12__ {scalar_t__ buf; } ;
struct TYPE_11__ {int wqe_shift; int /*<<< orphan*/  wqe_cnt; scalar_t__ offset; } ;
struct TYPE_9__ {scalar_t__ buf; } ;
struct mlx5_qp {TYPE_7__* bf; TYPE_6__ rq; TYPE_4__ buf; TYPE_3__ sq; TYPE_1__ sq_buf; scalar_t__ sq_buf_size; int /*<<< orphan*/  db; } ;
struct ibv_qp {int dummy; } ;
struct TYPE_15__ {scalar_t__ uuarn; int /*<<< orphan*/  buf_size; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 struct mlx5_qp* to_mqp (struct ibv_qp*) ; 

__attribute__((used)) static int mlx5dv_get_qp(struct ibv_qp *qp_in,
			 struct mlx5dv_qp *qp_out)
{
	struct mlx5_qp *mqp = to_mqp(qp_in);

	qp_out->comp_mask = 0;
	qp_out->dbrec     = mqp->db;

	if (mqp->sq_buf_size)
		/* IBV_QPT_RAW_PACKET */
		qp_out->sq.buf = (void *)((uintptr_t)mqp->sq_buf.buf);
	else
		qp_out->sq.buf = (void *)((uintptr_t)mqp->buf.buf + mqp->sq.offset);
	qp_out->sq.wqe_cnt = mqp->sq.wqe_cnt;
	qp_out->sq.stride  = 1 << mqp->sq.wqe_shift;

	qp_out->rq.buf     = (void *)((uintptr_t)mqp->buf.buf + mqp->rq.offset);
	qp_out->rq.wqe_cnt = mqp->rq.wqe_cnt;
	qp_out->rq.stride  = 1 << mqp->rq.wqe_shift;

	qp_out->bf.reg    = mqp->bf->reg;

	if (mqp->bf->uuarn > 0)
		qp_out->bf.size = mqp->bf->buf_size;
	else
		qp_out->bf.size = 0;

	return 0;
}