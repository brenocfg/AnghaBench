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
struct mlx5_wqe_data_seg {int dummy; } ;
struct mlx5_rwqe_sig {int dummy; } ;
struct TYPE_4__ {int wqe_cnt; int wqe_shift; int max_post; int max_gs; } ;
struct mlx5_qp {TYPE_2__ rq; scalar_t__ wq_sig; } ;
struct mlx5_context {scalar_t__ max_recv_wr; int max_rq_desc_sz; int /*<<< orphan*/ * dbg_fp; } ;
struct TYPE_3__ {scalar_t__ max_recv_wr; } ;
struct ibv_qp_init_attr_ex {TYPE_1__ cap; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX5_DBG_QP ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_BB ; 
 int max (int,int /*<<< orphan*/ ) ; 
 int mlx5_calc_rcv_wqe (struct mlx5_context*,struct ibv_qp_init_attr_ex*,struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_dbg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int mlx5_ilog2 (int) ; 
 int mlx5_round_up_power_of_two (scalar_t__) ; 

__attribute__((used)) static int mlx5_calc_rq_size(struct mlx5_context *ctx,
			     struct ibv_qp_init_attr_ex *attr,
			     struct mlx5_qp *qp)
{
	int wqe_size;
	int wq_size;
	int scat_spc;
	FILE *fp = ctx->dbg_fp;

	if (!attr->cap.max_recv_wr)
		return 0;

	if (attr->cap.max_recv_wr > ctx->max_recv_wr) {
		mlx5_dbg(fp, MLX5_DBG_QP, "\n");
		return -EINVAL;
	}

	wqe_size = mlx5_calc_rcv_wqe(ctx, attr, qp);
	if (wqe_size < 0 || wqe_size > ctx->max_rq_desc_sz) {
		mlx5_dbg(fp, MLX5_DBG_QP, "\n");
		return -EINVAL;
	}

	wq_size = mlx5_round_up_power_of_two(attr->cap.max_recv_wr) * wqe_size;
	if (wqe_size) {
		wq_size = max(wq_size, MLX5_SEND_WQE_BB);
		qp->rq.wqe_cnt = wq_size / wqe_size;
		qp->rq.wqe_shift = mlx5_ilog2(wqe_size);
		qp->rq.max_post = 1 << mlx5_ilog2(wq_size / wqe_size);
		scat_spc = wqe_size -
			(qp->wq_sig ? sizeof(struct mlx5_rwqe_sig) : 0);
		qp->rq.max_gs = scat_spc / sizeof(struct mlx5_wqe_data_seg);
	} else {
		qp->rq.wqe_cnt = 0;
		qp->rq.wqe_shift = 0;
		qp->rq.max_post = 0;
		qp->rq.max_gs = 0;
	}
	return wq_size;
}