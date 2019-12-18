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
struct res_srq {TYPE_2__* cq; TYPE_1__* mtt; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ref_count; } ;
struct TYPE_3__ {int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_SRQ ; 
 int /*<<< orphan*/  RES_SRQ_ALLOCATED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int srq_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_srq**) ; 

int mlx4_HW2SW_SRQ_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	int err;
	int srqn = vhcr->in_modifier;
	struct res_srq *srq = NULL;

	err = srq_res_start_move_to(dev, slave, srqn, RES_SRQ_ALLOCATED, &srq);
	if (err)
		return err;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_abort;
	atomic_dec(&srq->mtt->ref_count);
	if (srq->cq)
		atomic_dec(&srq->cq->ref_count);
	res_end_move(dev, slave, RES_SRQ, srqn);

	return 0;

ex_abort:
	res_abort_move(dev, slave, RES_SRQ, srqn);

	return err;
}