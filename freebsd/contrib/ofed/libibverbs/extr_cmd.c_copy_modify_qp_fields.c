#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  raw; } ;
struct TYPE_14__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_5__ dgid; } ;
struct TYPE_15__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; TYPE_6__ grh; int /*<<< orphan*/  dlid; } ;
struct TYPE_9__ {int /*<<< orphan*/  raw; } ;
struct TYPE_10__ {int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; int /*<<< orphan*/  flow_label; TYPE_1__ dgid; } ;
struct TYPE_12__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; TYPE_2__ grh; int /*<<< orphan*/  dlid; } ;
struct ibv_qp_attr {int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  min_rnr_timer; TYPE_7__ alt_ah_attr; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  path_mtu; TYPE_4__ ah_attr; int /*<<< orphan*/  qkey; int /*<<< orphan*/  port_num; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; } ;
struct ibv_qp {int /*<<< orphan*/  handle; } ;
struct TYPE_16__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; scalar_t__ reserved; int /*<<< orphan*/  dlid; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; } ;
struct TYPE_11__ {int /*<<< orphan*/  port_num; int /*<<< orphan*/  is_global; int /*<<< orphan*/  static_rate; int /*<<< orphan*/  src_path_bits; int /*<<< orphan*/  sl; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  hop_limit; int /*<<< orphan*/  sgid_index; scalar_t__ reserved; int /*<<< orphan*/  dlid; int /*<<< orphan*/  flow_label; int /*<<< orphan*/  dgid; } ;
struct ibv_modify_qp_common {int attr_mask; scalar_t__* reserved; int /*<<< orphan*/  dest_qp_num; int /*<<< orphan*/  path_mig_state; int /*<<< orphan*/  max_dest_rd_atomic; int /*<<< orphan*/  sq_psn; int /*<<< orphan*/  min_rnr_timer; TYPE_8__ alt_dest; int /*<<< orphan*/  alt_timeout; int /*<<< orphan*/  alt_port_num; int /*<<< orphan*/  alt_pkey_index; int /*<<< orphan*/  max_rd_atomic; int /*<<< orphan*/  rq_psn; int /*<<< orphan*/  rnr_retry; int /*<<< orphan*/  retry_cnt; int /*<<< orphan*/  timeout; int /*<<< orphan*/  path_mtu; TYPE_3__ dest; int /*<<< orphan*/  qkey; int /*<<< orphan*/  port_num; int /*<<< orphan*/  pkey_index; int /*<<< orphan*/  qp_access_flags; int /*<<< orphan*/  en_sqd_async_notify; int /*<<< orphan*/  cur_qp_state; int /*<<< orphan*/  qp_state; int /*<<< orphan*/  qp_handle; } ;

/* Variables and functions */
 int IBV_QP_ACCESS_FLAGS ; 
 int IBV_QP_ALT_PATH ; 
 int IBV_QP_AV ; 
 int IBV_QP_CUR_STATE ; 
 int IBV_QP_DEST_QPN ; 
 int IBV_QP_EN_SQD_ASYNC_NOTIFY ; 
 int IBV_QP_MAX_DEST_RD_ATOMIC ; 
 int IBV_QP_MAX_QP_RD_ATOMIC ; 
 int IBV_QP_MIN_RNR_TIMER ; 
 int IBV_QP_PATH_MIG_STATE ; 
 int IBV_QP_PATH_MTU ; 
 int IBV_QP_PKEY_INDEX ; 
 int IBV_QP_PORT ; 
 int IBV_QP_QKEY ; 
 int IBV_QP_RETRY_CNT ; 
 int IBV_QP_RNR_RETRY ; 
 int IBV_QP_RQ_PSN ; 
 int IBV_QP_SQ_PSN ; 
 int IBV_QP_STATE ; 
 int IBV_QP_TIMEOUT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copy_modify_qp_fields(struct ibv_qp *qp, struct ibv_qp_attr *attr,
				  int attr_mask,
				  struct ibv_modify_qp_common *cmd)
{
	cmd->qp_handle = qp->handle;
	cmd->attr_mask = attr_mask;

