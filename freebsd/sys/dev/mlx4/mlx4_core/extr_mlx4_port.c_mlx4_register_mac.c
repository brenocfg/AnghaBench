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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct mlx4_dev {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_CMD_ALLOC_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int MLX4_FLAG_OLD_REG_MAC ; 
 int RES_MAC ; 
 int /*<<< orphan*/  RES_OP_RESERVE_AND_MAP ; 
 int __mlx4_register_mac (struct mlx4_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 int /*<<< orphan*/  set_param_l (int /*<<< orphan*/ *,scalar_t__) ; 

int mlx4_register_mac(struct mlx4_dev *dev, u8 port, u64 mac)
{
	u64 out_param = 0;
	int err = -EINVAL;

	if (mlx4_is_mfunc(dev)) {
		if (!(dev->flags & MLX4_FLAG_OLD_REG_MAC)) {
			err = mlx4_cmd_imm(dev, mac, &out_param,
					   ((u32) port) << 8 | (u32) RES_MAC,
					   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
					   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
		}
		if (err && err == -EINVAL && mlx4_is_slave(dev)) {
			/* retry using old REG_MAC format */
			set_param_l(&out_param, port);
			err = mlx4_cmd_imm(dev, mac, &out_param, RES_MAC,
					   RES_OP_RESERVE_AND_MAP, MLX4_CMD_ALLOC_RES,
					   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED);
			if (!err)
				dev->flags |= MLX4_FLAG_OLD_REG_MAC;
		}
		if (err)
			return err;

		return get_param_l(&out_param);
	}
	return __mlx4_register_mac(dev, port, mac);
}