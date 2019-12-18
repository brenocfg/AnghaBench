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
typedef  int u32 ;
struct res_srq {int /*<<< orphan*/  ref_count; } ;
struct res_qp {int local_qpn; int qpc_flags; struct res_srq* srq; struct res_srq* scq; struct res_srq* rcq; struct res_srq* mtt; scalar_t__ feup; scalar_t__ vlan_index; scalar_t__ pri_path_fl; scalar_t__ fvl_rx; scalar_t__ vlan_control; scalar_t__ param3; scalar_t__ sched_queue; } ;
struct res_mtt {int /*<<< orphan*/  ref_count; } ;
struct res_cq {int /*<<< orphan*/  ref_count; } ;
struct mlx4_vhcr {int in_modifier; } ;
struct mlx4_qp_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  local_qpn; } ;
struct TYPE_2__ {int mtt_entry_sz; } ;
struct mlx4_dev {TYPE_1__ caps; } ;
struct mlx4_cmd_mailbox {struct mlx4_qp_context* buf; } ;
struct mlx4_cmd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RES_CQ ; 
 int /*<<< orphan*/  RES_MTT ; 
 int /*<<< orphan*/  RES_QP ; 
 int /*<<< orphan*/  RES_QP_HW ; 
 int /*<<< orphan*/  RES_SRQ ; 
 int /*<<< orphan*/  adjust_proxy_tun_qkey (struct mlx4_dev*,struct mlx4_vhcr*,struct mlx4_qp_context*) ; 
 int adjust_qp_sched_queue (struct mlx4_dev*,int,struct mlx4_qp_context*,struct mlx4_cmd_mailbox*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int check_mtt_range (struct mlx4_dev*,int,int,int,struct res_srq*) ; 
 int get_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_srq**) ; 
 int mlx4_DMA_wrapper (struct mlx4_dev*,int,struct mlx4_vhcr*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_mailbox*,struct mlx4_cmd_info*) ; 
 int /*<<< orphan*/  put_res (struct mlx4_dev*,int,int,int /*<<< orphan*/ ) ; 
 int qp_get_mtt_addr (struct mlx4_qp_context*) ; 
 int qp_get_mtt_size (struct mlx4_qp_context*) ; 
 int qp_get_rcqn (struct mlx4_qp_context*) ; 
 int qp_get_scqn (struct mlx4_qp_context*) ; 
 int qp_get_srqn (struct mlx4_qp_context*) ; 
 int qp_res_start_move_to (struct mlx4_dev*,int,int,int /*<<< orphan*/ ,struct res_qp**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  res_abort_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  res_end_move (struct mlx4_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  update_pkey_index (struct mlx4_dev*,int,struct mlx4_cmd_mailbox*) ; 

int mlx4_RST2INIT_QP_wrapper(struct mlx4_dev *dev, int slave,
			     struct mlx4_vhcr *vhcr,
			     struct mlx4_cmd_mailbox *inbox,
			     struct mlx4_cmd_mailbox *outbox,
			     struct mlx4_cmd_info *cmd)
{
	int err;
	int qpn = vhcr->in_modifier & 0x7fffff;
	struct res_mtt *mtt;
	struct res_qp *qp;
	struct mlx4_qp_context *qpc = inbox->buf + 8;
	int mtt_base = qp_get_mtt_addr(qpc) / dev->caps.mtt_entry_sz;
	int mtt_size = qp_get_mtt_size(qpc);
	struct res_cq *rcq;
	struct res_cq *scq;
	int rcqn = qp_get_rcqn(qpc);
	int scqn = qp_get_scqn(qpc);
	u32 srqn = qp_get_srqn(qpc) & 0xffffff;
	int use_srq = (qp_get_srqn(qpc) >> 24) & 1;
	struct res_srq *srq;
	int local_qpn = be32_to_cpu(qpc->local_qpn) & 0xffffff;

	err = adjust_qp_sched_queue(dev, slave, qpc, inbox);
	if (err)
		return err;

	err = qp_res_start_move_to(dev, slave, qpn, RES_QP_HW, &qp, 0);
	if (err)
		return err;
	qp->local_qpn = local_qpn;
	qp->sched_queue = 0;
	qp->param3 = 0;
	qp->vlan_control = 0;
	qp->fvl_rx = 0;
	qp->pri_path_fl = 0;
	qp->vlan_index = 0;
	qp->feup = 0;
	qp->qpc_flags = be32_to_cpu(qpc->flags);

	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	if (err)
		goto ex_abort;

	err = check_mtt_range(dev, slave, mtt_base, mtt_size, mtt);
	if (err)
		goto ex_put_mtt;

	err = get_res(dev, slave, rcqn, RES_CQ, &rcq);
	if (err)
		goto ex_put_mtt;

	if (scqn != rcqn) {
		err = get_res(dev, slave, scqn, RES_CQ, &scq);
		if (err)
			goto ex_put_rcq;
	} else
		scq = rcq;

	if (use_srq) {
		err = get_res(dev, slave, srqn, RES_SRQ, &srq);
		if (err)
			goto ex_put_scq;
	}

	adjust_proxy_tun_qkey(dev, vhcr, qpc);
	update_pkey_index(dev, slave, inbox);
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	if (err)
		goto ex_put_srq;
	atomic_inc(&mtt->ref_count);
	qp->mtt = mtt;
	atomic_inc(&rcq->ref_count);
	qp->rcq = rcq;
	atomic_inc(&scq->ref_count);
	qp->scq = scq;

	if (scqn != rcqn)
		put_res(dev, slave, scqn, RES_CQ);

	if (use_srq) {
		atomic_inc(&srq->ref_count);
		put_res(dev, slave, srqn, RES_SRQ);
		qp->srq = srq;
	}
	put_res(dev, slave, rcqn, RES_CQ);
	put_res(dev, slave, mtt_base, RES_MTT);
	res_end_move(dev, slave, RES_QP, qpn);

	return 0;

ex_put_srq:
	if (use_srq)
		put_res(dev, slave, srqn, RES_SRQ);
ex_put_scq:
	if (scqn != rcqn)
		put_res(dev, slave, scqn, RES_CQ);
ex_put_rcq:
	put_res(dev, slave, rcqn, RES_CQ);
ex_put_mtt:
	put_res(dev, slave, mtt_base, RES_MTT);
ex_abort:
	res_abort_move(dev, slave, RES_QP, qpn);

	return err;
}