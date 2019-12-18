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
typedef  int u8 ;
typedef  int u32 ;
struct ikev2_responder_data {int state; } ;

/* Variables and functions */
#define  CHILD_SA 133 
 int CREATE_CHILD_SA ; 
#define  IKEV2_DONE 132 
#define  IKEV2_FAILED 131 
 int IKE_SA_AUTH ; 
 int IKE_SA_INIT ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  NOTIFY 130 
#define  SA_AUTH 129 
#define  SA_INIT 128 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ikev2_validate_rx_state(struct ikev2_responder_data *data,
				   u8 exchange_type, u32 message_id)
{
	switch (data->state) {
	case SA_INIT:
		/* Expect to receive IKE_SA_INIT: HDR, SAi1, KEi, Ni */
		if (exchange_type != IKE_SA_INIT) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Exchange Type "
				   "%u in SA_INIT state", exchange_type);
			return -1;
		}
		if (message_id != 0) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Message ID %u "
				   "in SA_INIT state", message_id);
			return -1;
		}
		break;
	case SA_AUTH:
		/* Expect to receive IKE_SA_AUTH:
		 * HDR, SK {IDi, [CERT,] [CERTREQ,] [IDr,]
		 *	AUTH, SAi2, TSi, TSr}
		 */
		if (exchange_type != IKE_SA_AUTH) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Exchange Type "
				   "%u in SA_AUTH state", exchange_type);
			return -1;
		}
		if (message_id != 1) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Message ID %u "
				   "in SA_AUTH state", message_id);
			return -1;
		}
		break;
	case CHILD_SA:
		if (exchange_type != CREATE_CHILD_SA) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Exchange Type "
				   "%u in CHILD_SA state", exchange_type);
			return -1;
		}
		if (message_id != 2) {
			wpa_printf(MSG_INFO, "IKEV2: Unexpected Message ID %u "
				   "in CHILD_SA state", message_id);
			return -1;
		}
		break;
	case NOTIFY:
	case IKEV2_DONE:
	case IKEV2_FAILED:
		return -1;
	}

	return 0;
}