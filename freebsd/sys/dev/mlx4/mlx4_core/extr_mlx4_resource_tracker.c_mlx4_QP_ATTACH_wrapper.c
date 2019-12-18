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
typedef  int u8 ;
typedef  scalar_t__ u64 ;
struct res_qp {int dummy; } ;
struct mlx4_vhcr {int in_modifier; int op_modifier; } ;
struct mlx4_qp {int qpn; } ;
struct mlx4_dev {int dummy; } ;
struct mlx4_cmd_mailbox {int* buf; } ;
struct mlx4_cmd_info {int dummy; } ;
typedef  enum mlx4_steer_type { ____Placeholder_mlx4_steer_type } mlx4_steer_type ;
typedef  enum mlx4_protocol { ____Placeholder_mlx4_protocol } mlx4_protocol ;

/* Variables and functions */
 int /*<<< orphan*/  RES_QP ; 
 int add_mcg_res (struct mlx4_dev*,int,struct res_qp*,int*,int,int,scalar_t__) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_qp**) ; 
 int mlx4_adjust_port (struct mlx4_dev*,int,int*,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,...) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 
 int qp_attach (struct mlx4_dev*,int,struct mlx4_qp*,int*,int,int,int,scalar_t__*) ; 
 int qp_detach (struct mlx4_dev*,struct mlx4_qp*,int*,int,int,scalar_t__) ; 
 int rem_mcg_res (struct mlx4_dev*,int,struct res_qp*,int*,int,int,scalar_t__*) ; 

int mlx4_QP_ATTACH_wrapper(struct mlx4_dev *dev, int slave,
			       struct mlx4_vhcr *vhcr,
			       struct mlx4_cmd_mailbox *inbox,
			       struct mlx4_cmd_mailbox *outbox,
			       struct mlx4_cmd_info *cmd)
{
	struct mlx4_qp qp; /* dummy for calling attach/detach */
	u8 *gid = inbox->buf;
	enum mlx4_protocol prot = (vhcr->in_modifier >> 28) & 0x7;
	int err;
	int qpn;
	struct res_qp *rqp;
	u64 reg_id = 0;
	int attach = vhcr->op_modifier;
	int block_loopback = vhcr->in_modifier >> 31;
	u8 steer_type_mask = 2;
	enum mlx4_steer_type type = (gid[7] & steer_type_mask) >> 1;

	qpn = vhcr->in_modifier & 0xffffff;
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	if (err)
		return err;

	qp.qpn = qpn;
	if (attach) {
		err = qp_attach(dev, slave, &qp, gid, block_loopback, prot,
				type, &reg_id);
		if (err) {
			pr_err("Fail to attach rule to qp 0x%x\n", qpn);
			goto ex_put;
		}
		err = add_mcg_res(dev, slave, rqp, gid, prot, type, reg_id);
		if (err)
			goto ex_detach;
	} else {
		err = mlx4_adjust_port(dev, slave, gid, prot);
		if (err)
			goto ex_put;

		err = rem_mcg_res(dev, slave, rqp, gid, prot, type, &reg_id);
		if (err)
			goto ex_put;

		err = qp_detach(dev, &qp, gid, prot, type, reg_id);
		if (err)
			pr_err("Fail to detach rule from qp 0x%x reg_id = 0x%llx\n",
			       qpn, (unsigned long long)reg_id);
	}
	put_res(dev, slave, qpn, RES_QP);
	return err;

ex_detach:
	qp_detach(dev, &qp, gid, prot, type, reg_id);
ex_put:
	put_res(dev, slave, qpn, RES_QP);
	return err;
}