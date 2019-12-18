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
typedef  scalar_t__ u16 ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  dma; struct mlx4_alloc_vpp_param* buf; } ;
struct mlx4_alloc_vpp_param {int /*<<< orphan*/ * vpp_p_up; int /*<<< orphan*/  availible_vpp; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  MLX4_ALLOCATE_VPP_QUERY ; 
 int /*<<< orphan*/  MLX4_CMD_ALLOCATE_VPP ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int MLX4_NUM_UP ; 
 int PTR_ERR (struct mlx4_cmd_mailbox*) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 struct mlx4_cmd_mailbox* mlx4_alloc_cmd_mailbox (struct mlx4_dev*) ; 
 int mlx4_cmd_box (struct mlx4_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_free_cmd_mailbox (struct mlx4_dev*,struct mlx4_cmd_mailbox*) ; 

int mlx4_ALLOCATE_VPP_get(struct mlx4_dev *dev, u8 port,
			  u16 *availible_vpp, u8 *vpp_p_up)
{
	int i;
	int err;
	struct mlx4_cmd_mailbox *mailbox;
	struct mlx4_alloc_vpp_param *out_param;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	if (IS_ERR(mailbox))
		return PTR_ERR(mailbox);

	out_param = mailbox->buf;

	err = mlx4_cmd_box(dev, 0, mailbox->dma, port,
			   MLX4_ALLOCATE_VPP_QUERY,
			   MLX4_CMD_ALLOCATE_VPP,
			   MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	if (err)
		goto out;

	/* Total number of supported VPPs */
	*availible_vpp = (u16)be32_to_cpu(out_param->availible_vpp);

	for (i = 0; i < MLX4_NUM_UP; i++)
		vpp_p_up[i] = (u8)be32_to_cpu(out_param->vpp_p_up[i]);

out:
	mlx4_free_cmd_mailbox(dev, mailbox);

	return err;
}