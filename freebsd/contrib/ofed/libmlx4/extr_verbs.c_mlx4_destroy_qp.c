#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct mlx4_qp* wrid; scalar_t__ wqe_cnt; } ;
struct TYPE_6__ {struct mlx4_qp* wrid; scalar_t__ wqe_cnt; } ;
struct mlx4_qp {int /*<<< orphan*/  buf; TYPE_2__ sq; TYPE_1__ rq; int /*<<< orphan*/  db; } ;
struct ibv_qp {scalar_t__ recv_cq; scalar_t__ send_cq; int /*<<< orphan*/  context; int /*<<< orphan*/  qp_num; scalar_t__ srq; } ;
struct TYPE_8__ {int /*<<< orphan*/  qp_table_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DB_TYPE_RQ ; 
 int /*<<< orphan*/  __mlx4_cq_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mlx4_qp*) ; 
 int ibv_cmd_destroy_qp (struct ibv_qp*) ; 
 int /*<<< orphan*/  mlx4_clear_qp (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_db (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_lock_cqs (struct ibv_qp*) ; 
 int /*<<< orphan*/  mlx4_unlock_cqs (struct ibv_qp*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mcq (scalar_t__) ; 
 TYPE_3__* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx4_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/ * to_msrq (scalar_t__) ; 

int mlx4_destroy_qp(struct ibv_qp *ibqp)
{
	struct mlx4_qp *qp = to_mqp(ibqp);
	int ret;

	pthread_mutex_lock(&to_mctx(ibqp->context)->qp_table_mutex);
	ret = ibv_cmd_destroy_qp(ibqp);
	if (ret) {
		pthread_mutex_unlock(&to_mctx(ibqp->context)->qp_table_mutex);
		return ret;
	}

	mlx4_lock_cqs(ibqp);

	if (ibqp->recv_cq)
		__mlx4_cq_clean(to_mcq(ibqp->recv_cq), ibqp->qp_num,
				ibqp->srq ? to_msrq(ibqp->srq) : NULL);
	if (ibqp->send_cq && ibqp->send_cq != ibqp->recv_cq)
		__mlx4_cq_clean(to_mcq(ibqp->send_cq), ibqp->qp_num, NULL);

	if (qp->sq.wqe_cnt || qp->rq.wqe_cnt)
		mlx4_clear_qp(to_mctx(ibqp->context), ibqp->qp_num);

	mlx4_unlock_cqs(ibqp);
	pthread_mutex_unlock(&to_mctx(ibqp->context)->qp_table_mutex);

	if (qp->rq.wqe_cnt) {
		mlx4_free_db(to_mctx(ibqp->context), MLX4_DB_TYPE_RQ, qp->db);
		free(qp->rq.wrid);
	}
	if (qp->sq.wqe_cnt)
		free(qp->sq.wrid);
	mlx4_free_buf(&qp->buf);
	free(qp);

	return 0;
}