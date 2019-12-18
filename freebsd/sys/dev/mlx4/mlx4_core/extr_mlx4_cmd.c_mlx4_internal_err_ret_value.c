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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct mlx4_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_STAT_INTERNAL_ERR ; 
 int CMD_STAT_OK ; 
#define  MLX4_CMD_2RST_QP 140 
#define  MLX4_CMD_CLOSE_HCA 139 
#define  MLX4_CMD_CLOSE_PORT 138 
#define  MLX4_CMD_FREE_RES 137 
#define  MLX4_CMD_HW2SW_CQ 136 
#define  MLX4_CMD_HW2SW_EQ 135 
#define  MLX4_CMD_HW2SW_MPT 134 
#define  MLX4_CMD_HW2SW_SRQ 133 
#define  MLX4_CMD_QP_ATTACH 132 
#define  MLX4_CMD_UNMAP_FA 131 
#define  MLX4_CMD_UNMAP_ICM 130 
#define  MLX4_CMD_UNMAP_ICM_AUX 129 
#define  MLX4_QP_FLOW_STEERING_DETACH 128 
 int mlx4_status_to_errno (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_internal_err_ret_value(struct mlx4_dev *dev, u16 op,
				       u8 op_modifier)
{
	switch (op) {
	case MLX4_CMD_UNMAP_ICM:
	case MLX4_CMD_UNMAP_ICM_AUX:
	case MLX4_CMD_UNMAP_FA:
	case MLX4_CMD_2RST_QP:
	case MLX4_CMD_HW2SW_EQ:
	case MLX4_CMD_HW2SW_CQ:
	case MLX4_CMD_HW2SW_SRQ:
	case MLX4_CMD_HW2SW_MPT:
	case MLX4_CMD_CLOSE_HCA:
	case MLX4_QP_FLOW_STEERING_DETACH:
	case MLX4_CMD_FREE_RES:
	case MLX4_CMD_CLOSE_PORT:
		return CMD_STAT_OK;

	case MLX4_CMD_QP_ATTACH:
		/* On Detach case return success */
		if (op_modifier == 0)
			return CMD_STAT_OK;
		return mlx4_status_to_errno(CMD_STAT_INTERNAL_ERR);

	default:
		return mlx4_status_to_errno(CMD_STAT_INTERNAL_ERR);
	}
}