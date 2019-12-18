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
struct cm_work {int /*<<< orphan*/  list; TYPE_2__* mad_recv_wc; } ;
struct cm_rej_msg {int /*<<< orphan*/  reason; } ;
struct TYPE_10__ {TYPE_4__* port; } ;
struct TYPE_8__ {int state; int /*<<< orphan*/  lap_state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; int /*<<< orphan*/  work_list; int /*<<< orphan*/  work_count; int /*<<< orphan*/  msg; TYPE_5__ av; TYPE_3__ id; } ;
struct TYPE_9__ {int /*<<< orphan*/  mad_agent; } ;
struct TYPE_6__ {scalar_t__ mad; } ;
struct TYPE_7__ {TYPE_1__ recv_buf; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IB_CM_DREQ_SENT 137 
#define  IB_CM_ESTABLISHED 136 
 int /*<<< orphan*/  IB_CM_LAP_SENT ; 
 int /*<<< orphan*/  IB_CM_LAP_UNINIT ; 
#define  IB_CM_MRA_REP_RCVD 135 
#define  IB_CM_MRA_REP_SENT 134 
#define  IB_CM_MRA_REQ_RCVD 133 
#define  IB_CM_MRA_REQ_SENT 132 
 int /*<<< orphan*/  IB_CM_REJ_STALE_CONN ; 
#define  IB_CM_REP_RCVD 131 
#define  IB_CM_REP_SENT 130 
#define  IB_CM_REQ_RCVD 129 
#define  IB_CM_REQ_SENT 128 
 int /*<<< orphan*/  __be16_to_cpu (int /*<<< orphan*/ ) ; 
 int atomic_inc_and_test (int /*<<< orphan*/ *) ; 
 struct cm_id_private* cm_acquire_rejected_id (struct cm_rej_msg*) ; 
 int /*<<< orphan*/  cm_deref_id (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_enter_timewait (struct cm_id_private*) ; 
 int /*<<< orphan*/  cm_format_rej_event (struct cm_work*) ; 
 int /*<<< orphan*/  cm_process_work (struct cm_id_private*,struct cm_work*) ; 
 int /*<<< orphan*/  cm_reset_to_idle (struct cm_id_private*) ; 
 int /*<<< orphan*/  ib_cancel_mad (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm_rej_handler(struct cm_work *work)
{
	struct cm_id_private *cm_id_priv;
	struct cm_rej_msg *rej_msg;
	int ret;

	rej_msg = (struct cm_rej_msg *)work->mad_recv_wc->recv_buf.mad;
	cm_id_priv = cm_acquire_rejected_id(rej_msg);
	if (!cm_id_priv)
		return -EINVAL;

	cm_format_rej_event(work);

	spin_lock_irq(&cm_id_priv->lock);
	switch (cm_id_priv->id.state) {
	case IB_CM_REQ_SENT:
	case IB_CM_MRA_REQ_RCVD:
	case IB_CM_REP_SENT:
	case IB_CM_MRA_REP_RCVD:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		/* fall through */
	case IB_CM_REQ_RCVD:
	case IB_CM_MRA_REQ_SENT:
		if (__be16_to_cpu(rej_msg->reason) == IB_CM_REJ_STALE_CONN)
			cm_enter_timewait(cm_id_priv);
		else
			cm_reset_to_idle(cm_id_priv);
		break;
	case IB_CM_DREQ_SENT:
		ib_cancel_mad(cm_id_priv->av.port->mad_agent, cm_id_priv->msg);
		/* fall through */
	case IB_CM_REP_RCVD:
	case IB_CM_MRA_REP_SENT:
		cm_enter_timewait(cm_id_priv);
		break;
	case IB_CM_ESTABLISHED:
		if (cm_id_priv->id.lap_state == IB_CM_LAP_UNINIT ||
		    cm_id_priv->id.lap_state == IB_CM_LAP_SENT) {
			if (cm_id_priv->id.lap_state == IB_CM_LAP_SENT)
				ib_cancel_mad(cm_id_priv->av.port->mad_agent,
					      cm_id_priv->msg);
			cm_enter_timewait(cm_id_priv);
			break;
		}
		/* fall through */
	default:
		spin_unlock_irq(&cm_id_priv->lock);
		ret = -EINVAL;
		goto out;
	}

	ret = atomic_inc_and_test(&cm_id_priv->work_count);
	if (!ret)
		list_add_tail(&work->list, &cm_id_priv->work_list);
	spin_unlock_irq(&cm_id_priv->lock);

	if (ret)
		cm_process_work(cm_id_priv, work);
	else
		cm_deref_id(cm_id_priv);
	return 0;
out:
	cm_deref_id(cm_id_priv);
	return -EINVAL;
}