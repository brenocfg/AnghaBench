#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ng_mesg {scalar_t__ data; } ;
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  TYPE_2__* ng_hci_unit_con_p ;
struct TYPE_8__ {int completed; int /*<<< orphan*/  con_handle; } ;
typedef  TYPE_3__ ng_hci_sync_con_queue_ep ;
typedef  int /*<<< orphan*/ * hook_p ;
struct TYPE_7__ {scalar_t__ link_type; int /*<<< orphan*/  con_handle; } ;
struct TYPE_6__ {int /*<<< orphan*/  node; int /*<<< orphan*/ * sco; int /*<<< orphan*/ * acl; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTCONN ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  NGM_HCI_COOKIE ; 
 int /*<<< orphan*/  NGM_HCI_SYNC_CON_QUEUE ; 
 scalar_t__ NG_HCI_LINK_SCO ; 
 scalar_t__ NG_HOOK_NOT_VALID (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_MKMESSAGE (struct ng_mesg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_SEND_MSG_HOOK (int,int /*<<< orphan*/ ,struct ng_mesg*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sync_con_queue(ng_hci_unit_p unit, ng_hci_unit_con_p con, int completed)
{
	hook_p				 hook = NULL;
	struct ng_mesg			*msg = NULL;
	ng_hci_sync_con_queue_ep	*state = NULL;
	int				 error;

	hook = (con->link_type != NG_HCI_LINK_SCO)? unit->acl : unit->sco;
	if (hook == NULL || NG_HOOK_NOT_VALID(hook))
		return (ENOTCONN);

	NG_MKMESSAGE(msg, NGM_HCI_COOKIE, NGM_HCI_SYNC_CON_QUEUE,
		sizeof(*state), M_NOWAIT);
	if (msg == NULL)
		return (ENOMEM);

	state = (ng_hci_sync_con_queue_ep *)(msg->data);
	state->con_handle = con->con_handle;
	state->completed = completed;

	NG_SEND_MSG_HOOK(error, unit->node, msg, hook, 0);

	return (error);
}