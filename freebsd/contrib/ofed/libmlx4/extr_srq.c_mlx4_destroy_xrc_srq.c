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
struct TYPE_2__ {int /*<<< orphan*/  srq_num; int /*<<< orphan*/  cq; } ;
struct mlx4_srq {struct mlx4_srq* wrid; int /*<<< orphan*/  buf; int /*<<< orphan*/  db; TYPE_1__ verbs_srq; } ;
struct mlx4_cq {int /*<<< orphan*/  lock; } ;
struct mlx4_context {int /*<<< orphan*/  xsrq_table; } ;
struct ibv_srq {int /*<<< orphan*/  context; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_DB_TYPE_RQ ; 
 int /*<<< orphan*/  free (struct mlx4_srq*) ; 
 int ibv_cmd_destroy_srq (struct ibv_srq*) ; 
 int /*<<< orphan*/  mlx4_clear_xsrq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_cq_clean (struct mlx4_cq*,int /*<<< orphan*/ ,struct mlx4_srq*) ; 
 int /*<<< orphan*/  mlx4_free_buf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_free_db (struct mlx4_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_store_xsrq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct mlx4_srq*) ; 
 int /*<<< orphan*/  pthread_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_spin_unlock (int /*<<< orphan*/ *) ; 
 struct mlx4_cq* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx4_context* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx4_srq* to_msrq (struct ibv_srq*) ; 

int mlx4_destroy_xrc_srq(struct ibv_srq *srq)
{
	struct mlx4_context *mctx = to_mctx(srq->context);
	struct mlx4_srq *msrq = to_msrq(srq);
	struct mlx4_cq *mcq;
	int ret;

	mcq = to_mcq(msrq->verbs_srq.cq);
	mlx4_cq_clean(mcq, 0, msrq);
	pthread_spin_lock(&mcq->lock);
	mlx4_clear_xsrq(&mctx->xsrq_table, msrq->verbs_srq.srq_num);
	pthread_spin_unlock(&mcq->lock);

	ret = ibv_cmd_destroy_srq(srq);
	if (ret) {
		pthread_spin_lock(&mcq->lock);
		mlx4_store_xsrq(&mctx->xsrq_table, msrq->verbs_srq.srq_num, msrq);
		pthread_spin_unlock(&mcq->lock);
		return ret;
	}

	mlx4_free_db(mctx, MLX4_DB_TYPE_RQ, msrq->db);
	mlx4_free_buf(&msrq->buf);
	free(msrq->wrid);
	free(msrq);

	return 0;
}