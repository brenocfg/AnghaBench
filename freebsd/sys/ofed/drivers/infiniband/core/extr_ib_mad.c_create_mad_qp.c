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
struct TYPE_6__ {int /*<<< orphan*/  max_recv_sge; int /*<<< orphan*/  max_send_sge; void* max_recv_wr; void* max_send_wr; } ;
struct ib_qp_init_attr {int qp_type; int /*<<< orphan*/  event_handler; struct ib_mad_qp_info* qp_context; int /*<<< orphan*/  port_num; TYPE_1__ cap; int /*<<< orphan*/  sq_sig_type; int /*<<< orphan*/  recv_cq; int /*<<< orphan*/  send_cq; } ;
struct TYPE_10__ {void* max_active; } ;
struct TYPE_9__ {void* max_active; } ;
struct ib_mad_qp_info {TYPE_5__ recv_queue; TYPE_4__ send_queue; int /*<<< orphan*/  qp; TYPE_3__* port_priv; } ;
typedef  enum ib_qp_type { ____Placeholder_ib_qp_type } ib_qp_type ;
struct TYPE_8__ {TYPE_2__* device; int /*<<< orphan*/  pd; int /*<<< orphan*/  port_num; int /*<<< orphan*/  cq; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_MAD_RECV_REQ_MAX_SG ; 
 int /*<<< orphan*/  IB_MAD_SEND_REQ_MAX_SG ; 
 int /*<<< orphan*/  IB_SIGNAL_ALL_WR ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_spl_qp_index (int) ; 
 int /*<<< orphan*/  ib_create_qp (int /*<<< orphan*/ ,struct ib_qp_init_attr*) ; 
 void* mad_recvq_size ; 
 void* mad_sendq_size ; 
 int /*<<< orphan*/  memset (struct ib_qp_init_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qp_event_handler ; 

__attribute__((used)) static int create_mad_qp(struct ib_mad_qp_info *qp_info,
			 enum ib_qp_type qp_type)
{
	struct ib_qp_init_attr	qp_init_attr;
	int ret;

	memset(&qp_init_attr, 0, sizeof qp_init_attr);
	qp_init_attr.send_cq = qp_info->port_priv->cq;
	qp_init_attr.recv_cq = qp_info->port_priv->cq;
	qp_init_attr.sq_sig_type = IB_SIGNAL_ALL_WR;
	qp_init_attr.cap.max_send_wr = mad_sendq_size;
	qp_init_attr.cap.max_recv_wr = mad_recvq_size;
	qp_init_attr.cap.max_send_sge = IB_MAD_SEND_REQ_MAX_SG;
	qp_init_attr.cap.max_recv_sge = IB_MAD_RECV_REQ_MAX_SG;
	qp_init_attr.qp_type = qp_type;
	qp_init_attr.port_num = qp_info->port_priv->port_num;
	qp_init_attr.qp_context = qp_info;
	qp_init_attr.event_handler = qp_event_handler;
	qp_info->qp = ib_create_qp(qp_info->port_priv->pd, &qp_init_attr);
	if (IS_ERR(qp_info->qp)) {
		dev_err(&qp_info->port_priv->device->dev,
			"Couldn't create ib_mad QP%d\n",
			get_spl_qp_index(qp_type));
		ret = PTR_ERR(qp_info->qp);
		goto error;
	}
	/* Use minimum queue sizes unless the CQ is resized */
	qp_info->send_queue.max_active = mad_sendq_size;
	qp_info->recv_queue.max_active = mad_recvq_size;
	return 0;

error:
	return ret;
}