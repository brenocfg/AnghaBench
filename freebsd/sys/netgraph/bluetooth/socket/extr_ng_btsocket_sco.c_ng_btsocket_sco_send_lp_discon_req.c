#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ng_mesg {scalar_t__ data; } ;
struct TYPE_6__ {int reason; int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_2__ ng_hci_lp_discon_req_ep ;
typedef  TYPE_3__* ng_btsocket_sco_pcb_p ;
struct TYPE_7__ {TYPE_1__* rt; int /*<<< orphan*/  con_handle; int /*<<< orphan*/  pcb_mtx; } ;
struct TYPE_5__ {int /*<<< orphan*/ * hook; } ;

/* Variables and functions */
 int ENETDOWN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_HCI_COOKIE ; 
 int /*<<< orphan*/  NGM_HCI_LP_DISCON_REQ ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_btsocket_sco_node ; 

__attribute__((used)) static int
ng_btsocket_sco_send_lp_discon_req(ng_btsocket_sco_pcb_p pcb)
{
	struct ng_mesg		*msg = NULL;
	ng_hci_lp_discon_req_ep	*ep = NULL;
	int			 error = 0;

	mtx_assert(&pcb->pcb_mtx, MA_OWNED);

	if (pcb->rt == NULL || 
	    pcb->rt->hook == NULL || NG_HOOK_NOT_VALID(pcb->rt->hook))
		return (ENETDOWN); 

	NG_MKMESSAGE(msg, NGM_HCI_COOKIE, NGM_HCI_LP_DISCON_REQ,
		sizeof(*ep), M_NOWAIT);
	if (msg == NULL)
		return (ENOMEM);

	ep = (ng_hci_lp_discon_req_ep *)(msg->data);
	ep->con_handle = pcb->con_handle;
	ep->reason = 0x13; /* User Ended Connection */

	NG_SEND_MSG_HOOK(error, ng_btsocket_sco_node, msg, pcb->rt->hook, 0);

	return (error);
}