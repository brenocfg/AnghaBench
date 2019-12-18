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
struct res_eq {TYPE_2__* mtt; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  res_id; } ;
struct TYPE_4__ {TYPE_1__ com; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_EQ ; 
 int /*<<< orphan*/  RES_EQ_RESERVED ; 
 int /*<<< orphan*/  RES_MTT ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int eq_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_eq**) ; 
 int get_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rem_res_range (struct mlx4_dev*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

int mlx4_HW2SW_EQ_wrapper(struct mlx4_dev *dev, int slave,
			  struct mlx4_vhcr *vhcr,
			  struct mlx4_cmd_mailbox *inbox,
			  struct mlx4_cmd_mailbox *outbox,
			  struct mlx4_cmd_info *cmd)
{
	int eqn = vhcr->in_modifier;
	int res_id = eqn | (slave << 10);
	struct res_eq *eq;
	int err;

	err = eq_res_start_move_to(dev, slave, res_id, RES_EQ_RESERVED, &eq);
	if (err)
		return err;

	err = get_res(dev, slave, eq->mtt->com.res_id, RES_MTT, NULL);
	if (err)
		goto ex_abort;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_put;

	atomic_dec(&eq->mtt->ref_count);
	put_res(dev, slave, eq->mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_EQ, res_id);
	rem_res_range(dev, slave, res_id, 1, RES_EQ, 0);

	return 0;

ex_put:
	put_res(dev, slave, eq->mtt->com.res_id, RES_MTT);
ex_abort:
	res_abort_move(dev, slave, RES_EQ, res_id);

	return err;
}