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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx5_wqe_ctrl_seg {int fm_ce_se; int /*<<< orphan*/  signature; void* qpn_ds; void* opmod_idx_opcode; } ;
struct TYPE_10__ {scalar_t__ cur_post; TYPE_4__* w_list; scalar_t__ head; scalar_t__* wqe_head; int /*<<< orphan*/ * wrid; } ;
struct TYPE_6__ {int qpn; } ;
struct TYPE_7__ {TYPE_1__ mqp; } ;
struct TYPE_8__ {TYPE_2__ base; } ;
struct mlx5_ib_qp {int fm_cache; TYPE_5__ sq; int /*<<< orphan*/  wq_sig; TYPE_3__ trans_qp; } ;
struct TYPE_9__ {int opcode; scalar_t__ next; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_BB ; 
 void* cpu_to_be32 (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wq_sig (struct mlx5_wqe_ctrl_seg*) ; 

__attribute__((used)) static void finish_wqe(struct mlx5_ib_qp *qp,
		       struct mlx5_wqe_ctrl_seg *ctrl,
		       u8 size, unsigned idx, u64 wr_id,
		       int nreq, u8 fence, u8 next_fence,
		       u32 mlx5_opcode)
{
	u8 opmod = 0;

	ctrl->opmod_idx_opcode = cpu_to_be32(((u32)(qp->sq.cur_post) << 8) |
					     mlx5_opcode | ((u32)opmod << 24));
	ctrl->qpn_ds = cpu_to_be32(size | (qp->trans_qp.base.mqp.qpn << 8));
	ctrl->fm_ce_se |= fence;
	qp->fm_cache = next_fence;
	if (unlikely(qp->wq_sig))
		ctrl->signature = wq_sig(ctrl);

	qp->sq.wrid[idx] = wr_id;
	qp->sq.w_list[idx].opcode = mlx5_opcode;
	qp->sq.wqe_head[idx] = qp->sq.head + nreq;
	qp->sq.cur_post += DIV_ROUND_UP(size * 16, MLX5_SEND_WQE_BB);
	qp->sq.w_list[idx].next = qp->sq.cur_post;
}