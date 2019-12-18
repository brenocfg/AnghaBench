#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int pkey_index; int sched_queue; int ackto; } ;
struct mlx4_qp_context {int mtu_msgmax; TYPE_6__ alt_path; int /*<<< orphan*/  params1; TYPE_6__ pri_path; int /*<<< orphan*/  rnr_nextrecvpsn; int /*<<< orphan*/  params2; int /*<<< orphan*/  remote_qpn; int /*<<< orphan*/  next_send_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_gs; int /*<<< orphan*/  wqe_cnt; } ;
struct TYPE_7__ {scalar_t__ qp_type; } ;
struct mlx4_ib_qp {scalar_t__ state; int port; int flags; scalar_t__ sq_signal_bits; int /*<<< orphan*/  mutex; TYPE_3__ sq; TYPE_2__ rq; TYPE_1__ ibqp; int /*<<< orphan*/  mqp; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {scalar_t__ max_inline_data; int /*<<< orphan*/  max_send_sge; int /*<<< orphan*/  max_send_wr; int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_recv_wr; } ;
struct ib_qp_init_attr {int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  create_flags; TYPE_4__ cap; } ;
struct TYPE_11__ {int /*<<< orphan*/  port_num; } ;
struct ib_qp_attr {scalar_t__ qp_state; int path_mtu; int qkey; int rq_psn; int sq_psn; int dest_qp_num; int alt_pkey_index; int pkey_index; int port_num; int sq_draining; int max_rd_atomic; int max_dest_rd_atomic; int min_rnr_timer; int timeout; int retry_cnt; int rnr_retry; int alt_timeout; scalar_t__ cur_qp_state; TYPE_4__ cap; TYPE_5__ alt_ah_attr; int /*<<< orphan*/  alt_port_num; TYPE_5__ ah_attr; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  path_mig_state; } ;
struct ib_qp {int /*<<< orphan*/  uobject; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IB_QPS_INIT ; 
 scalar_t__ IB_QPS_RESET ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 int /*<<< orphan*/  IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK ; 
 int /*<<< orphan*/  IB_QP_CREATE_IPOIB_UD_LSO ; 
 int /*<<< orphan*/  IB_QP_CREATE_NETIF_QP ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 int /*<<< orphan*/  IB_SIGNAL_REQ_WR ; 
 int MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK ; 
 int MLX4_IB_QP_LSO ; 
 int MLX4_IB_QP_NETIF ; 
 int MLX4_QP_STATE_SQ_DRAINING ; 
 int /*<<< orphan*/  MLX4_WQE_CTRL_CQ_UPDATE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int mlx4_qp_query (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mlx4_qp_context*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_ib_ah_attr (struct mlx4_ib_dev*,TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  to_ib_mig_state (int) ; 
 int /*<<< orphan*/  to_ib_qp_access_flags (int) ; 
 scalar_t__ to_ib_qp_state (int) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_qp* to_mqp (struct ib_qp*) ; 

int mlx4_ib_query_qp(struct ib_qp *ibqp, struct ib_qp_attr *qp_attr, int qp_attr_mask,
		     struct ib_qp_init_attr *qp_init_attr)
{
	struct mlx4_ib_dev *dev = to_mdev(ibqp->device);
	struct mlx4_ib_qp *qp = to_mqp(ibqp);
	struct mlx4_qp_context context;
	int mlx4_state;
	int err = 0;

	mutex_lock(&qp->mutex);

	if (qp->state == IB_QPS_RESET) {
		qp_attr->qp_state = IB_QPS_RESET;
		goto done;
	}

	err = mlx4_qp_query(dev->dev, &qp->mqp, &context);
	if (err) {
		err = -EINVAL;
		goto out;
	}

	mlx4_state = be32_to_cpu(context.flags) >> 28;

	qp->state		     = to_ib_qp_state(mlx4_state);
	qp_attr->qp_state	     = qp->state;
	qp_attr->path_mtu	     = context.mtu_msgmax >> 5;
	qp_attr->path_mig_state	     =
		to_ib_mig_state((be32_to_cpu(context.flags) >> 11) & 0x3);
	qp_attr->qkey		     = be32_to_cpu(context.qkey);
	qp_attr->rq_psn		     = be32_to_cpu(context.rnr_nextrecvpsn) & 0xffffff;
	qp_attr->sq_psn		     = be32_to_cpu(context.next_send_psn) & 0xffffff;
	qp_attr->dest_qp_num	     = be32_to_cpu(context.remote_qpn) & 0xffffff;
	qp_attr->qp_access_flags     =
		to_ib_qp_access_flags(be32_to_cpu(context.params2));

	if (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC) {
		to_ib_ah_attr(dev, &qp_attr->ah_attr, &context.pri_path);
		to_ib_ah_attr(dev, &qp_attr->alt_ah_attr, &context.alt_path);
		qp_attr->alt_pkey_index = context.alt_path.pkey_index & 0x7f;
		qp_attr->alt_port_num	= qp_attr->alt_ah_attr.port_num;
	}

	qp_attr->pkey_index = context.pri_path.pkey_index & 0x7f;
	if (qp_attr->qp_state == IB_QPS_INIT)
		qp_attr->port_num = qp->port;
	else
		qp_attr->port_num = context.pri_path.sched_queue & 0x40 ? 2 : 1;

	/* qp_attr->en_sqd_async_notify is only applicable in modify qp */
	qp_attr->sq_draining = mlx4_state == MLX4_QP_STATE_SQ_DRAINING;

	qp_attr->max_rd_atomic = 1 << ((be32_to_cpu(context.params1) >> 21) & 0x7);

	qp_attr->max_dest_rd_atomic =
		1 << ((be32_to_cpu(context.params2) >> 21) & 0x7);
	qp_attr->min_rnr_timer	    =
		(be32_to_cpu(context.rnr_nextrecvpsn) >> 24) & 0x1f;
	qp_attr->timeout	    = context.pri_path.ackto >> 3;
	qp_attr->retry_cnt	    = (be32_to_cpu(context.params1) >> 16) & 0x7;
	qp_attr->rnr_retry	    = (be32_to_cpu(context.params1) >> 13) & 0x7;
	qp_attr->alt_timeout	    = context.alt_path.ackto >> 3;

done:
	qp_attr->cur_qp_state	     = qp_attr->qp_state;
	qp_attr->cap.max_recv_wr     = qp->rq.wqe_cnt;
	qp_attr->cap.max_recv_sge    = qp->rq.max_gs;

	if (!ibqp->uobject) {
		qp_attr->cap.max_send_wr  = qp->sq.wqe_cnt;
		qp_attr->cap.max_send_sge = qp->sq.max_gs;
	} else {
		qp_attr->cap.max_send_wr  = 0;
		qp_attr->cap.max_send_sge = 0;
	}

	/*
	 * We don't support inline sends for kernel QPs (yet), and we
	 * don't know what userspace's value should be.
	 */
	qp_attr->cap.max_inline_data = 0;

	qp_init_attr->cap	     = qp_attr->cap;

	qp_init_attr->create_flags = 0;
	if (qp->flags & MLX4_IB_QP_BLOCK_MULTICAST_LOOPBACK)
		qp_init_attr->create_flags |= IB_QP_CREATE_BLOCK_MULTICAST_LOOPBACK;

	if (qp->flags & MLX4_IB_QP_LSO)
		qp_init_attr->create_flags |= IB_QP_CREATE_IPOIB_UD_LSO;

	if (qp->flags & MLX4_IB_QP_NETIF)
		qp_init_attr->create_flags |= IB_QP_CREATE_NETIF_QP;

	qp_init_attr->sq_sig_type =
		qp->sq_signal_bits == cpu_to_be32(MLX4_WQE_CTRL_CQ_UPDATE) ?
		IB_SIGNAL_ALL_WR : IB_SIGNAL_REQ_WR;

out:
	mutex_unlock(&qp->mutex);
	return err;
}