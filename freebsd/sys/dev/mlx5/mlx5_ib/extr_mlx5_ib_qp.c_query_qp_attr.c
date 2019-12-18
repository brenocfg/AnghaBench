#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_10__ {int ackto_lt; int /*<<< orphan*/  port; int /*<<< orphan*/  pkey_index; } ;
struct mlx5_qp_context {int mtu_msgmax; TYPE_5__ alt_path; int /*<<< orphan*/  params1; TYPE_5__ pri_path; int /*<<< orphan*/  rnr_nextrecvpsn; int /*<<< orphan*/  params2; int /*<<< orphan*/  log_pg_sz_remote_qpn; int /*<<< orphan*/  next_send_psn; int /*<<< orphan*/  qkey; int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {scalar_t__ qp_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  mqp; } ;
struct TYPE_7__ {TYPE_1__ base; } ;
struct mlx5_ib_qp {TYPE_3__ ibqp; int /*<<< orphan*/  state; TYPE_2__ trans_qp; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;
struct TYPE_9__ {int /*<<< orphan*/  port_num; } ;
struct ib_qp_attr {int path_mtu; int qkey; int rq_psn; int sq_psn; int dest_qp_num; int sq_draining; int max_rd_atomic; int max_dest_rd_atomic; int min_rnr_timer; int timeout; int retry_cnt; int rnr_retry; int alt_timeout; int /*<<< orphan*/  port_num; void* pkey_index; TYPE_4__ alt_ah_attr; int /*<<< orphan*/  alt_port_num; void* alt_pkey_index; TYPE_4__ ah_attr; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  path_mig_state; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IB_QPT_RC ; 
 scalar_t__ IB_QPT_UC ; 
 scalar_t__ MLX5_ADDR_OF (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int MLX5_QP_STATE_SQ_DRAINING ; 
 int MLX5_ST_SZ_BYTES (int /*<<< orphan*/ ) ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int mlx5_core_qp_query (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  qpc ; 
 int /*<<< orphan*/  query_qp_out ; 
 int /*<<< orphan*/  to_ib_ah_attr (struct mlx5_ib_dev*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  to_ib_mig_state (int) ; 
 int /*<<< orphan*/  to_ib_qp_access_flags (int) ; 
 int /*<<< orphan*/  to_ib_qp_state (int) ; 

__attribute__((used)) static int query_qp_attr(struct mlx5_ib_dev *dev, struct mlx5_ib_qp *qp,
			 struct ib_qp_attr *qp_attr)
{
	int outlen = MLX5_ST_SZ_BYTES(query_qp_out);
	struct mlx5_qp_context *context;
	int mlx5_state;
	u32 *outb;
	int err = 0;

	outb = kzalloc(outlen, GFP_KERNEL);
	if (!outb)
		return -ENOMEM;

	err = mlx5_core_qp_query(dev->mdev, &qp->trans_qp.base.mqp, outb,
				 outlen);
	if (err)
		goto out;

	/* FIXME: use MLX5_GET rather than mlx5_qp_context manual struct */
	context = (struct mlx5_qp_context *)MLX5_ADDR_OF(query_qp_out, outb, qpc);

	mlx5_state = be32_to_cpu(context->flags) >> 28;

	qp->state		     = to_ib_qp_state(mlx5_state);
	qp_attr->path_mtu	     = context->mtu_msgmax >> 5;
	qp_attr->path_mig_state	     =
		to_ib_mig_state((be32_to_cpu(context->flags) >> 11) & 0x3);
	qp_attr->qkey		     = be32_to_cpu(context->qkey);
	qp_attr->rq_psn		     = be32_to_cpu(context->rnr_nextrecvpsn) & 0xffffff;
	qp_attr->sq_psn		     = be32_to_cpu(context->next_send_psn) & 0xffffff;
	qp_attr->dest_qp_num	     = be32_to_cpu(context->log_pg_sz_remote_qpn) & 0xffffff;
	qp_attr->qp_access_flags     =
		to_ib_qp_access_flags(be32_to_cpu(context->params2));

	if (qp->ibqp.qp_type == IB_QPT_RC || qp->ibqp.qp_type == IB_QPT_UC) {
		to_ib_ah_attr(dev, &qp_attr->ah_attr, &context->pri_path);
		to_ib_ah_attr(dev, &qp_attr->alt_ah_attr, &context->alt_path);
		qp_attr->alt_pkey_index =
			be16_to_cpu(context->alt_path.pkey_index);
		qp_attr->alt_port_num	= qp_attr->alt_ah_attr.port_num;
	}

	qp_attr->pkey_index = be16_to_cpu(context->pri_path.pkey_index);
	qp_attr->port_num = context->pri_path.port;

	/* qp_attr->en_sqd_async_notify is only applicable in modify qp */
	qp_attr->sq_draining = mlx5_state == MLX5_QP_STATE_SQ_DRAINING;

	qp_attr->max_rd_atomic = 1 << ((be32_to_cpu(context->params1) >> 21) & 0x7);

	qp_attr->max_dest_rd_atomic =
		1 << ((be32_to_cpu(context->params2) >> 21) & 0x7);
	qp_attr->min_rnr_timer	    =
		(be32_to_cpu(context->rnr_nextrecvpsn) >> 24) & 0x1f;
	qp_attr->timeout	    = context->pri_path.ackto_lt >> 3;
	qp_attr->retry_cnt	    = (be32_to_cpu(context->params1) >> 16) & 0x7;
	qp_attr->rnr_retry	    = (be32_to_cpu(context->params1) >> 13) & 0x7;
	qp_attr->alt_timeout	    = context->alt_path.ackto_lt >> 3;

out:
	kfree(outb);
	return err;
}