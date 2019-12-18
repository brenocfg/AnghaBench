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
typedef  TYPE_1__* ng_btsocket_sco_pcb_p ;
struct TYPE_6__ {scalar_t__ state; int flags; int /*<<< orphan*/  pcb_mtx; } ;

/* Variables and functions */
 int EINPROGRESS ; 
 int EINVAL ; 
 scalar_t__ NG_BTSOCKET_SCO_CLOSED ; 
 scalar_t__ NG_BTSOCKET_SCO_DISCONNECTING ; 
 scalar_t__ NG_BTSOCKET_SCO_OPEN ; 
 int NG_BTSOCKET_SCO_TIMO ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ng_btsocket_sco_node ; 
 int /*<<< orphan*/  ng_btsocket_sco_send_lp_discon_req (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_btsocket_sco_timeout (TYPE_1__*) ; 
 int /*<<< orphan*/  ng_btsocket_sco_untimeout (TYPE_1__*) ; 
 TYPE_1__* so2sco_pcb (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnected (struct socket*) ; 
 int /*<<< orphan*/  soisdisconnecting (struct socket*) ; 

int
ng_btsocket_sco_disconnect(struct socket *so)
{
	ng_btsocket_sco_pcb_p	pcb = so2sco_pcb(so);

	if (pcb == NULL)
		return (EINVAL);
	if (ng_btsocket_sco_node == NULL) 
		return (EINVAL);

	mtx_lock(&pcb->pcb_mtx);

	if (pcb->state == NG_BTSOCKET_SCO_DISCONNECTING) {
		mtx_unlock(&pcb->pcb_mtx);

		return (EINPROGRESS);
	}

	if (pcb->flags & NG_BTSOCKET_SCO_TIMO)
		ng_btsocket_sco_untimeout(pcb);

	if (pcb->state == NG_BTSOCKET_SCO_OPEN) {
		ng_btsocket_sco_send_lp_discon_req(pcb);

		pcb->state = NG_BTSOCKET_SCO_DISCONNECTING;
		soisdisconnecting(so);

		ng_btsocket_sco_timeout(pcb);
	} else {
		pcb->state = NG_BTSOCKET_SCO_CLOSED;
		soisdisconnected(so);
	}

	mtx_unlock(&pcb->pcb_mtx);

	return (0);
}