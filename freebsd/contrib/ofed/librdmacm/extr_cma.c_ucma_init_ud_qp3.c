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
struct ibv_qp_attr {scalar_t__ sq_psn; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  qkey; int /*<<< orphan*/  port_num; int /*<<< orphan*/  pkey_index; } ;
struct ibv_qp {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  pkey; } ;
struct TYPE_7__ {TYPE_1__ ibaddr; } ;
struct TYPE_8__ {TYPE_2__ addr; } ;
struct TYPE_9__ {TYPE_3__ addr; } ;
struct TYPE_10__ {int /*<<< orphan*/  port_num; TYPE_4__ route; } ;
struct cma_id_private {TYPE_5__ id; int /*<<< orphan*/  cma_dev; } ;

/* Variables and functions */
 int ERR (int) ; 
 int /*<<< orphan*/  IBV_QPS_INIT ; 
 int /*<<< orphan*/  IBV_QPS_RTR ; 
 int /*<<< orphan*/  IBV_QPS_RTS ; 
 int IBV_QP_PKEY_INDEX ; 
 int IBV_QP_PORT ; 
 int IBV_QP_QKEY ; 
 int IBV_QP_SQ_PSN ; 
 int IBV_QP_STATE ; 
 int /*<<< orphan*/  RDMA_UDP_QKEY ; 
 int ibv_modify_qp (struct ibv_qp*,struct ibv_qp_attr*,int) ; 
 int rdma_seterrno (int) ; 
 int ucma_find_pkey (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ucma_init_ud_qp3(struct cma_id_private *id_priv, struct ibv_qp *qp)
{
	struct ibv_qp_attr qp_attr;
	int ret;

	ret = ucma_find_pkey(id_priv->cma_dev, id_priv->id.port_num,
			     id_priv->id.route.addr.addr.ibaddr.pkey,
			     &qp_attr.pkey_index);
	if (ret)
		return ret;

	qp_attr.port_num = id_priv->id.port_num;
	qp_attr.qp_state = IBV_QPS_INIT;
	qp_attr.qkey = RDMA_UDP_QKEY;

	ret = ibv_modify_qp(qp, &qp_attr, IBV_QP_STATE | IBV_QP_QKEY |
					  IBV_QP_PKEY_INDEX | IBV_QP_PORT);
	if (ret)
		return ERR(ret);

	qp_attr.qp_state = IBV_QPS_RTR;
	ret = ibv_modify_qp(qp, &qp_attr, IBV_QP_STATE);
	if (ret)
		return ERR(ret);

	qp_attr.qp_state = IBV_QPS_RTS;
	qp_attr.sq_psn = 0;
	ret = ibv_modify_qp(qp, &qp_attr, IBV_QP_STATE | IBV_QP_SQ_PSN);
	return rdma_seterrno(ret);
}