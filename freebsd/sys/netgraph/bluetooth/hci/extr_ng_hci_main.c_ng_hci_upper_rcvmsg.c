#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  node_p ;
typedef  int /*<<< orphan*/  ng_hci_unit_p ;
typedef  int /*<<< orphan*/  item_p ;
typedef  int /*<<< orphan*/  hook_p ;
struct TYPE_3__ {int typecookie; int /*<<< orphan*/  cmd; } ;
struct TYPE_4__ {TYPE_1__ header; } ;

/* Variables and functions */
 TYPE_2__* NGI_MSG (int /*<<< orphan*/ ) ; 
#define  NGM_HCI_COOKIE 132 
#define  NGM_HCI_LP_CON_REQ 131 
#define  NGM_HCI_LP_CON_RSP 130 
#define  NGM_HCI_LP_DISCON_REQ 129 
#define  NGM_HCI_LP_QOS_REQ 128 
 int /*<<< orphan*/  NG_NODE_PRIVATE (int /*<<< orphan*/ ) ; 
 int ng_hci_default_rcvmsg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ng_hci_lp_con_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ng_hci_lp_con_rsp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ng_hci_lp_discon_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ng_hci_lp_qos_req (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ng_hci_upper_rcvmsg(node_p node, item_p item, hook_p lasthook)
{
	ng_hci_unit_p	unit = (ng_hci_unit_p) NG_NODE_PRIVATE(node);
	int		error = 0;

	switch (NGI_MSG(item)->header.typecookie) {
	case NGM_HCI_COOKIE:
		switch (NGI_MSG(item)->header.cmd) {
		case NGM_HCI_LP_CON_REQ:
			error = ng_hci_lp_con_req(unit, item, lasthook);
			break;

		case NGM_HCI_LP_DISCON_REQ: /* XXX not defined by specs */
			error = ng_hci_lp_discon_req(unit, item, lasthook);
			break;

		case NGM_HCI_LP_CON_RSP:
			error = ng_hci_lp_con_rsp(unit, item, lasthook);
			break;

		case NGM_HCI_LP_QOS_REQ:
			error = ng_hci_lp_qos_req(unit, item, lasthook);
			break;

		default:
			error = ng_hci_default_rcvmsg(node, item, lasthook);
			break;
		}
		break;

	default:
		error = ng_hci_default_rcvmsg(node, item, lasthook);
		break;
	}

	return (error);
}