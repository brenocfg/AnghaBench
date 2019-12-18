#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_6__ {int head; int /*<<< orphan*/  lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  rsn; } ;
struct mlx5_qp {int qp_cap_cache; TYPE_3__ rq; scalar_t__* db; TYPE_2__ rsc; int /*<<< orphan*/  max_tso; scalar_t__ rss_qp; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_tso; int /*<<< orphan*/  supported_qpts; } ;
struct mlx5_context {int cached_device_cap_flags; TYPE_1__ cached_tso_caps; int /*<<< orphan*/ * cached_link_layer; } ;
struct ibv_qp_attr {scalar_t__ qp_state; int /*<<< orphan*/  port_num; } ;
struct ibv_qp {int qp_type; scalar_t__ recv_cq; scalar_t__ send_cq; scalar_t__ srq; int /*<<< orphan*/  context; } ;
struct ibv_modify_qp_resp_ex {int dummy; } ;
struct ibv_modify_qp_ex {int dummy; } ;
struct ibv_modify_qp {int dummy; } ;
typedef  int /*<<< orphan*/  resp ;
typedef  int /*<<< orphan*/  cmd_ex ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int ENOSYS ; 
 int IBV_DEVICE_RAW_IP_CSUM ; 
 int /*<<< orphan*/  IBV_LINK_LAYER_ETHERNET ; 
 scalar_t__ IBV_QPS_RESET ; 
 scalar_t__ IBV_QPS_RTR ; 
#define  IBV_QPT_RAW_PACKET 128 
 int IBV_QP_PORT ; 
 int IBV_QP_STATE ; 
 int MLX5_CSUM_SUPPORT_RAW_OVER_ETH ; 
 int MLX5_MODIFY_QP_EX_ATTR_MASK ; 
 size_t MLX5_RCV_DBR ; 
 int MLX5_RX_CSUM_VALID ; 
 size_t MLX5_SND_DBR ; 
 scalar_t__ htobe32 (int) ; 
 int ibv_cmd_modify_qp (struct ibv_qp*,struct ibv_qp_attr*,int,struct ibv_modify_qp*,int) ; 
 int ibv_cmd_modify_qp_ex (struct ibv_qp*,struct ibv_qp_attr*,int,struct ibv_modify_qp_ex*,int,int,struct ibv_modify_qp_resp_ex*,int,int) ; 
 int /*<<< orphan*/  ibv_is_qpt_supported (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  mlx5_cq_clean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_init_qp_indices (struct mlx5_qp*) ; 
 int /*<<< orphan*/  mlx5_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_mcq (scalar_t__) ; 
 struct mlx5_context* to_mctx (int /*<<< orphan*/ ) ; 
 struct mlx5_qp* to_mqp (struct ibv_qp*) ; 
 int /*<<< orphan*/ * to_msrq (scalar_t__) ; 

int mlx5_modify_qp(struct ibv_qp *qp, struct ibv_qp_attr *attr,
		   int attr_mask)
{
	struct ibv_modify_qp cmd = {};
	struct ibv_modify_qp_ex cmd_ex = {};
	struct ibv_modify_qp_resp_ex resp = {};
	struct mlx5_qp *mqp = to_mqp(qp);
	struct mlx5_context *context = to_mctx(qp->context);
	int ret;
	uint32_t *db;

	if (mqp->rss_qp)
		return ENOSYS;

	if (attr_mask & IBV_QP_PORT) {
		switch (qp->qp_type) {
		case IBV_QPT_RAW_PACKET:
			if (context->cached_link_layer[attr->port_num - 1] ==
			     IBV_LINK_LAYER_ETHERNET) {
				if (context->cached_device_cap_flags &
				    IBV_DEVICE_RAW_IP_CSUM)
					mqp->qp_cap_cache |=
						MLX5_CSUM_SUPPORT_RAW_OVER_ETH |
						MLX5_RX_CSUM_VALID;

				if (ibv_is_qpt_supported(
				 context->cached_tso_caps.supported_qpts,
				 IBV_QPT_RAW_PACKET))
					mqp->max_tso =
					     context->cached_tso_caps.max_tso;
			}
			break;
		default:
			break;
		}
	}

	if (attr_mask & MLX5_MODIFY_QP_EX_ATTR_MASK)
		ret = ibv_cmd_modify_qp_ex(qp, attr, attr_mask,
					   &cmd_ex,
					   sizeof(cmd_ex), sizeof(cmd_ex),
					   &resp,
					   sizeof(resp), sizeof(resp));
	else
		ret = ibv_cmd_modify_qp(qp, attr, attr_mask,
					&cmd, sizeof(cmd));

	if (!ret		       &&
	    (attr_mask & IBV_QP_STATE) &&
	    attr->qp_state == IBV_QPS_RESET) {
		if (qp->recv_cq) {
			mlx5_cq_clean(to_mcq(qp->recv_cq), mqp->rsc.rsn,
				      qp->srq ? to_msrq(qp->srq) : NULL);
		}
		if (qp->send_cq != qp->recv_cq && qp->send_cq)
			mlx5_cq_clean(to_mcq(qp->send_cq),
				      to_mqp(qp)->rsc.rsn, NULL);

		mlx5_init_qp_indices(mqp);
		db = mqp->db;
		db[MLX5_RCV_DBR] = 0;
		db[MLX5_SND_DBR] = 0;
	}

	/*
	 * When the Raw Packet QP is in INIT state, its RQ
	 * underneath is already in RDY, which means it can
	 * receive packets. According to the IB spec, a QP can't
	 * receive packets until moved to RTR state. To achieve this,
	 * for Raw Packet QPs, we update the doorbell record
	 * once the QP is moved to RTR.
	 */
	if (!ret &&
	    (attr_mask & IBV_QP_STATE) &&
	    attr->qp_state == IBV_QPS_RTR &&
	    qp->qp_type == IBV_QPT_RAW_PACKET) {
		mlx5_spin_lock(&mqp->rq.lock);
		mqp->db[MLX5_RCV_DBR] = htobe32(mqp->rq.head & 0xffff);
		mlx5_spin_unlock(&mqp->rq.lock);
	}

	return ret;
}