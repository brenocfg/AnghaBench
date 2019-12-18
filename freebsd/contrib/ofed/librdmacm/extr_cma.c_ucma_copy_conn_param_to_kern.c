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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct ucma_abi_conn_param {int valid; int retry_count; int rnr_retry_count; scalar_t__ private_data_len; scalar_t__ private_data; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/  srq; int /*<<< orphan*/  qp_num; } ;
struct rdma_conn_param {int retry_count; int rnr_retry_count; scalar_t__ private_data_len; scalar_t__ private_data; int /*<<< orphan*/  flow_control; } ;
struct cma_id_private {scalar_t__ connect_len; scalar_t__ connect; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void ucma_copy_conn_param_to_kern(struct cma_id_private *id_priv,
					 struct ucma_abi_conn_param *dst,
					 struct rdma_conn_param *src,
					 uint32_t qp_num, uint8_t srq)
{
	dst->qp_num = qp_num;
	dst->srq = srq;
	dst->responder_resources = id_priv->responder_resources;
	dst->initiator_depth = id_priv->initiator_depth;
	dst->valid = 1;

	if (id_priv->connect_len) {
		memcpy(dst->private_data, id_priv->connect, id_priv->connect_len);
		dst->private_data_len = id_priv->connect_len;
	}

	if (src) {
		dst->flow_control = src->flow_control;
		dst->retry_count = src->retry_count;
		dst->rnr_retry_count = src->rnr_retry_count;

		if (src->private_data && src->private_data_len) {
			memcpy(dst->private_data + dst->private_data_len,
			       src->private_data, src->private_data_len);
			dst->private_data_len += src->private_data_len;
		}
	} else {
		dst->retry_count = 7;
		dst->rnr_retry_count = 7;
	}
}