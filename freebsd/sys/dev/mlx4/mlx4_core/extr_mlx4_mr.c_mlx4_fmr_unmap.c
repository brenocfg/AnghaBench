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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  enabled; int /*<<< orphan*/  key; } ;
struct mlx4_fmr {TYPE_2__ mr; scalar_t__ maps; } ;
struct TYPE_3__ {int num_mpts; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_MPT_EN_SW ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 int key_to_hw_index (int /*<<< orphan*/ ) ; 
 int mlx4_HW2SW_MPT (struct mlx4_dev*,int /*<<< orphan*/ *,int) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

void mlx4_fmr_unmap(struct mlx4_dev *dev, struct mlx4_fmr *fmr,
		    u32 *lkey, u32 *rkey)
{
	struct mlx4_cmd_mailbox *mailbox;
	int err;

	if (!fmr->maps)
		return;

	fmr->maps = 0;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox)) {
		err = PTR_ERR(mailbox);
		pr_warn("mlx4_ib: mlx4_alloc_cmd_mailbox failed (%d)\n", err);
		return;
	}

	err = mlx4_HW2SW_MPT(dev, NULL,
			     key_to_hw_index(fmr->mr.key) &
			     (dev->caps.num_mpts - 1));
	mlx4_free_cmd_mailbox(dev, mailbox);
	if (err) {
		pr_warn("mlx4_ib: mlx4_HW2SW_MPT failed (%d)\n", err);
		return;
	}
	fmr->mr.enabled = MLX4_MPT_EN_SW;
}