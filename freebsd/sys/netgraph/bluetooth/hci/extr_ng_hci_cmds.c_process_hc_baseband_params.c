#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int16_t ;
struct mbuf {int dummy; } ;
typedef  TYPE_1__* ng_hci_unit_p ;
typedef  TYPE_2__* ng_hci_unit_con_p ;
struct TYPE_9__ {int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; int /*<<< orphan*/  buffer; int /*<<< orphan*/  con_list; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 TYPE_2__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NG_FREE_M (struct mbuf*) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_ACL_FREE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_ACL_TOTAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_SCO_FREE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NG_HCI_BUFF_SCO_TOTAL (int /*<<< orphan*/ ,int) ; 
 int NG_HCI_CON_TIMEOUT_PENDING ; 
#define  NG_HCI_OCF_CHANGE_LOCAL_NAME 180 
#define  NG_HCI_OCF_CREATE_NEW_UNIT_KEY 179 
#define  NG_HCI_OCF_DELETE_STORED_LINK_KEY 178 
#define  NG_HCI_OCF_FLUSH 177 
#define  NG_HCI_OCF_H2HC_FLOW_CONTROL 176 
#define  NG_HCI_OCF_HOST_BUFFER_SIZE 175 
#define  NG_HCI_OCF_HOST_NUM_COMPL_PKTS 174 
#define  NG_HCI_OCF_READ_AUTH_ENABLE 173 
#define  NG_HCI_OCF_READ_AUTO_FLUSH_TIMO 172 
#define  NG_HCI_OCF_READ_CON_ACCEPT_TIMO 171 
#define  NG_HCI_OCF_READ_ENCRYPTION_MODE 170 
#define  NG_HCI_OCF_READ_HOLD_MODE_ACTIVITY 169 
#define  NG_HCI_OCF_READ_IAC_LAP 168 
#define  NG_HCI_OCF_READ_INQUIRY_SCAN_ACTIVITY 167 
#define  NG_HCI_OCF_READ_LE_HOST_SUPPORTED 166 
#define  NG_HCI_OCF_READ_LINK_SUPERVISION_TIMO 165 
#define  NG_HCI_OCF_READ_LOCAL_NAME 164 
#define  NG_HCI_OCF_READ_NUM_BROADCAST_RETRANS 163 
#define  NG_HCI_OCF_READ_PAGE_SCAN 162 
#define  NG_HCI_OCF_READ_PAGE_SCAN_ACTIVITY 161 
#define  NG_HCI_OCF_READ_PAGE_SCAN_PERIOD 160 
#define  NG_HCI_OCF_READ_PAGE_TIMO 159 
#define  NG_HCI_OCF_READ_PIN_TYPE 158 
#define  NG_HCI_OCF_READ_SCAN_ENABLE 157 
#define  NG_HCI_OCF_READ_SCO_FLOW_CONTROL 156 
#define  NG_HCI_OCF_READ_STORED_LINK_KEY 155 
#define  NG_HCI_OCF_READ_SUPPORTED_IAC_NUM 154 
#define  NG_HCI_OCF_READ_UNIT_CLASS 153 
#define  NG_HCI_OCF_READ_VOICE_SETTINGS 152 
#define  NG_HCI_OCF_READ_XMIT_LEVEL 151 
#define  NG_HCI_OCF_RESET 150 
#define  NG_HCI_OCF_SET_EVENT_FILTER 149 
#define  NG_HCI_OCF_SET_EVENT_MASK 148 
#define  NG_HCI_OCF_WRITE_AUTH_ENABLE 147 
#define  NG_HCI_OCF_WRITE_AUTO_FLUSH_TIMO 146 
#define  NG_HCI_OCF_WRITE_CON_ACCEPT_TIMO 145 
#define  NG_HCI_OCF_WRITE_ENCRYPTION_MODE 144 
#define  NG_HCI_OCF_WRITE_HOLD_MODE_ACTIVITY 143 
#define  NG_HCI_OCF_WRITE_IAC_LAP 142 
#define  NG_HCI_OCF_WRITE_INQUIRY_SCAN_ACTIVITY 141 
#define  NG_HCI_OCF_WRITE_LE_HOST_SUPPORTED 140 
#define  NG_HCI_OCF_WRITE_LINK_SUPERVISION_TIMO 139 
#define  NG_HCI_OCF_WRITE_NUM_BROADCAST_RETRANS 138 
#define  NG_HCI_OCF_WRITE_PAGE_SCAN 137 
#define  NG_HCI_OCF_WRITE_PAGE_SCAN_ACTIVITY 136 
#define  NG_HCI_OCF_WRITE_PAGE_SCAN_PERIOD 135 
#define  NG_HCI_OCF_WRITE_PAGE_TIMO 134 
#define  NG_HCI_OCF_WRITE_PIN_TYPE 133 
#define  NG_HCI_OCF_WRITE_SCAN_ENABLE 132 
#define  NG_HCI_OCF_WRITE_SCO_FLOW_CONTROL 131 
#define  NG_HCI_OCF_WRITE_STORED_LINK_KEY 130 
#define  NG_HCI_OCF_WRITE_UNIT_CLASS 129 
#define  NG_HCI_OCF_WRITE_VOICE_SETTINGS 128 
 int /*<<< orphan*/  NG_HCI_UNIT_INITED ; 
 int /*<<< orphan*/  ng_hci_con_untimeout (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_hci_free_con (TYPE_2__*) ; 
 int /*<<< orphan*/  ng_hci_lp_discon_ind (TYPE_2__*,int) ; 

int
process_hc_baseband_params(ng_hci_unit_p unit, u_int16_t ocf, 
		struct mbuf *mcp, struct mbuf *mrp)
{
	int	error = 0;

	switch (ocf) {
	case NG_HCI_OCF_SET_EVENT_MASK:
	case NG_HCI_OCF_SET_EVENT_FILTER:
	case NG_HCI_OCF_FLUSH:	/* XXX Do we need to handle that? */
	case NG_HCI_OCF_READ_PIN_TYPE:
	case NG_HCI_OCF_WRITE_PIN_TYPE:
	case NG_HCI_OCF_CREATE_NEW_UNIT_KEY:
	case NG_HCI_OCF_WRITE_STORED_LINK_KEY:
	case NG_HCI_OCF_WRITE_CON_ACCEPT_TIMO:
	case NG_HCI_OCF_WRITE_PAGE_TIMO:
	case NG_HCI_OCF_READ_SCAN_ENABLE:
	case NG_HCI_OCF_WRITE_SCAN_ENABLE:
	case NG_HCI_OCF_WRITE_PAGE_SCAN_ACTIVITY:
	case NG_HCI_OCF_WRITE_INQUIRY_SCAN_ACTIVITY:
	case NG_HCI_OCF_READ_AUTH_ENABLE:
	case NG_HCI_OCF_WRITE_AUTH_ENABLE:
	case NG_HCI_OCF_READ_ENCRYPTION_MODE:
	case NG_HCI_OCF_WRITE_ENCRYPTION_MODE:
	case NG_HCI_OCF_WRITE_VOICE_SETTINGS:
	case NG_HCI_OCF_READ_NUM_BROADCAST_RETRANS:
	case NG_HCI_OCF_WRITE_NUM_BROADCAST_RETRANS:
	case NG_HCI_OCF_READ_HOLD_MODE_ACTIVITY:
	case NG_HCI_OCF_WRITE_HOLD_MODE_ACTIVITY:
	case NG_HCI_OCF_READ_SCO_FLOW_CONTROL:
	case NG_HCI_OCF_WRITE_SCO_FLOW_CONTROL:
	case NG_HCI_OCF_H2HC_FLOW_CONTROL: /* XXX Not supported this time */
	case NG_HCI_OCF_HOST_BUFFER_SIZE:
	case NG_HCI_OCF_READ_IAC_LAP:
	case NG_HCI_OCF_WRITE_IAC_LAP:
	case NG_HCI_OCF_READ_PAGE_SCAN_PERIOD:
	case NG_HCI_OCF_WRITE_PAGE_SCAN_PERIOD:
	case NG_HCI_OCF_READ_PAGE_SCAN:
	case NG_HCI_OCF_WRITE_PAGE_SCAN:
	case NG_HCI_OCF_READ_LINK_SUPERVISION_TIMO:
	case NG_HCI_OCF_WRITE_LINK_SUPERVISION_TIMO:
	case NG_HCI_OCF_READ_SUPPORTED_IAC_NUM:
	case NG_HCI_OCF_READ_STORED_LINK_KEY:
	case NG_HCI_OCF_DELETE_STORED_LINK_KEY:
	case NG_HCI_OCF_READ_CON_ACCEPT_TIMO:
	case NG_HCI_OCF_READ_PAGE_TIMO:
	case NG_HCI_OCF_READ_PAGE_SCAN_ACTIVITY:
	case NG_HCI_OCF_READ_INQUIRY_SCAN_ACTIVITY:
	case NG_HCI_OCF_READ_VOICE_SETTINGS:
	case NG_HCI_OCF_READ_AUTO_FLUSH_TIMO:
	case NG_HCI_OCF_WRITE_AUTO_FLUSH_TIMO:
	case NG_HCI_OCF_READ_XMIT_LEVEL:
	case NG_HCI_OCF_HOST_NUM_COMPL_PKTS:	/* XXX Can get here? */
	case NG_HCI_OCF_CHANGE_LOCAL_NAME:
	case NG_HCI_OCF_READ_LOCAL_NAME:
	case NG_HCI_OCF_READ_UNIT_CLASS:
	case NG_HCI_OCF_WRITE_UNIT_CLASS:
	case NG_HCI_OCF_READ_LE_HOST_SUPPORTED:
	case NG_HCI_OCF_WRITE_LE_HOST_SUPPORTED:
		/* These do not need post processing */
		break;

	case NG_HCI_OCF_RESET: {
		ng_hci_unit_con_p	con = NULL;
		int			size;

		/*
		 * XXX 
		 *
		 * After RESET command unit goes into standby mode
		 * and all operational state is lost. Host controller
		 * will revert to default values for all parameters.
		 * 
		 * For now we shall terminate all connections and drop
		 * inited bit. After RESET unit must be re-initialized.
		 */

		while (!LIST_EMPTY(&unit->con_list)) {
			con = LIST_FIRST(&unit->con_list);

			/* Remove all timeouts (if any) */
			if (con->flags & NG_HCI_CON_TIMEOUT_PENDING)
				ng_hci_con_untimeout(con);

			/* Connection terminated by local host */
			ng_hci_lp_discon_ind(con, 0x16);
			ng_hci_free_con(con);
		}

		NG_HCI_BUFF_ACL_TOTAL(unit->buffer, size);
		NG_HCI_BUFF_ACL_FREE(unit->buffer, size);

		NG_HCI_BUFF_SCO_TOTAL(unit->buffer, size);
		NG_HCI_BUFF_SCO_FREE(unit->buffer, size);

		unit->state &= ~NG_HCI_UNIT_INITED;
		} break;

	default:
		error = EINVAL;
		break;
	}

	NG_FREE_M(mcp);
	NG_FREE_M(mrp);

	return (error);
}