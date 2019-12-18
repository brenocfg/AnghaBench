#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  enum mlx5_ib_cong_node_type { ____Placeholder_mlx5_ib_cong_node_type } mlx5_ib_cong_node_type ;

/* Variables and functions */
 scalar_t__ MLX5_IB_INDEX (int /*<<< orphan*/ ) ; 
 int MLX5_IB_RROCE_ECN_NP ; 
 int MLX5_IB_RROCE_ECN_RP ; 
 int /*<<< orphan*/  rp_clamp_tgt_rate ; 
 int /*<<< orphan*/  rp_gd ; 

__attribute__((used)) static enum mlx5_ib_cong_node_type
mlx5_ib_param_to_node(u32 index)
{

	if (index >= MLX5_IB_INDEX(rp_clamp_tgt_rate) &&
	    index <= MLX5_IB_INDEX(rp_gd))
		return MLX5_IB_RROCE_ECN_RP;
	else
		return MLX5_IB_RROCE_ECN_NP;
}