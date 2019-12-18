#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ib_gid {int dummy; } ib_gid ;
struct TYPE_8__ {scalar_t__ device; int /*<<< orphan*/  qp; int /*<<< orphan*/  port_num; } ;
struct rdma_id_private {int /*<<< orphan*/  qp_mutex; TYPE_4__ id; TYPE_3__* cma_dev; } ;
struct rdma_conn_param {int /*<<< orphan*/  responder_resources; } ;
struct TYPE_5__ {int /*<<< orphan*/  sgid_index; } ;
struct TYPE_6__ {TYPE_1__ grh; } ;
struct ib_qp_attr {int /*<<< orphan*/  max_dest_rd_atomic; TYPE_2__ ah_attr; int /*<<< orphan*/  qp_state; } ;
struct TYPE_7__ {scalar_t__ device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IB_QPS_INIT ; 
 int /*<<< orphan*/  IB_QPS_RTR ; 
 int ib_modify_qp (int /*<<< orphan*/ ,struct ib_qp_attr*,int) ; 
 int ib_query_gid (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,union ib_gid*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int rdma_init_qp_attr (TYPE_4__*,struct ib_qp_attr*,int*) ; 

__attribute__((used)) static int cma_modify_qp_rtr(struct rdma_id_private *id_priv,
			     struct rdma_conn_param *conn_param)
{
	struct ib_qp_attr qp_attr;
	int qp_attr_mask, ret;
	union ib_gid sgid;

	mutex_lock(&id_priv->qp_mutex);
	if (!id_priv->id.qp) {
		ret = 0;
		goto out;
	}

	/* Need to update QP attributes from default values. */
	qp_attr.qp_state = IB_QPS_INIT;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	if (ret)
		goto out;

	ret = ib_modify_qp(id_priv->id.qp, &qp_attr, qp_attr_mask);
	if (ret)
		goto out;

	qp_attr.qp_state = IB_QPS_RTR;
	ret = rdma_init_qp_attr(&id_priv->id, &qp_attr, &qp_attr_mask);
	if (ret)
		goto out;

	ret = ib_query_gid(id_priv->id.device, id_priv->id.port_num,
			   qp_attr.ah_attr.grh.sgid_index, &sgid, NULL);
	if (ret)
		goto out;

	BUG_ON(id_priv->cma_dev->device != id_priv->id.device);

	if (conn_param)
		qp_attr.max_dest_rd_atomic = conn_param->responder_resources;
	ret = ib_modify_qp(id_priv->id.qp, &qp_attr, qp_attr_mask);
out:
	mutex_unlock(&id_priv->qp_mutex);
	return ret;
}