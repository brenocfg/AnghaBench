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
typedef  int u64 ;
struct mlx4_dev {int dummy; } ;
typedef  enum mlx4_port_type { ____Placeholder_mlx4_port_type } mlx4_port_type ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MLX4_CMD_SENSE_PORT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 int mlx4_cmd_imm (struct mlx4_dev*,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,long long) ; 

int mlx4_SENSE_PORT(struct mlx4_dev *dev, int port,
		    enum mlx4_port_type *type)
{
	u64 out_param;
	int err = 0;

	err = mlx4_cmd_imm(dev, 0, &out_param, port, 0,
			   MLX4_CMD_SENSE_PORT, MLX4_CMD_TIME_CLASS_B,
			   MLX4_CMD_WRAPPED);
	if (err) {
		mlx4_err(dev, "Sense command failed for port: %d\n", port);
		return err;
	}

	if (out_param > 2) {
		mlx4_err(dev, "Sense returned illegal value: 0x%llx\n", (long long)out_param);
		return -EINVAL;
	}

	*type = out_param;
	return 0;
}