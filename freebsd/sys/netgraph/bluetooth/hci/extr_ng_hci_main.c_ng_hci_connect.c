#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  scalar_t__ hook_p ;
struct TYPE_2__ {scalar_t__ drv; scalar_t__ acl; scalar_t__ sco; scalar_t__ raw; int /*<<< orphan*/  state; int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  NG_HCI_UNIT_CONNECTED ; 
 int /*<<< orphan*/  NG_HOOK_NODE (scalar_t__) ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVDATA (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_HOOK_SET_RCVMSG (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ng_hci_acl_rcvdata ; 
 int /*<<< orphan*/  ng_hci_node_is_up ; 
 int /*<<< orphan*/  ng_hci_raw_rcvdata ; 
 int /*<<< orphan*/  ng_hci_sco_rcvdata ; 
 int /*<<< orphan*/  ng_hci_upper_rcvmsg ; 
 int /*<<< orphan*/  ng_send_fn (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_hci_connect(hook_p hook)
{
	ng_hci_unit_p	unit = (ng_hci_unit_p) NG_NODE_PRIVATE(NG_HOOK_NODE(hook));

	if (hook != unit->drv) {
		if (hook == unit->acl) {
			NG_HOOK_SET_RCVMSG(hook, ng_hci_upper_rcvmsg);
			NG_HOOK_SET_RCVDATA(hook, ng_hci_acl_rcvdata);
		} else if (hook == unit->sco) {
			NG_HOOK_SET_RCVMSG(hook, ng_hci_upper_rcvmsg);
			NG_HOOK_SET_RCVDATA(hook, ng_hci_sco_rcvdata);
		} else
			NG_HOOK_SET_RCVDATA(hook, ng_hci_raw_rcvdata);

		/* Send delayed notification to the upper layers */
		if (hook != unit->raw) 
			ng_send_fn(unit->node, hook, ng_hci_node_is_up, NULL,0);
	} else
		unit->state |= NG_HCI_UNIT_CONNECTED;

	return (0);
}