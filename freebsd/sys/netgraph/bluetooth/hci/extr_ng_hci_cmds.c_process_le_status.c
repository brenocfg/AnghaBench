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
#define  NG_HCI_OCF_LE_ADD_DEVICE_TO_WHITE_LIST 157 
#define  NG_HCI_OCF_LE_CLEAR_WHITE_LIST 156 
#define  NG_HCI_OCF_LE_CONNECTION_UPDATE 155 
#define  NG_HCI_OCF_LE_CREATE_CONNECTION 154 
#define  NG_HCI_OCF_LE_CREATE_CONNECTION_CANCEL 153 
#define  NG_HCI_OCF_LE_ENCRYPT 152 
#define  NG_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY 151 
#define  NG_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY 150 
#define  NG_HCI_OCF_LE_RAND 149 
#define  NG_HCI_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER 148 
#define  NG_HCI_OCF_LE_READ_BUFFER_SIZE 147 
#define  NG_HCI_OCF_LE_READ_CHANNEL_MAP 146 
#define  NG_HCI_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES 145 
#define  NG_HCI_OCF_LE_READ_REMOTE_USED_FEATURES 144 
#define  NG_HCI_OCF_LE_READ_SUPPORTED_STATUS 143 
#define  NG_HCI_OCF_LE_READ_WHITE_LIST_SIZE 142 
#define  NG_HCI_OCF_LE_RECEIVER_TEST 141 
#define  NG_HCI_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST 140 
#define  NG_HCI_OCF_LE_SET_ADVERTISE_ENABLE 139 
#define  NG_HCI_OCF_LE_SET_ADVERTISING_DATA 138 
#define  NG_HCI_OCF_LE_SET_ADVERTISING_PARAMETERS 137 
#define  NG_HCI_OCF_LE_SET_EVENT_MASK 136 
#define  NG_HCI_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION 135 
#define  NG_HCI_OCF_LE_SET_RANDOM_ADDRESS 134 
#define  NG_HCI_OCF_LE_SET_SCAN_ENABLE 133 
#define  NG_HCI_OCF_LE_SET_SCAN_PARAMETERS 132 
#define  NG_HCI_OCF_LE_SET_SCAN_RESPONSE_DATA 131 
#define  NG_HCI_OCF_LE_START_ENCRYPTION 130 
#define  NG_HCI_OCF_LE_TEST_END 129 
#define  NG_HCI_OCF_LE_TRANSMITTER_TEST 128 

__attribute__((used)) static int
process_le_status(ng_hci_unit_p unit,ng_hci_command_status_ep *ep,
		struct mbuf *mcp)
{
	int	error = 0;

	switch (NG_HCI_OCF(ep->opcode)){
	case NG_HCI_OCF_LE_CREATE_CONNECTION:
	case NG_HCI_OCF_LE_CONNECTION_UPDATE:
	case NG_HCI_OCF_LE_READ_REMOTE_USED_FEATURES:
	case NG_HCI_OCF_LE_START_ENCRYPTION:

		/* These do not need post processing */
		break;

	case NG_HCI_OCF_LE_SET_EVENT_MASK:
	case NG_HCI_OCF_LE_READ_BUFFER_SIZE:
	case NG_HCI_OCF_LE_READ_LOCAL_SUPPORTED_FEATURES:
	case NG_HCI_OCF_LE_SET_RANDOM_ADDRESS:
	case NG_HCI_OCF_LE_SET_ADVERTISING_PARAMETERS:
	case NG_HCI_OCF_LE_READ_ADVERTISING_CHANNEL_TX_POWER:
	case NG_HCI_OCF_LE_SET_ADVERTISING_DATA:
	case NG_HCI_OCF_LE_SET_SCAN_RESPONSE_DATA:
	case NG_HCI_OCF_LE_SET_ADVERTISE_ENABLE:
	case NG_HCI_OCF_LE_SET_SCAN_PARAMETERS:
	case NG_HCI_OCF_LE_SET_SCAN_ENABLE:
	case NG_HCI_OCF_LE_CREATE_CONNECTION_CANCEL:
	case NG_HCI_OCF_LE_CLEAR_WHITE_LIST:
	case NG_HCI_OCF_LE_READ_WHITE_LIST_SIZE:
	case NG_HCI_OCF_LE_ADD_DEVICE_TO_WHITE_LIST:
	case NG_HCI_OCF_LE_REMOVE_DEVICE_FROM_WHITE_LIST:
	case NG_HCI_OCF_LE_SET_HOST_CHANNEL_CLASSIFICATION:
	case NG_HCI_OCF_LE_READ_CHANNEL_MAP:
	case NG_HCI_OCF_LE_ENCRYPT:
	case NG_HCI_OCF_LE_RAND:
	case NG_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_REPLY:
	case NG_HCI_OCF_LE_LONG_TERM_KEY_REQUEST_NEGATIVE_REPLY:
	case NG_HCI_OCF_LE_READ_SUPPORTED_STATUS:
	case NG_HCI_OCF_LE_RECEIVER_TEST:
	case NG_HCI_OCF_LE_TRANSMITTER_TEST:
	case NG_HCI_OCF_LE_TEST_END:


	default:
		/*
		 * None of these command was supposed to generate 
		 * Command_Stutus event. Command Complete instead.
		 */

		error = EINVAL;
		break;
	} 

	NG_FREE_M(mcp);

	return (error);

}