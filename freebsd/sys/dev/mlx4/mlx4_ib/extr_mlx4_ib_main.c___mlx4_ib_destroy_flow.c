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
typedef  scalar_t__ u64 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_DETACH ; 
 int mlx4_cmd (struct mlx4_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,long long) ; 

__attribute__((used)) static int __mlx4_ib_destroy_flow(struct mlx4_dev *dev, u64 reg_id)
{
	int err;
	err = mlx4_cmd(dev, reg_id, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_WRAPPED);
	if (err)
		pr_err("Fail to detach network rule. registration id = 0x%llx\n",
		       (long long)reg_id);
	return err;
}