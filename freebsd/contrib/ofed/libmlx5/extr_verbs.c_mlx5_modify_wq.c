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
struct mlx5_rwq {scalar_t__* db; TYPE_1__ rsc; } ;
struct mlx5_modify_wq {int /*<<< orphan*/  ibv_cmd; } ;
struct ibv_wq_attr {int attr_mask; scalar_t__ wq_state; scalar_t__ curr_wq_state; } ;
struct ibv_wq {scalar_t__ state; int /*<<< orphan*/  cq; } ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IBV_WQS_RDY ; 
 scalar_t__ IBV_WQS_RESET ; 
 int IBV_WQ_ATTR_CURR_STATE ; 
 int IBV_WQ_ATTR_STATE ; 
 size_t MLX5_RCV_DBR ; 
 size_t MLX5_SND_DBR ; 
 int /*<<< orphan*/  __mlx5_cq_clean (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ibv_cmd_modify_wq (struct ibv_wq*,struct ibv_wq_attr*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mlx5_init_rwq_indices (struct mlx5_rwq*) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_mcq (int /*<<< orphan*/ ) ; 
 struct mlx5_rwq* to_mrwq (struct ibv_wq*) ; 

int mlx5_modify_wq(struct ibv_wq *wq, struct ibv_wq_attr *attr)
{
	struct mlx5_modify_wq	cmd = {};
	struct mlx5_rwq *rwq = to_mrwq(wq);

	if ((attr->attr_mask & IBV_WQ_ATTR_STATE) &&
	    attr->wq_state == IBV_WQS_RDY) {
		if ((attr->attr_mask & IBV_WQ_ATTR_CURR_STATE) &&
		    attr->curr_wq_state != wq->state)
			return -EINVAL;

		if (wq->state == IBV_WQS_RESET) {
			mlx5_spin_lock(&to_mcq(wq->cq)->lock);
			__mlx5_cq_clean(to_mcq(wq->cq),
					rwq->rsc.rsn, NULL);
			mlx5_spin_unlock(&to_mcq(wq->cq)->lock);
			mlx5_init_rwq_indices(rwq);
			rwq->db[MLX5_RCV_DBR] = 0;
			rwq->db[MLX5_SND_DBR] = 0;
		}
	}

	return ibv_cmd_modify_wq(wq, attr, &cmd.ibv_cmd,  sizeof(cmd.ibv_cmd), sizeof(cmd));
}