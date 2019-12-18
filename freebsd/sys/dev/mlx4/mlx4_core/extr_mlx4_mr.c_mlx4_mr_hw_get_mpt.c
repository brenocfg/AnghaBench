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
struct mlx4_mr {scalar_t__ enabled; int /*<<< orphan*/  key; } ;
struct mlx4_mpt_entry {int dummy; } ;
struct TYPE_4__ {int num_mpts; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; int /*<<< orphan*/  dma; } ;
struct TYPE_5__ {int /*<<< orphan*/  dmpt_table; } ;
struct TYPE_6__ {TYPE_2__ mr_table; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_CMD_QUERY_MPT ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_B ; 
 int /*<<< orphan*/  MLX4_CMD_WRAPPED ; 
 scalar_t__ MLX4_MPT_EN_HW ; 
 scalar_t__ MLX4_MPT_EN_SW ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int key_to_hw_index (int /*<<< orphan*/ ) ; 
 int mlx4_HW2SW_MPT (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  mlx4_is_mfunc (struct mlx4_dev*) ; 
 TYPE_3__* mlx4_priv (struct mlx4_dev*) ; 
 struct mlx4_mpt_entry* mlx4_table_find (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_warn (struct mlx4_dev*,char*,...) ; 

int mlx4_mr_hw_get_mpt(struct mlx4_dev *dev, struct mlx4_mr *mmr,
		       struct mlx4_mpt_entry ***mpt_entry)
{
	int err;
	int key = key_to_hw_index(mmr->key) & (dev->caps.num_mpts - 1);
	struct mlx4_cmd_mailbox *mailbox = NULL;

	if (mmr->enabled != MLX4_MPT_EN_HW)
		return -EINVAL;

	err = mlx4_HW2SW_MPT(dev, NULL, key);
	if (err) {
		mlx4_warn(dev, "HW2SW_MPT failed (%d).", err);
		mlx4_warn(dev, "Most likely the MR has MWs bound to it.\n");
		return err;
	}

	mmr->enabled = MLX4_MPT_EN_SW;

	if (!mlx4_is_mfunc(dev)) {
		**mpt_entry = mlx4_table_find(
				&mlx4_priv(dev)->mr_table.dmpt_table,
				key, NULL);
	} else {
		mailbox = mlx4_alloc_cmd_mailbox(dev);
		if (IS_ERR(mailbox))
			return PTR_ERR(mailbox);

		err = mlx4_cmd_box(dev, 0, mailbox->dma, key,
				   0, MLX4_CMD_QUERY_MPT,
				   MLX4_CMD_TIME_CLASS_B,
				   MLX4_CMD_WRAPPED);
		if (err)
			goto free_mailbox;

		*mpt_entry = (struct mlx4_mpt_entry **)&mailbox->buf;
	}

	if (!(*mpt_entry) || !(**mpt_entry)) {
		err = -ENOMEM;
		goto free_mailbox;
	}

	return 0;

free_mailbox:
	mlx4_free_cmd_mailbox(dev, mailbox);
	return err;
}