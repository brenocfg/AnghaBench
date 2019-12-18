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
struct net_dim_cq_moder {int usec; int pkts; } ;
struct TYPE_2__ {int log_rq_size; int rx_cq_moderation_mode; int rx_cq_moderation_usec; int rx_cq_moderation_pkts; scalar_t__ cqe_zipping_en; } ;
struct mlx5e_priv {int /*<<< orphan*/  mdev; TYPE_1__ params; } ;
struct mlx5e_cq_param {void* cqc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CAP_GEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MLX5_CQE_FORMAT_HASH ; 
 int MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int MLX5_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  MLX5_SET (void*,void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE ; 
 int /*<<< orphan*/  NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE ; 
 int /*<<< orphan*/  cq_max_count ; 
 int /*<<< orphan*/  cq_period ; 
 int /*<<< orphan*/  cq_period_mode ; 
 int /*<<< orphan*/  cq_period_start_from_cqe ; 
 int /*<<< orphan*/  cqe_compression_en ; 
 int /*<<< orphan*/  log_cq_size ; 
 int /*<<< orphan*/  mini_cqe_res_format ; 
 int /*<<< orphan*/  mlx5e_build_common_cq_param (struct mlx5e_priv*,struct mlx5e_cq_param*) ; 
 int /*<<< orphan*/  mlx5e_dim_build_cq_param (struct mlx5e_priv*,struct mlx5e_cq_param*) ; 
 int /*<<< orphan*/  mlx5e_get_default_profile (struct mlx5e_priv*,int /*<<< orphan*/ ,struct net_dim_cq_moder*) ; 

__attribute__((used)) static void
mlx5e_build_rx_cq_param(struct mlx5e_priv *priv,
    struct mlx5e_cq_param *param)
{
	struct net_dim_cq_moder curr;
	void *cqc = param->cqc;

	/*
	 * We use MLX5_CQE_FORMAT_HASH because the RX hash mini CQE
	 * format is more beneficial for FreeBSD use case.
	 *
	 * Adding support for MLX5_CQE_FORMAT_CSUM will require changes
	 * in mlx5e_decompress_cqe.
	 */
	if (priv->params.cqe_zipping_en) {
		MLX5_SET(cqc, cqc, mini_cqe_res_format, MLX5_CQE_FORMAT_HASH);
		MLX5_SET(cqc, cqc, cqe_compression_en, 1);
	}

	MLX5_SET(cqc, cqc, log_cq_size, priv->params.log_rq_size);

	switch (priv->params.rx_cq_moderation_mode) {
	case 0:
		MLX5_SET(cqc, cqc, cq_period, priv->params.rx_cq_moderation_usec);
		MLX5_SET(cqc, cqc, cq_max_count, priv->params.rx_cq_moderation_pkts);
		MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);
		break;
	case 1:
		MLX5_SET(cqc, cqc, cq_period, priv->params.rx_cq_moderation_usec);
		MLX5_SET(cqc, cqc, cq_max_count, priv->params.rx_cq_moderation_pkts);
		if (MLX5_CAP_GEN(priv->mdev, cq_period_start_from_cqe))
			MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_CQE);
		else
			MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);
		break;
	case 2:
		mlx5e_get_default_profile(priv, NET_DIM_CQ_PERIOD_MODE_START_FROM_EQE, &curr);
		MLX5_SET(cqc, cqc, cq_period, curr.usec);
		MLX5_SET(cqc, cqc, cq_max_count, curr.pkts);
		MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);
		break;
	case 3:
		mlx5e_get_default_profile(priv, NET_DIM_CQ_PERIOD_MODE_START_FROM_CQE, &curr);
		MLX5_SET(cqc, cqc, cq_period, curr.usec);
		MLX5_SET(cqc, cqc, cq_max_count, curr.pkts);
		if (MLX5_CAP_GEN(priv->mdev, cq_period_start_from_cqe))
			MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_CQE);
		else
			MLX5_SET(cqc, cqc, cq_period_mode, MLX5_CQ_PERIOD_MODE_START_FROM_EQE);
		break;
	default:
		break;
	}

	mlx5e_dim_build_cq_param(priv, param);

	mlx5e_build_common_cq_param(priv, param);
}