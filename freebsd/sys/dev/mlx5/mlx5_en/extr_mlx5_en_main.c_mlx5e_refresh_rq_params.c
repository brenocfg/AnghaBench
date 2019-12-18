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
typedef  int /*<<< orphan*/  uint8_t ;
struct net_dim_cq_moder {int /*<<< orphan*/  pkts; int /*<<< orphan*/  usec; } ;
struct TYPE_5__ {int /*<<< orphan*/  mcq; } ;
struct TYPE_4__ {int /*<<< orphan*/  profile_ix; scalar_t__ state; int /*<<< orphan*/  mode; int /*<<< orphan*/  work; } ;
struct mlx5e_rq {TYPE_2__ cq; int /*<<< orphan*/  mtx; TYPE_1__ dim; } ;
struct TYPE_6__ {int rx_cq_moderation_mode; int /*<<< orphan*/  rx_cq_moderation_pkts; int /*<<< orphan*/  rx_cq_moderation_usec; } ;
struct mlx5e_priv {TYPE_3__ params; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_DIM_DEFAULT_PROFILE ; 
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  NET_DIM_CQ_PERIOD_MODE_DISABLED ; 
 int /*<<< orphan*/  NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cq_period_mode_modify ; 
 int mlx5_core_modify_cq_moderation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_modify_cq_moderation_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5e_get_default_profile (struct mlx5e_priv*,int /*<<< orphan*/ ,struct net_dim_cq_moder*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mlx5e_refresh_rq_params(struct mlx5e_priv *priv, struct mlx5e_rq *rq)
{

	if (MLX5_CAP_GEN(priv->mdev, cq_period_mode_modify)) {
		uint8_t cq_mode;
		uint8_t dim_mode;
		int retval;

		switch (priv->params.rx_cq_moderation_mode) {
		case 0:
		case 2:
			cq_mode = MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
			dim_mode = NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE;
			break;
		default:
			cq_mode = MLX5_CQ_PERIOD_MODE_START_FROM_CQE;
			dim_mode = NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE;
			break;
		}

		/* tear down dynamic interrupt moderation */
		mtx_lock(&rq->mtx);
		rq->dim.mode = NET_DIM_CQ_PERIOD_MODE_DISABLED;
		mtx_unlock(&rq->mtx);

		/* wait for dynamic interrupt moderation work task, if any */
		cancel_work_sync(&rq->dim.work);

		if (priv->params.rx_cq_moderation_mode >= 2) {
			struct net_dim_cq_moder curr;

			mlx5e_get_default_profile(priv, dim_mode, &curr);

			retval = mlx5_core_modify_cq_moderation_mode(priv->mdev, &rq->cq.mcq,
			    curr.usec, curr.pkts, cq_mode);

			/* set dynamic interrupt moderation mode and zero defaults */
			mtx_lock(&rq->mtx);
			rq->dim.mode = dim_mode;
			rq->dim.state = 0;
			rq->dim.profile_ix = MLX5E_DIM_DEFAULT_PROFILE;
			mtx_unlock(&rq->mtx);
		} else {
			retval = mlx5_core_modify_cq_moderation_mode(priv->mdev, &rq->cq.mcq,
			    priv->params.rx_cq_moderation_usec,
			    priv->params.rx_cq_moderation_pkts,
			    cq_mode);
		}
		return (retval);
	}

	return (mlx5_core_modify_cq_moderation(priv->mdev, &rq->cq.mcq,
	    priv->params.rx_cq_moderation_usec,
	    priv->params.rx_cq_moderation_pkts));
}