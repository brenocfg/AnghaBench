#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct res_qp {scalar_t__ qpn; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  mirr_mbox; scalar_t__ mirr_rule_id; } ;
struct res_fs_rule {scalar_t__ qpn; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  mirr_mbox; scalar_t__ mirr_rule_id; } ;
struct mlx4_vhcr {scalar_t__ in_param; } ;
struct TYPE_2__ {scalar_t__ steering_mode; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {int dummy; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MLX4_CMD_NATIVE ; 
 int /*<<< orphan*/  MLX4_CMD_TIME_CLASS_A ; 
 int /*<<< orphan*/  MLX4_QP_FLOW_STEERING_DETACH ; 
 scalar_t__ MLX4_STEERING_MODE_DEVICE_MANAGED ; 
 int /*<<< orphan*/  RES_FS_RULE ; 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int get_res (struct mlx4_dev*,int,scalar_t__,int /*<<< orphan*/ ,struct res_qp**) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int mlx4_cmd (struct mlx4_dev*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx4_err (struct mlx4_dev*,char*) ; 
 scalar_t__ mlx4_is_bonded (struct mlx4_dev*) ; 
 int /*<<< orphan*/  mlx4_undo_mirror_rule (struct mlx4_dev*,struct res_qp*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int rem_res_range (struct mlx4_dev*,int,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mlx4_QP_FLOW_STEERING_DETACH_wrapper(struct mlx4_dev *dev, int slave,
					 struct mlx4_vhcr *vhcr,
					 struct mlx4_cmd_mailbox *inbox,
					 struct mlx4_cmd_mailbox *outbox,
					 struct mlx4_cmd_info *cmd)
{
	int err;
	struct res_qp *rqp;
	struct res_fs_rule *rrule;
	u64 mirr_reg_id;

	if (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		return -EOPNOTSUPP;

	err = get_res(dev, slave, vhcr->in_param, RES_FS_RULE, &rrule);
	if (err)
		return err;

	if (!rrule->mirr_mbox) {
		mlx4_err(dev, "Mirror rules cannot be removed explicitly\n");
		put_res(dev, slave, vhcr->in_param, RES_FS_RULE);
		return -EINVAL;
	}
	mirr_reg_id = rrule->mirr_rule_id;
	kfree(rrule->mirr_mbox);

	/* Release the rule form busy state before removal */
	put_res(dev, slave, vhcr->in_param, RES_FS_RULE);
	err = get_res(dev, slave, rrule->qpn, RES_QP, &rqp);
	if (err)
		return err;

	if (mirr_reg_id && mlx4_is_bonded(dev)) {
		err = get_res(dev, slave, mirr_reg_id, RES_FS_RULE, &rrule);
		if (err) {
			mlx4_err(dev, "Fail to get resource of mirror rule\n");
		} else {
			put_res(dev, slave, mirr_reg_id, RES_FS_RULE);
			mlx4_undo_mirror_rule(dev, rrule);
		}
	}
	err = rem_res_range(dev, slave, vhcr->in_param, 1, RES_FS_RULE, 0);
	if (err) {
		mlx4_err(dev, "Fail to remove flow steering resources\n");
		goto out;
	}

	err = mlx4_cmd(dev, vhcr->in_param, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	if (!err)
		atomic_dec(&rqp->ref_count);
out:
	put_res(dev, slave, rrule->qpn, RES_QP);
	return err;
}