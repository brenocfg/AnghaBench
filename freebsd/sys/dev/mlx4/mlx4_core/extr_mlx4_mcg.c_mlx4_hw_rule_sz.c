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
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_net_trans_rule_id { ____Placeholder_mlx4_net_trans_rule_id } mlx4_net_trans_rule_id ;

/* Variables and functions */
 int EINVAL ; 
 int MLX4_NET_TRANS_RULE_NUM ; 
 int* __rule_hw_sz ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int) ; 

int mlx4_hw_rule_sz(struct mlx4_dev *dev,
	       enum mlx4_net_trans_rule_id id)
{
	if (id >= MLX4_NET_TRANS_RULE_NUM) {
		mlx4_err(dev, "Invalid network rule id. id = %d\n", id);
		return -EINVAL;
	}

	return __rule_hw_sz[id];
}