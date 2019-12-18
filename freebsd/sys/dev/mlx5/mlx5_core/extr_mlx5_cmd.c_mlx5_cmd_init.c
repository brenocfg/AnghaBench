#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct mlx5_cmd {int log_sz; int log_stride; int checksum_disabled; int max_reg_cmds; int bitmask; int cmdif_rev; int /*<<< orphan*/  mode; scalar_t__ dma; int /*<<< orphan*/  pages_sem; int /*<<< orphan*/  sem; TYPE_2__* stats; int /*<<< orphan*/  token_lock; int /*<<< orphan*/  alloc_lock; } ;
struct mlx5_core_dev {TYPE_1__* iseg; struct mlx5_cmd cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  cmdq_addr_l_sz; int /*<<< orphan*/  cmdq_addr_h; int /*<<< orphan*/  cmdif_rev_fw_sub; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int CMD_IF_REV ; 
 int EINVAL ; 
 int ENOMEM ; 
 int ENOTSUPP ; 
 int MLX5_ADAPTER_PAGE_SHIFT ; 
 int /*<<< orphan*/  MLX5_CMD_MODE_POLLING ; 
 int MLX5_MAX_COMMANDS ; 
 int alloc_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 
 int cmdif_rev_get (struct mlx5_core_dev*) ; 
 int create_msg_cache (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  free_cmd_page (struct mlx5_core_dev*,struct mlx5_cmd*) ; 
 int ioread32be (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32be (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mlx5_cmd*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,unsigned long long) ; 
 int /*<<< orphan*/  mlx5_core_err (struct mlx5_core_dev*,char*,...) ; 
 int /*<<< orphan*/  sema_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

int mlx5_cmd_init(struct mlx5_core_dev *dev)
{
	struct mlx5_cmd *cmd = &dev->cmd;
	u32 cmd_h, cmd_l;
	u16 cmd_if_rev;
	int err;
	int i;

	memset(cmd, 0, sizeof(*cmd));
	cmd_if_rev = cmdif_rev_get(dev);
	if (cmd_if_rev != CMD_IF_REV) {
		mlx5_core_err(dev,
		    "Driver cmdif rev(%d) differs from firmware's(%d)\n",
		    CMD_IF_REV, cmd_if_rev);
		return -EINVAL;
	}

	err = alloc_cmd_page(dev, cmd);
	if (err)
		goto err_free_pool;

	cmd_l = ioread32be(&dev->iseg->cmdq_addr_l_sz) & 0xff;
	cmd->log_sz = cmd_l >> 4 & 0xf;
	cmd->log_stride = cmd_l & 0xf;
	if (1 << cmd->log_sz > MLX5_MAX_COMMANDS) {
		mlx5_core_err(dev,
		    "firmware reports too many outstanding commands %d\n",
		    1 << cmd->log_sz);
		err = -EINVAL;
		goto err_free_page;
	}

	if (cmd->log_sz + cmd->log_stride > MLX5_ADAPTER_PAGE_SHIFT) {
		mlx5_core_err(dev,
		    "command queue size overflow\n");
		err = -EINVAL;
		goto err_free_page;
	}

	cmd->checksum_disabled = 1;
	cmd->max_reg_cmds = (1 << cmd->log_sz) - 1;
	cmd->bitmask = (1 << cmd->max_reg_cmds) - 1;

	cmd->cmdif_rev = ioread32be(&dev->iseg->cmdif_rev_fw_sub) >> 16;
	if (cmd->cmdif_rev > CMD_IF_REV) {
		mlx5_core_err(dev,
		    "driver does not support command interface version. driver %d, firmware %d\n",
		    CMD_IF_REV, cmd->cmdif_rev);
		err = -ENOTSUPP;
		goto err_free_page;
	}

	spin_lock_init(&cmd->alloc_lock);
	spin_lock_init(&cmd->token_lock);
	for (i = 0; i < ARRAY_SIZE(cmd->stats); i++)
		spin_lock_init(&cmd->stats[i].lock);

	sema_init(&cmd->sem, cmd->max_reg_cmds);
	sema_init(&cmd->pages_sem, 1);

	cmd_h = (u32)((u64)(cmd->dma) >> 32);
	cmd_l = (u32)(cmd->dma);
	if (cmd_l & 0xfff) {
		mlx5_core_err(dev, "invalid command queue address\n");
		err = -ENOMEM;
		goto err_free_page;
	}

	iowrite32be(cmd_h, &dev->iseg->cmdq_addr_h);
	iowrite32be(cmd_l, &dev->iseg->cmdq_addr_l_sz);

	/* Make sure firmware sees the complete address before we proceed */
	wmb();

	mlx5_core_dbg(dev, "descriptor at dma 0x%llx\n", (unsigned long long)(cmd->dma));

	cmd->mode = MLX5_CMD_MODE_POLLING;

	err = create_msg_cache(dev);
	if (err) {
		mlx5_core_err(dev, "failed to create command cache\n");
		goto err_free_page;
	}
	return 0;

err_free_page:
	free_cmd_page(dev, cmd);

err_free_pool:
	return err;
}