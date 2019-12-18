#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
typedef  TYPE_1__* ng_btsocket_l2cap_pcb_p ;
struct TYPE_6__ {scalar_t__ state; int flags; int /*<<< orphan*/  pcb_mtx; int /*<<< orphan*/  token; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 scalar_t__ NG_BTSOCKET_L2CAP_CLOSED ; 
 scalar_t__ NG_BTSOCKET_L2CAP_DISCONNECTING ; 
 int NG_BTSOCKET_L2CAP_TIMO ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_l2cap_node ; 
 int ng_btsocket_l2cap_send_l2ca_discon_req (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_btsocket_l2cap_untimeout (TYPE_1__*) ; 
 TYPE_1__* so2l2cap_pcb (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnecting (struct socket*) ; 

int
ng_btsocket_l2cap_disconnect(struct socket *so)
{
	ng_btsocket_l2cap_pcb_p	pcb = so2l2cap_pcb(so);
	int			error = 0;

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_l2cap_node == NULL) 
		return (EINVAL);

	mtx_lock(&pcb->pcb_mtx);

	if (pcb->state == NG_BTSOCKET_L2CAP_DISCONNECTING) {
		mtx_unlock(&pcb->pcb_mtx);
		return (EINPROGRESS);
	}

	if (pcb->state != NG_BTSOCKET_L2CAP_CLOSED) {
		/* XXX FIXME what to do with pending request? */
		if (pcb->flags & NG_BTSOCKET_L2CAP_TIMO)
			ng_btsocket_l2cap_untimeout(pcb);

		error = ng_btsocket_l2cap_send_l2ca_discon_req(pcb->token, pcb);
		if (error == 0) {
			pcb->state = NG_BTSOCKET_L2CAP_DISCONNECTING;
			soisdisconnecting(so);

			ng_btsocket_l2cap_timeout(pcb);
		}

		/* XXX FIXME what to do if error != 0 */
	}

	mtx_unlock(&pcb->pcb_mtx);

	return (error);
}