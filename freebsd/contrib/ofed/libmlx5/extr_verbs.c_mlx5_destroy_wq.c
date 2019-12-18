#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  rsn; } ;
struct mlx5_rwq {int /*<<< orphan*/  db; TYPE_1__ rsc; } ;
struct ibv_wq {int /*<<< orphan*/  context; int /*<<< orphan*/  cq; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mlx5_cq_clean (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct mlx5_rwq*) ; 
 int ibv_cmd_destroy_wq (struct ibv_wq*) ; 
 int /*<<< orphan*/  mlx5_clear_uidx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_free_rwq_buf (struct mlx5_rwq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_mcq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx5_rwq* to_mrwq (struct ibv_wq*) ; 

int mlx5_destroy_wq(struct ibv_wq *wq)
{
	struct mlx5_rwq *rwq = to_mrwq(wq);
	int ret;

	ret = ibv_cmd_destroy_wq(wq);
	if (ret)
		return ret;

	mlx5_spin_lock(&to_mcq(wq->cq)->lock);
	__mlx5_cq_clean(to_mcq(wq->cq), rwq->rsc.rsn, NULL);
	mlx5_spin_unlock(&to_mcq(wq->cq)->lock);
	mlx5_clear_uidx(to_mctx(wq->context), rwq->rsc.rsn);
	mlx5_free_db(to_mctx(wq->context), rwq->db);
	mlx5_free_rwq_buf(rwq, wq->context);
	free(rwq);

	return 0;
}