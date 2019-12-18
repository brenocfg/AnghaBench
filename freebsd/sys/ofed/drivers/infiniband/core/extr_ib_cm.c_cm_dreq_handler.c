#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_send_buf {scalar_t__ mad; } ;
struct TYPE_15__ {int /*<<< orphan*/ * private_data; } ;
struct cm_work {int /*<<< orphan*/  list; TYPE_8__* port; TYPE_9__* mad_recv_wc; TYPE_2__ cm_event; } ;
struct TYPE_19__ {int state; int /*<<< orphan*/  lap_state; } ;
struct TYPE_17__ {TYPE_3__* port; } ;
struct cm_id_private {scalar_t__ local_qpn; int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/  tid; TYPE_6__ id; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  msg; TYPE_4__ av; } ;
struct TYPE_20__ {int /*<<< orphan*/  tid; } ;
struct cm_dreq_msg {TYPE_7__ hdr; int /*<<< orphan*/  private_data; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  remote_comm_id; } ;
struct cm_drep_msg {int dummy; } ;
struct TYPE_14__ {scalar_t__ mad; } ;
struct TYPE_22__ {TYPE_1__ recv_buf; } ;
struct TYPE_21__ {TYPE_5__* counter_group; } ;
struct TYPE_18__ {int /*<<< orphan*/ * counter; } ;
struct TYPE_16__ {int /*<<< orphan*/  mad_agent; } ;

/* Variables and functions */
 size_t CM_DREQ_COUNTER ; 
 size_t CM_RECV_DUPLICATES ; 
 int EINVAL ; 
#define  IB_CM_DREQ_RCVD 133 
#define  IB_CM_DREQ_SENT 132 
#define  IB_CM_ESTABLISHED 131 
 int /*<<< orphan*/  IB_CM_LAP_SENT ; 
 int /*<<< orphan*/  IB_CM_MRA_LAP_RCVD ; 
#define  IB_CM_MRA_REP_RCVD 130 
#define  IB_CM_REP_SENT 129 
#define  IB_CM_TIMEWAIT 128 
 int /*<<< orphan*/  IS_ERR (struct ib_mad_send_buf*) ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_mad_send_buf* cm_alloc_response_msg_no_ah (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  cm_create_response_msg_ah (TYPE_8__*,TYPE_9__*,struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 scalar_t__ cm_dreq_get_remote_qpn (struct cm_dreq_msg*) ; 
 int /*<<< orphan*/  cm_format_drep (struct cm_drep_msg*,struct cm_id_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_free_msg (struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  cm_issue_drep (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ib_post_send_mad (struct ib_mad_send_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_dreq_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_dreq_msg *dreq_msg;
	struct ib_mad_send_buf *msg = NULL;
	int ret;

	dreq_msg = (struct cm_dreq_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(dreq_msg->remote_comm_id,
				   dreq_msg->local_comm_id);
	if (!cm_id_priv) {
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		cm_issue_drep(work->port, work->mad_recv_wc);
		return -EINVAL;
	}

	work->cm_event.private_data = &dreq_msg->private_data;

	spin_lock_irq(&cm_id_priv->lock);
	if (cm_id_priv->local_qpn != cm_dreq_get_remote_qpn(dreq_msg))
		goto unlock;

	switch (cm_id_priv->id.state) {
	case IB_CM_REP_SENT:
	case IB_CM_DREQ_SENT:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		break;
	case IB_CM_ESTABLISHED:
		if (cm_id_priv->id.lap_state == IB_CM_LAP_SENT ||
		    cm_id_priv->id.lap_state == IB_CM_MRA_LAP_RCVD)
			ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		break;
	case IB_CM_MRA_REP_RCVD:
		break;
	case IB_CM_TIMEWAIT:
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		msg = cm_alloc_response_msg_no_ah(work->port, work->mad_recv_wc);
		if (IS_ERR(msg))
			goto unlock;

		cm_format_drep((struct cm_drep_msg *) msg->mad, cm_id_priv,
			       cm_id_priv->private_data,
			       cm_id_priv->private_data_len);
		spin_unlock_irq(&cm_id_priv->lock);

		if (cm_create_response_msg_ah(work->port, work->mad_recv_wc, msg) ||
		    ib_post_send_mad(msg, NULL))
			cm_free_msg(msg);
		goto deref;
	case IB_CM_DREQ_RCVD:
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_DREQ_COUNTER]);
		goto unlock;
	default:
		goto unlock;
	}
	cm_id_priv->id.state = IB_CM_DREQ_RCVD;
	cm_id_priv->tid = dreq_msg->hdr.tid;
	ret = atomic_inc_and_test(&cm_id_priv->work_count);
	if (!ret)
		list_add_tail(&work->list, &cm_id_priv->work_list);
	spin_unlock_irq(&cm_id_priv->lock);

	if (ret)
		cm_process_work(cm_id_priv, work);
	else
		cm_deref_id(cm_id_priv);
	return 0;

unlock:	spin_unlock_irq(&cm_id_priv->lock);
deref:	cm_deref_id(cm_id_priv);
	return -EINVAL;
}