	if (attr_mask & IBV_QP_STATE)
		cmd->qp_state = attr->qp_state;
	if (attr_mask & IBV_QP_CUR_STATE)
		cmd->cur_qp_state = attr->cur_qp_state;
	if (attr_mask & IBV_QP_EN_SQD_ASYNC_NOTIFY)
		cmd->en_sqd_async_notify = attr->en_sqd_async_notify;
	if (attr_mask & IBV_QP_ACCESS_FLAGS)
		cmd->qp_access_flags = attr->qp_access_flags;
	if (attr_mask & IBV_QP_PKEY_INDEX)
		cmd->pkey_index = attr->pkey_index;
	if (attr_mask & IBV_QP_PORT)
		cmd->port_num = attr->port_num;
	if (attr_mask & IBV_QP_QKEY)
		cmd->qkey = attr->qkey;

	if (attr_mask & IBV_QP_AV) {
		memcpy(cmd->dest.dgid, attr->ah_attr.grh.dgid.raw, 16);
		cmd->dest.flow_label = attr->ah_attr.grh.flow_label;
		cmd->dest.dlid = attr->ah_attr.dlid;
		cmd->dest.reserved = 0;
		cmd->dest.sgid_index = attr->ah_attr.grh.sgid_index;
		cmd->dest.hop_limit = attr->ah_attr.grh.hop_limit;
		cmd->dest.traffic_class = attr->ah_attr.grh.traffic_class;
		cmd->dest.sl = attr->ah_attr.sl;
		cmd->dest.src_path_bits = attr->ah_attr.src_path_bits;
		cmd->dest.static_rate = attr->ah_attr.static_rate;
		cmd->dest.is_global = attr->ah_attr.is_global;
		cmd->dest.port_num = attr->ah_attr.port_num;
	}

	if (attr_mask & IBV_QP_PATH_MTU)
		cmd->path_mtu = attr->path_mtu;
	if (attr_mask & IBV_QP_TIMEOUT)
		cmd->timeout = attr->timeout;
	if (attr_mask & IBV_QP_RETRY_CNT)
		cmd->retry_cnt = attr->retry_cnt;
	if (attr_mask & IBV_QP_RNR_RETRY)
		cmd->rnr_retry = attr->rnr_retry;
	if (attr_mask & IBV_QP_RQ_PSN)
		cmd->rq_psn = attr->rq_psn;
	if (attr_mask & IBV_QP_MAX_QP_RD_ATOMIC)
		cmd->max_rd_atomic = attr->max_rd_atomic;

	if (attr_mask & IBV_QP_ALT_PATH) {
		cmd->alt_pkey_index = attr->alt_pkey_index;
		cmd->alt_port_num = attr->alt_port_num;
		cmd->alt_timeout = attr->alt_timeout;

		memcpy(cmd->alt_dest.dgid, attr->alt_ah_attr.grh.dgid.raw, 16);
		cmd->alt_dest.flow_label = attr->alt_ah_attr.grh.flow_label;
		cmd->alt_dest.dlid = attr->alt_ah_attr.dlid;
		cmd->alt_dest.reserved = 0;
		cmd->alt_dest.sgid_index = attr->alt_ah_attr.grh.sgid_index;
		cmd->alt_dest.hop_limit = attr->alt_ah_attr.grh.hop_limit;
		cmd->alt_dest.traffic_class =
		    attr->alt_ah_attr.grh.traffic_class;
		cmd->alt_dest.sl = attr->alt_ah_attr.sl;
		cmd->alt_dest.src_path_bits = attr->alt_ah_attr.src_path_bits;
		cmd->alt_dest.static_rate = attr->alt_ah_attr.static_rate;
		cmd->alt_dest.is_global = attr->alt_ah_attr.is_global;
		cmd->alt_dest.port_num = attr->alt_ah_attr.port_num;
	}

	if (attr_mask & IBV_QP_MIN_RNR_TIMER)
		cmd->min_rnr_timer = attr->min_rnr_timer;
	if (attr_mask & IBV_QP_SQ_PSN)
		cmd->sq_psn = attr->sq_psn;
	if (attr_mask & IBV_QP_MAX_DEST_RD_ATOMIC)
		cmd->max_dest_rd_atomic = attr->max_dest_rd_atomic;
	if (attr_mask & IBV_QP_PATH_MIG_STATE)
		cmd->path_mig_state = attr->path_mig_state;
	if (attr_mask & IBV_QP_DEST_QPN)
		cmd->dest_qp_num = attr->dest_qp_num;

	cmd->reserved[0] = cmd->reserved[1] = 0;
}