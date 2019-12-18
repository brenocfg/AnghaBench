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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  mcq; } ;
struct mlx5e_sq {TYPE_1__ cq; } ;
struct TYPE_4__ {int tx_cq_moderation_mode; int /*<<< orphan*/  tx_cq_moderation_pkts; int /*<<< orphan*/  tx_cq_moderation_usec; } ;
struct mlx5e_priv {TYPE_2__ params; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  cq_period_mode_modify ; 
 int mlx5_core_modify_cq_moderation (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mlx5_core_modify_cq_moderation_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mlx5e_refresh_sq_params(struct mlx5e_priv *priv, struct mlx5e_sq *sq)
{

	if (MLX5_CAP_GEN(priv->mdev, cq_period_mode_modify)) {
		uint8_t cq_mode;

		switch (priv->params.tx_cq_moderation_mode) {
		case 0:
		case 2:
			cq_mode = MLX5_CQ_PERIOD_MODE_START_FROM_EQE;
			break;
		default:
			cq_mode = MLX5_CQ_PERIOD_MODE_START_FROM_CQE;
			break;
		}

		return (mlx5_core_modify_cq_moderation_mode(priv->mdev, &sq->cq.mcq,
		    priv->params.tx_cq_moderation_usec,
		    priv->params.tx_cq_moderation_pkts,
		    cq_mode));
	}

	return (mlx5_core_modify_cq_moderation(priv->mdev, &sq->cq.mcq,
	    priv->params.tx_cq_moderation_usec,
	    priv->params.tx_cq_moderation_pkts));
}