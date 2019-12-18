#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long long u64 ;
typedef  int u32 ;
struct mlx4_update_qp_params {int flags; int rate_unit; int rate_val; int /*<<< orphan*/  qos_vport; int /*<<< orphan*/  smac_index; } ;
struct TYPE_5__ {int /*<<< orphan*/  fl; int /*<<< orphan*/  grh_mylmc; } ;
struct TYPE_6__ {int /*<<< orphan*/  qos_vport; int /*<<< orphan*/  rate_limit_params; int /*<<< orphan*/  param3; TYPE_2__ pri_path; } ;
struct mlx4_update_qp_context {void* qp_mask; void* primary_addr_path_mask; TYPE_3__ qp_context; } ;
struct TYPE_4__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__ buf; } ;
typedef  enum mlx4_update_qp_attr { ____Placeholder_mlx4_update_qp_attr } mlx4_update_qp_attr ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_UPDATE_QP ; 
 int MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB ; 
 int /*<<< orphan*/  MLX4_FL_ETH_SRC_CHECK_MC_LB ; 
 int /*<<< orphan*/  MLX4_STRIP_VLAN ; 
 int MLX4_UPDATE_QP_ETH_SRC_CHECK_MC_LB ; 
 int MLX4_UPDATE_QP_PARAMS_FLAGS_ETH_CHECK_MC_LB ; 
 int MLX4_UPDATE_QP_PARAMS_FLAGS_VSD_ENABLE ; 
 int MLX4_UPDATE_QP_QOS_VPORT ; 
 int MLX4_UPDATE_QP_RATE_LIMIT ; 
 int MLX4_UPDATE_QP_SMAC ; 
 int MLX4_UPDATE_QP_SUPPORTED_ATTRS ; 
 int MLX4_UPDATE_QP_VSD ; 
 unsigned long long MLX4_UPD_QP_MASK_QOS_VPP ; 
 unsigned long long MLX4_UPD_QP_MASK_RATE_LIMIT ; 
 unsigned long long MLX4_UPD_QP_MASK_VSD ; 
 unsigned long long MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB ; 
 unsigned long long MLX4_UPD_QP_PATH_MASK_MAC_INDEX ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (unsigned long long) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*) ; 

int mlx4_update_qp(struct mlx4_dev *dev, u32 qpn,
		   enum mlx4_update_qp_attr attr,
		   struct mlx4_update_qp_params *params)
{
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_update_qp_context *cmd;
	u64 pri_addr_path_mask = 0;
	u64 qp_mask = 0;
	int err = 0;

	if (!attr || (attr & ~MLX4_UPDATE_QP_SUPPORTED_ATTRS))
		return -EINVAL;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	cmd = (struct mlx4_update_qp_context *)mailbox->buf;

	if (attr & MLX4_UPDATE_QP_SMAC) {
		pri_addr_path_mask |= 1ULL << MLX4_UPD_QP_PATH_MASK_MAC_INDEX;
		cmd->qp_context.pri_path.grh_mylmc = params->smac_index;
	}

	if (attr & MLX4_UPDATE_QP_ETH_SRC_CHECK_MC_LB) {
		if (!(dev->caps.flags2
		      & MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB)) {
			mlx4_warn(dev,
				  "Trying to set src check LB, but it isn't supported\n");
			err = -ENOTSUPP;
			goto out;
		}
		pri_addr_path_mask |=
			1ULL << MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB;
		if (params->flags &
		    MLX4_UPDATE_QP_PARAMS_FLAGS_ETH_CHECK_MC_LB) {
			cmd->qp_context.pri_path.fl |=
				MLX4_FL_ETH_SRC_CHECK_MC_LB;
		}
	}

	if (attr & MLX4_UPDATE_QP_VSD) {
		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_VSD;
		if (params->flags & MLX4_UPDATE_QP_PARAMS_FLAGS_VSD_ENABLE)
			cmd->qp_context.param3 |= cpu_to_be32(MLX4_STRIP_VLAN);
	}

	if (attr & MLX4_UPDATE_QP_RATE_LIMIT) {
		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_RATE_LIMIT;
		cmd->qp_context.rate_limit_params = cpu_to_be16((params->rate_unit << 14) | params->rate_val);
	}

	if (attr & MLX4_UPDATE_QP_QOS_VPORT) {
		qp_mask |= 1ULL << MLX4_UPD_QP_MASK_QOS_VPP;
		cmd->qp_context.qos_vport = params->qos_vport;
	}

	cmd->primary_addr_path_mask = cpu_to_be64(pri_addr_path_mask);
	cmd->qp_mask = cpu_to_be64(qp_mask);

	err = mlx4_cmd(dev, mailbox->dma, qpn & 0xffffff, 0,
		       MLX4_CMD_UPDATE_QP, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
out:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}