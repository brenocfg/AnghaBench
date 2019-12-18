#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rsn; } ;
struct TYPE_5__ {scalar_t__ wqe_cnt; } ;
struct TYPE_4__ {scalar_t__ wqe_cnt; } ;
struct mlx5_qp {int /*<<< orphan*/  db; TYPE_3__ rsc; TYPE_2__ rq; TYPE_1__ sq; scalar_t__ rss_qp; } ;
struct mlx5_context {int /*<<< orphan*/  qp_table_mutex; int /*<<< orphan*/  cqe_version; } ;
struct ibv_qp {scalar_t__ recv_cq; scalar_t__ send_cq; int /*<<< orphan*/  qp_type; int /*<<< orphan*/  qp_num; scalar_t__ srq; int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlx5_cq_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mlx5_qp*) ; 
 int ibv_cmd_destroy_qp (struct ibv_qp*) ; 
 int /*<<< orphan*/  is_xrc_tgt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_clear_qp (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_clear_uidx (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_db (struct mlx5_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_qp_buf (struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_lock_cqs (struct ibv_qp*) ; 
 int /*<<< orphan*/  mlx5_unlock_cqs (struct ibv_qp*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mcq (scalar_t__) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx5_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/ * to_msrq (scalar_t__) ; 

int mlx5_destroy_qp(struct ibv_qp *ibqp)
{
	struct mlx5_qp *qp = to_mqp(ibqp);
	struct mlx5_context *ctx = to_mctx(ibqp->context);
	int ret;

	if (qp->rss_qp) {
		ret = ibv_cmd_destroy_qp(ibqp);
		if (ret)
			return ret;
		goto free;
	}

	if (!ctx->cqe_version)
		pthread_mutex_lock(&ctx->qp_table_mutex);

	ret = ibv_cmd_destroy_qp(ibqp);
	if (ret) {
		if (!ctx->cqe_version)
			pthread_mutex_unlock(&ctx->qp_table_mutex);
		return ret;
	}

	mlx5_lock_cqs(ibqp);

	__mlx5_cq_clean(to_mcq(ibqp->recv_cq), qp->rsc.rsn,
			ibqp->srq ? to_msrq(ibqp->srq) : NULL);
	if (ibqp->send_cq != ibqp->recv_cq)
		__mlx5_cq_clean(to_mcq(ibqp->send_cq), qp->rsc.rsn, NULL);

	if (!ctx->cqe_version) {
		if (qp->sq.wqe_cnt || qp->rq.wqe_cnt)
			mlx5_clear_qp(ctx, ibqp->qp_num);
	}

	mlx5_unlock_cqs(ibqp);
	if (!ctx->cqe_version)
		pthread_mutex_unlock(&ctx->qp_table_mutex);
	else if (!is_xrc_tgt(ibqp->qp_type))
		mlx5_clear_uidx(ctx, qp->rsc.rsn);

	mlx5_free_db(ctx, qp->db);
	mlx5_free_qp_buf(qp);
free:
	free(qp);

	return 0;
}