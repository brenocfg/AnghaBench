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
struct TYPE_2__ {scalar_t__ wqe_cnt; } ;
struct mlx4_qp {int qp_cap_cache; scalar_t__* db; TYPE_1__ rq; int /*<<< orphan*/  link_layer; } ;
struct ibv_qp_attr {scalar_t__ qp_state; int /*<<< orphan*/  port_num; } ;
struct ibv_qp {int qp_type; scalar_t__ state; scalar_t__ recv_cq; scalar_t__ send_cq; int /*<<< orphan*/  qp_num; scalar_t__ srq; int /*<<< orphan*/  context; } ;
struct ibv_port_attr {int /*<<< orphan*/  link_layer; } ;
struct ibv_modify_qp {int dummy; } ;
struct ibv_device_attr {int device_cap_flags; } ;
typedef  int /*<<< orphan*/  device_attr ;

/* Variables and functions */
 int IBV_DEVICE_RAW_IP_CSUM ; 
 int IBV_DEVICE_UD_IP_CSUM ; 
 int /*<<< orphan*/  IBV_LINK_LAYER_ETHERNET ; 
 int /*<<< orphan*/  IBV_LINK_LAYER_INFINIBAND ; 
 scalar_t__ IBV_QPS_INIT ; 
 scalar_t__ IBV_QPS_RESET ; 
#define  IBV_QPT_RAW_PACKET 129 
#define  IBV_QPT_UD 128 
 int IBV_QP_PORT ; 
 int IBV_QP_STATE ; 
 int MLX4_CSUM_SUPPORT_RAW_OVER_ETH ; 
 int MLX4_CSUM_SUPPORT_UD_OVER_IB ; 
 int MLX4_RX_CSUM_VALID ; 
 int ibv_cmd_modify_qp (struct ibv_qp*,struct ibv_qp_attr*,int,struct ibv_modify_qp*,int) ; 
 int ibv_query_device (int /*<<< orphan*/ ,struct ibv_device_attr*) ; 
 int ibv_query_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ibv_port_attr*) ; 
 int /*<<< orphan*/  memset (struct ibv_device_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlx4_cq_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx4_init_qp_indices (struct mlx4_qp*) ; 
 int /*<<< orphan*/  mlx4_qp_init_sq_ownership (struct mlx4_qp*) ; 
 int /*<<< orphan*/  to_mcq (scalar_t__) ; 
 struct mlx4_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/ * to_msrq (scalar_t__) ; 

int mlx4_modify_qp(struct ibv_qp *qp, struct ibv_qp_attr *attr,
		    int attr_mask)
{
	struct ibv_modify_qp cmd = {};
	struct ibv_port_attr port_attr;
	struct mlx4_qp *mqp = to_mqp(qp);
	struct ibv_device_attr device_attr;
	int ret;

	memset(&device_attr, 0, sizeof(device_attr));
	if (attr_mask & IBV_QP_PORT) {
		ret = ibv_query_port(qp->context, attr->port_num,
				     &port_attr);
		if (ret)
			return ret;
		mqp->link_layer = port_attr.link_layer;

		ret = ibv_query_device(qp->context, &device_attr);
		if (ret)
			return ret;

		switch(qp->qp_type) {
		case IBV_QPT_UD:
			if ((mqp->link_layer == IBV_LINK_LAYER_INFINIBAND) &&
			    (device_attr.device_cap_flags & IBV_DEVICE_UD_IP_CSUM))
				mqp->qp_cap_cache |= MLX4_CSUM_SUPPORT_UD_OVER_IB |
						MLX4_RX_CSUM_VALID;
			break;
		case IBV_QPT_RAW_PACKET:
			if ((mqp->link_layer == IBV_LINK_LAYER_ETHERNET) &&
			    (device_attr.device_cap_flags & IBV_DEVICE_RAW_IP_CSUM))
				mqp->qp_cap_cache |= MLX4_CSUM_SUPPORT_RAW_OVER_ETH |
						MLX4_RX_CSUM_VALID;
			break;
		default:
			break;
		}

	}

	if (qp->state == IBV_QPS_RESET &&
	    attr_mask & IBV_QP_STATE   &&
	    attr->qp_state == IBV_QPS_INIT) {
		mlx4_qp_init_sq_ownership(to_mqp(qp));
	}

	ret = ibv_cmd_modify_qp(qp, attr, attr_mask, &cmd, sizeof cmd);

	if (!ret		       &&
	    (attr_mask & IBV_QP_STATE) &&
	    attr->qp_state == IBV_QPS_RESET) {
		if (qp->recv_cq)
			mlx4_cq_clean(to_mcq(qp->recv_cq), qp->qp_num,
				      qp->srq ? to_msrq(qp->srq) : NULL);
		if (qp->send_cq && qp->send_cq != qp->recv_cq)
			mlx4_cq_clean(to_mcq(qp->send_cq), qp->qp_num, NULL);

		mlx4_init_qp_indices(to_mqp(qp));
		if (to_mqp(qp)->rq.wqe_cnt)
			*to_mqp(qp)->db = 0;
	}

	return ret;
}