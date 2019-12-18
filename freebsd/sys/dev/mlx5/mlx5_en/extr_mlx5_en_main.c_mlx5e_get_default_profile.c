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
struct net_dim_cq_moder {scalar_t__ pkts; } ;
struct TYPE_2__ {scalar_t__ hw_lro_en; } ;
struct mlx5e_priv {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_DIM_DEFAULT_PROFILE ; 
 scalar_t__ MLX5E_DIM_MAX_RX_CQ_MODERATION_PKTS_WITH_LRO ; 
 struct net_dim_cq_moder net_dim_get_profile (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mlx5e_get_default_profile(struct mlx5e_priv *priv, int mode, struct net_dim_cq_moder *ptr)
{

	*ptr = net_dim_get_profile(mode, MLX5E_DIM_DEFAULT_PROFILE);

	/* apply LRO restrictions */
	if (priv->params.hw_lro_en &&
	    ptr->pkts > MLX5E_DIM_MAX_RX_CQ_MODERATION_PKTS_WITH_LRO) {
		ptr->pkts = MLX5E_DIM_MAX_RX_CQ_MODERATION_PKTS_WITH_LRO;
	}
}