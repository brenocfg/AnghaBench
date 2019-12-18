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
struct ib_qp_attr {int qp_access_flags; int /*<<< orphan*/  port_num; int /*<<< orphan*/  pkey_index; } ;
struct TYPE_6__ {TYPE_2__* port; int /*<<< orphan*/  pkey_index; } ;
struct TYPE_4__ {int state; } ;
struct cm_id_private {int /*<<< orphan*/  lock; TYPE_3__ av; int /*<<< orphan*/  responder_resources; TYPE_1__ id; } ;
struct TYPE_5__ {int /*<<< orphan*/  port_num; } ;

/* Variables and functions */
 int EINVAL ; 
 int IB_ACCESS_REMOTE_ATOMIC ; 
 int IB_ACCESS_REMOTE_READ ; 
 int IB_ACCESS_REMOTE_WRITE ; 
#define  IB_CM_ESTABLISHED 136 
#define  IB_CM_MRA_REP_RCVD 135 
#define  IB_CM_MRA_REP_SENT 134 
#define  IB_CM_MRA_REQ_RCVD 133 
#define  IB_CM_MRA_REQ_SENT 132 
#define  IB_CM_REP_RCVD 131 
#define  IB_CM_REP_SENT 130 
#define  IB_CM_REQ_RCVD 129 
#define  IB_CM_REQ_SENT 128 
 int IB_QP_ACCESS_FLAGS ; 
 int IB_QP_PKEY_INDEX ; 
 int IB_QP_PORT ; 
 int IB_QP_STATE ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cm_init_qp_init_attr(struct cm_id_private *cm_id_priv,
				struct ib_qp_attr *qp_attr,
				int *qp_attr_mask)
{
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&cm_id_priv->lock, flags);
	switch (cm_id_priv->id.state) {
	case IB_CM_REQ_SENT:
	case IB_CM_MRA_REQ_RCVD:
	case IB_CM_REQ_RCVD:
	case IB_CM_MRA_REQ_SENT:
	case IB_CM_REP_RCVD:
	case IB_CM_MRA_REP_SENT:
	case IB_CM_REP_SENT:
	case IB_CM_MRA_REP_RCVD:
	case IB_CM_ESTABLISHED:
		*qp_attr_mask = IB_QP_STATE | IB_QP_ACCESS_FLAGS |
				IB_QP_PKEY_INDEX | IB_QP_PORT;
		qp_attr->qp_access_flags = IB_ACCESS_REMOTE_WRITE;
		if (cm_id_priv->responder_resources)
			qp_attr->qp_access_flags |= IB_ACCESS_REMOTE_READ |
						    IB_ACCESS_REMOTE_ATOMIC;
		qp_attr->pkey_index = cm_id_priv->av.pkey_index;
		qp_attr->port_num = cm_id_priv->av.port->port_num;
		ret = 0;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	spin_unlock_irqrestore(&cm_id_priv->lock, flags);
	return ret;
}