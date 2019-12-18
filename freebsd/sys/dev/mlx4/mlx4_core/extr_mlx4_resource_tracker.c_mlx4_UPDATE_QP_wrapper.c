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
struct res_qp {int sched_queue; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct TYPE_5__ {int grh_mylmc; } ;
struct TYPE_6__ {TYPE_2__ pri_path; } ;
struct mlx4_update_qp_context {TYPE_3__ qp_context; scalar_t__ secondary_addr_path_mask; scalar_t__ qp_mask; int /*<<< orphan*/  primary_addr_path_mask; } ;
struct TYPE_4__ {int flags2; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; scalar_t__ buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_CMD_UPDATE_QP ; 
 int MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB ; 
 unsigned long long MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB ; 
 unsigned long long MLX4_UPD_QP_PATH_MASK_MAC_INDEX ; 
 unsigned long long MLX4_UPD_QP_PATH_MASK_SUPPORTED ; 
 int /*<<< orphan*/  RES_QP ; 
 unsigned long long be64_to_cpu (int /*<<< orphan*/ ) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_qp**) ; 
 int mac_find_smac_ix_in_slave (struct mlx4_dev*,int,unsigned int,int,unsigned long long*) ; 
 int mlx4_cmd (struct mlx4_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*,int,...) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,int) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 

int mlx4_UPDATE_QP_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd_info)
{
	int err;
	u32 qpn = vhcr->in_modifier & 0xffffff;
	struct res_qp *rqp;
	u64 mac;
	unsigned port;
	u64 pri_addr_path_mask;
	struct mlx4_update_qp_context *cmd;
	int smac_index;

	cmd = (struct mlx4_update_qp_context *)inbox->buf;

	pri_addr_path_mask = be64_to_cpu(cmd->primary_addr_path_mask);
	if (cmd->qp_mask || cmd->secondary_addr_path_mask ||
	    (pri_addr_path_mask & ~MLX4_UPD_QP_PATH_MASK_SUPPORTED))
		return -EPERM;

	if ((pri_addr_path_mask &
	     (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB)) &&
		!(dev->caps.flags2 &
		  MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB)) {
		mlx4_warn(dev, "Src check LB for slave %d isn't supported\n",
			  slave);
		return -ENOTSUPP;
	}

	/* Just change the smac for the QP */
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	if (err) {
		mlx4_err(dev, "Updating qpn 0x%x for slave %d rejected\n", qpn, slave);
		return err;
	}

	port = (rqp->sched_queue >> 6 & 1) + 1;

	if (pri_addr_path_mask & (1ULL << MLX4_UPD_QP_PATH_MASK_MAC_INDEX)) {
		smac_index = cmd->qp_context.pri_path.grh_mylmc;
		err = mac_find_smac_ix_in_slave(dev, slave, port,
						smac_index, &mac);

		if (err) {
			mlx4_err(dev, "Failed to update qpn 0x%x, MAC is invalid. smac_ix: %d\n",
				 qpn, smac_index);
			goto err_mac;
		}
	}

	err = mlx4_cmd(dev, inbox->dma,
		       vhcr->in_modifier, 0,
		       MLX4_CMD_UPDATE_QP, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	if (err) {
		mlx4_err(dev, "Failed to update qpn on qpn 0x%x, command failed\n", qpn);
		goto err_mac;
	}

err_mac:
	put_res(dev, slave, qpn, RES_QP);
	return err;
}