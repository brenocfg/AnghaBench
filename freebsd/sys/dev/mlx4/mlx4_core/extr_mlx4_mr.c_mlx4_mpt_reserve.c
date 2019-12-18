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
typedef  int /*<<< orphan*/  u64 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_ALLOC_RES ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  RES_MPT ; 
 int /*<<< orphan*/  RES_OP_RESERVE ; 
 int __mlx4_mpt_reserve (struct mlx4_dev*) ; 
 int get_param_l (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mlx4_is_mfunc (struct mlx4_dev*) ; 

__attribute__((used)) static int mlx4_mpt_reserve(struct mlx4_dev *dev)
{
	u64 out_param;

	if (mlx4_is_mfunc(dev)) {
		if (mlx4_cmd_imm(dev, 0, &out_param, RES_MPT, RES_OP_RESERVE,
				   MLX4_CMD_ALLOC_RES,
				   MLX4_CMD_TIME_CLASS_A, MLX4_CMD_WRAPPED))
			return -1;
		return get_param_l(&out_param);
	}
	return  __mlx4_mpt_reserve(dev);
}