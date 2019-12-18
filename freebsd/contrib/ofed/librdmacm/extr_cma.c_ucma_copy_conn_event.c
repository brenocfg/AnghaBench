#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ucma_abi_conn_param {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; scalar_t__ private_data_len; int /*<<< orphan*/  private_data; } ;
struct rdma_conn_param {int /*<<< orphan*/  qp_num; int /*<<< orphan*/  srq; int /*<<< orphan*/  rnr_retry_count; int /*<<< orphan*/  retry_count; int /*<<< orphan*/  flow_control; int /*<<< orphan*/  initiator_depth; int /*<<< orphan*/  responder_resources; int /*<<< orphan*/ * private_data; scalar_t__ private_data_len; } ;
struct TYPE_3__ {struct rdma_conn_param conn; } ;
struct TYPE_4__ {TYPE_1__ param; } ;
struct cma_event {int /*<<< orphan*/  private_data; TYPE_2__ event; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ucma_copy_conn_event(struct cma_event *event,
				 struct ucma_abi_conn_param *src)
{
	struct rdma_conn_param *dst = &event->event.param.conn;

	dst->private_data_len = src->private_data_len;
	if (src->private_data_len) {
		dst->private_data = &event->private_data;
		memcpy(&event->private_data, src->private_data,
		       src->private_data_len);
	}

	dst->responder_resources = src->responder_resources;
	dst->initiator_depth = src->initiator_depth;
	dst->flow_control = src->flow_control;
	dst->retry_count = src->retry_count;
	dst->rnr_retry_count = src->rnr_retry_count;
	dst->srq = src->srq;
	dst->qp_num = src->qp_num;
}