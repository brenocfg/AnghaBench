#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u_int16_t ;
struct mbuf {int dummy; } ;
typedef  int /*<<< orphan*/  ng_hci_unit_p ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
#define  NG_HCI_OCF_ACCEPT_CON 149 
#define  NG_HCI_OCF_ADD_SCO_CON 148 
#define  NG_HCI_OCF_AUTH_REQ 147 
#define  NG_HCI_OCF_CHANGE_CON_LINK_KEY 146 
#define  NG_HCI_OCF_CHANGE_CON_PKT_TYPE 145 
#define  NG_HCI_OCF_CREATE_CON 144 
#define  NG_HCI_OCF_DISCON 143 
#define  NG_HCI_OCF_EXIT_PERIODIC_INQUIRY 142 
#define  NG_HCI_OCF_INQUIRY 141 
#define  NG_HCI_OCF_INQUIRY_CANCEL 140 
#define  NG_HCI_OCF_LINK_KEY_NEG_REP 139 
#define  NG_HCI_OCF_LINK_KEY_REP 138 
#define  NG_HCI_OCF_MASTER_LINK_KEY 137 
#define  NG_HCI_OCF_PERIODIC_INQUIRY 136 
#define  NG_HCI_OCF_PIN_CODE_NEG_REP 135 
#define  NG_HCI_OCF_PIN_CODE_REP 134 
#define  NG_HCI_OCF_READ_CLOCK_OFFSET 133 
#define  NG_HCI_OCF_READ_REMOTE_FEATURES 132 
#define  NG_HCI_OCF_READ_REMOTE_VER_INFO 131 
#define  NG_HCI_OCF_REJECT_CON 130 
#define  NG_HCI_OCF_REMOTE_NAME_REQ 129 
#define  NG_HCI_OCF_SET_CON_ENCRYPTION 128 

__attribute__((used)) static int
process_link_control_params(ng_hci_unit_p unit, u_int16_t ocf, 
		struct mbuf *mcp, struct mbuf *mrp)
{
	int	error  = 0;

	switch (ocf) {
	case NG_HCI_OCF_INQUIRY_CANCEL:
	case NG_HCI_OCF_PERIODIC_INQUIRY:
	case NG_HCI_OCF_EXIT_PERIODIC_INQUIRY:
	case NG_HCI_OCF_LINK_KEY_REP:
	case NG_HCI_OCF_LINK_KEY_NEG_REP: 
	case NG_HCI_OCF_PIN_CODE_REP:
	case NG_HCI_OCF_PIN_CODE_NEG_REP:
		/* These do not need post processing */
		break;

	case NG_HCI_OCF_INQUIRY:
	case NG_HCI_OCF_CREATE_CON:
	case NG_HCI_OCF_DISCON:
	case NG_HCI_OCF_ADD_SCO_CON:
	case NG_HCI_OCF_ACCEPT_CON:
	case NG_HCI_OCF_REJECT_CON:
	case NG_HCI_OCF_CHANGE_CON_PKT_TYPE:
	case NG_HCI_OCF_AUTH_REQ:
	case NG_HCI_OCF_SET_CON_ENCRYPTION:
	case NG_HCI_OCF_CHANGE_CON_LINK_KEY:
	case NG_HCI_OCF_MASTER_LINK_KEY:
	case NG_HCI_OCF_REMOTE_NAME_REQ:
	case NG_HCI_OCF_READ_REMOTE_FEATURES:
	case NG_HCI_OCF_READ_REMOTE_VER_INFO:
	case NG_HCI_OCF_READ_CLOCK_OFFSET:
	default:

		/*
		 * None of these command was supposed to generate 
		 * Command_Complete event. Instead Command_Status event 
		 * should have been generated and then appropriate event 
		 * should have been sent to indicate the final result.
		 */

		error = EINVAL;
		break;
	}

	NG_FREE_M(mcp);
	NG_FREE_M(mrp);

	return (error);
}