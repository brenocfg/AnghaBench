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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  res_id; } ;
struct res_mtt {TYPE_2__ com; int /*<<< orphan*/  ref_count; } ;
struct res_mpt {struct res_mtt* mtt; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct TYPE_3__ {int mtt_entry_sz; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int /*<<< orphan*/  buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  RES_MPT ; 
 int /*<<< orphan*/  RES_MPT_HW ; 
 int /*<<< orphan*/  RES_MTT ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int check_mtt_range (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mtt*) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mtt**) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int mpt_mask (struct mlx4_dev*) ; 
 int mr_get_mtt_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mr_get_mtt_size (int /*<<< orphan*/ ) ; 
 int mr_get_pd (int /*<<< orphan*/ ) ; 
 scalar_t__ mr_is_bind_enabled (int /*<<< orphan*/ ) ; 
 scalar_t__ mr_is_fmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mr_is_region (int /*<<< orphan*/ ) ; 
 int mr_phys_mpt (int /*<<< orphan*/ ) ; 
 int mr_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_mpt**) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 

int mlx4_SW2HW_MPT_wrapper(struct mlx4_dev *dev, int slave,
			   struct mlx4_vhcr *vhcr,
			   struct mlx4_cmd_mailbox *inbox,
			   struct mlx4_cmd_mailbox *outbox,
			   struct mlx4_cmd_info *cmd)
{
	int err;
	int index = vhcr->in_modifier;
	struct res_mtt *mtt;
	struct res_mpt *mpt;
	int mtt_base = mr_get_mtt_addr(inbox->buf) / dev->caps.mtt_entry_sz;
	int phys;
	int id;
	u32 pd;
	int pd_slave;

	id = index & mpt_mask(dev);
	err = mr_res_start_move_to(dev, slave, id, RES_MPT_HW, &mpt);
	if (err)
		return err;

	/* Disable memory windows for VFs. */
	if (!mr_is_region(inbox->buf)) {
		err = -EPERM;
		goto ex_abort;
	}

	/* Make sure that the PD bits related to the slave id are zeros. */
	pd = mr_get_pd(inbox->buf);
	pd_slave = (pd >> 17) & 0x7f;
	if (pd_slave != 0 && --pd_slave != slave) {
		err = -EPERM;
		goto ex_abort;
	}

	if (mr_is_fmr(inbox->buf)) {
		/* FMR and Bind Enable are forbidden in slave devices. */
		if (mr_is_bind_enabled(inbox->buf)) {
			err = -EPERM;
			goto ex_abort;
		}
		/* FMR and Memory Windows are also forbidden. */
		if (!mr_is_region(inbox->buf)) {
			err = -EPERM;
			goto ex_abort;
		}
	}

	phys = mr_phys_mpt(inbox->buf);
	if (!phys) {
		err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
		if (err)
			goto ex_abort;

		err = check_mtt_range(dev, slave, mtt_base,
				      mr_get_mtt_size(inbox->buf), mtt);
		if (err)
			goto ex_put;

		mpt->mtt = mtt;
	}

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_put;

	if (!phys) {
		atomic_inc(&mtt->ref_count);
		put_res(dev, slave, mtt->com.res_id, RES_MTT);
	}

	res_end_move(dev, slave, RES_MPT, id);
	return 0;

ex_put:
	if (!phys)
		put_res(dev, slave, mtt->com.res_id, RES_MTT);
ex_abort:
	res_abort_move(dev, slave, RES_MPT, id);

	return err;
}