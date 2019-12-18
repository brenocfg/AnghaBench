#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ng_hci_unit_p ;
struct TYPE_3__ {int /*<<< orphan*/  opcode; } ;
typedef  TYPE_1__ ng_hci_command_status_ep ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int NG_HCI_OCF (int /*<<< orphan*/ ) ; 
#define  NG_HCI_OCF_EXIT_PARK_MODE 137 
#define  NG_HCI_OCF_EXIT_SNIFF_MODE 136 
#define  NG_HCI_OCF_HOLD_MODE 135 
#define  NG_HCI_OCF_PARK_MODE 134 
#define  NG_HCI_OCF_QOS_SETUP 133 
#define  NG_HCI_OCF_READ_LINK_POLICY_SETTINGS 132 
#define  NG_HCI_OCF_ROLE_DISCOVERY 131 
#define  NG_HCI_OCF_SNIFF_MODE 130 
#define  NG_HCI_OCF_SWITCH_ROLE 129 
#define  NG_HCI_OCF_WRITE_LINK_POLICY_SETTINGS 128 

__attribute__((used)) static int
process_link_policy_status(ng_hci_unit_p unit, ng_hci_command_status_ep *ep,
		struct mbuf *mcp)
{
	int	error = 0;

	switch (NG_HCI_OCF(ep->opcode)) {
	case NG_HCI_OCF_HOLD_MODE:
	case NG_HCI_OCF_SNIFF_MODE:
	case NG_HCI_OCF_EXIT_SNIFF_MODE:
	case NG_HCI_OCF_PARK_MODE:
	case NG_HCI_OCF_EXIT_PARK_MODE:
	case NG_HCI_OCF_SWITCH_ROLE:
		/* These do not need post processing */
		break;

	case NG_HCI_OCF_QOS_SETUP:
		break;

	case NG_HCI_OCF_ROLE_DISCOVERY:
	case NG_HCI_OCF_READ_LINK_POLICY_SETTINGS:
	case NG_HCI_OCF_WRITE_LINK_POLICY_SETTINGS:
	default:

		/*
		 * None of these command was supposed to generate 
		 * Command_Status event. Instead Command_Complete event 
		 * should have been sent.
		 */

		error = EINVAL;
		break;
	}

	NG_FREE_M(mcp);

	return (error);
}