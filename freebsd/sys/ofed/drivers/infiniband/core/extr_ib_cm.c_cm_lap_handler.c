#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ib_mad_send_buf {scalar_t__ mad; } ;
struct ib_cm_lap_event_param {int /*<<< orphan*/ * alternate_path; } ;
struct TYPE_12__ {struct ib_cm_lap_event_param lap_rcvd; } ;
struct TYPE_13__ {int /*<<< orphan*/ * private_data; TYPE_1__ param; } ;
struct cm_work {int /*<<< orphan*/  list; TYPE_9__* mad_recv_wc; TYPE_7__* port; TYPE_2__ cm_event; int /*<<< orphan*/ * path; } ;
struct cm_mra_msg {int dummy; } ;
struct TYPE_16__ {int /*<<< orphan*/  tid; } ;
struct cm_lap_msg {TYPE_5__ hdr; int /*<<< orphan*/  private_data; int /*<<< orphan*/  local_comm_id; int /*<<< orphan*/  remote_comm_id; } ;
struct TYPE_15__ {scalar_t__ state; int lap_state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/  alt_av; int /*<<< orphan*/  av; int /*<<< orphan*/  tid; TYPE_4__ id; int /*<<< orphan*/  private_data_len; int /*<<< orphan*/  private_data; int /*<<< orphan*/  service_timeout; } ;
struct TYPE_17__ {int /*<<< orphan*/  grh; scalar_t__ mad; } ;
struct TYPE_19__ {TYPE_6__ recv_buf; int /*<<< orphan*/  wc; } ;
struct TYPE_18__ {TYPE_3__* counter_group; } ;
struct TYPE_14__ {int /*<<< orphan*/ * counter; } ;

/* Variables and functions */
 size_t CM_LAP_COUNTER ; 
 int /*<<< orphan*/  CM_MSG_RESPONSE_OTHER ; 
 size_t CM_RECV_DUPLICATES ; 
 int EINVAL ; 
 scalar_t__ IB_CM_ESTABLISHED ; 
#define  IB_CM_LAP_IDLE 131 
#define  IB_CM_LAP_RCVD 130 
#define  IB_CM_LAP_UNINIT 129 
#define  IB_CM_MRA_LAP_SENT 128 
 int /*<<< orphan*/  IS_ERR (struct ib_mad_send_buf*) ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ib_mad_send_buf* cm_alloc_response_msg_no_ah (TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  cm_create_response_msg_ah (TYPE_7__*,TYPE_9__*,struct ib_mad_send_buf*) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_format_mra (struct cm_mra_msg*,struct cm_id_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm_format_path_from_lap (struct cm_id_private*,int /*<<< orphan*/ *,struct cm_lap_msg*) ; 
 int /*<<< orphan*/  cm_free_msg (struct ib_mad_send_buf*) ; 
 int cm_init_av_by_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct cm_id_private*) ; 
 int cm_init_av_for_response (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  ib_post_send_mad (struct ib_mad_send_buf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_lap_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_lap_msg *lap_msg;
	struct ib_cm_lap_event_param *param;
	struct ib_mad_send_buf *msg = NULL;
	int ret;

	/* todo: verify LAP request and send reject APR if invalid. */
	lap_msg = (struct cm_lap_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_id(lap_msg->remote_comm_id,
				   lap_msg->local_comm_id);
	if (!cm_id_priv)
		return -EINVAL;

	param = &work->cm_event.param.lap_rcvd;
	param->alternate_path = &work->path[0];
	cm_format_path_from_lap(cm_id_priv, param->alternate_path, lap_msg);
	work->cm_event.private_data = &lap_msg->private_data;

	spin_lock_irq(&cm_id_priv->lock);
	if (cm_id_priv->id.state != IB_CM_ESTABLISHED)
		goto unlock;

	switch (cm_id_priv->id.lap_state) {
	case IB_CM_LAP_UNINIT:
	case IB_CM_LAP_IDLE:
		break;
	case IB_CM_MRA_LAP_SENT:
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_LAP_COUNTER]);
		msg = cm_alloc_response_msg_no_ah(work->port, work->mad_recv_wc);
		if (IS_ERR(msg))
			goto unlock;

		cm_format_mra((struct cm_mra_msg *) msg->mad, cm_id_priv,
			      CM_MSG_RESPONSE_OTHER,
			      cm_id_priv->service_timeout,
			      cm_id_priv->private_data,
			      cm_id_priv->private_data_len);
		spin_unlock_irq(&cm_id_priv->lock);

		if (cm_create_response_msg_ah(work->port, work->mad_recv_wc, msg) ||
		    ib_post_send_mad(msg, NULL))
			cm_free_msg(msg);
		goto deref;
	case IB_CM_LAP_RCVD:
		atomic_long_inc(&work->port->counter_group[CM_RECV_DUPLICATES].
				counter[CM_LAP_COUNTER]);
		goto unlock;
	default:
		goto unlock;
	}

	cm_id_priv->id.lap_state = IB_CM_LAP_RCVD;
	cm_id_priv->tid = lap_msg->hdr.tid;
	ret = cm_init_av_for_response(work->port, work->mad_recv_wc->wc,
				      work->mad_recv_wc->recv_buf.grh,
				      &cm_id_priv->av);
	if (ret)
		goto unlock;
	ret = cm_init_av_by_path(param->alternate_path, &cm_id_priv->alt_av,
				 cm_id_priv);
	if (ret)
		goto unlock;
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