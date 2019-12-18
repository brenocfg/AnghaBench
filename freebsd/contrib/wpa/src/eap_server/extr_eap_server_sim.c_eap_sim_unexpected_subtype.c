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
typedef  scalar_t__ u8 ;
struct eap_sim_data {int state; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
#define  CHALLENGE 131 
 scalar_t__ EAP_SIM_SUBTYPE_CHALLENGE ; 
 scalar_t__ EAP_SIM_SUBTYPE_CLIENT_ERROR ; 
 scalar_t__ EAP_SIM_SUBTYPE_NOTIFICATION ; 
 scalar_t__ EAP_SIM_SUBTYPE_REAUTHENTICATION ; 
 scalar_t__ EAP_SIM_SUBTYPE_START ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_INFO ; 
#define  NOTIFICATION 130 
#define  REAUTH 129 
#define  START 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static Boolean eap_sim_unexpected_subtype(struct eap_sim_data *data,
					  u8 subtype)
{
	if (subtype == EAP_SIM_SUBTYPE_CLIENT_ERROR)
		return FALSE;

	switch (data->state) {
	case START:
		if (subtype != EAP_SIM_SUBTYPE_START) {
			wpa_printf(MSG_INFO, "EAP-SIM: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case CHALLENGE:
		if (subtype != EAP_SIM_SUBTYPE_CHALLENGE) {
			wpa_printf(MSG_INFO, "EAP-SIM: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case REAUTH:
		if (subtype != EAP_SIM_SUBTYPE_REAUTHENTICATION) {
			wpa_printf(MSG_INFO, "EAP-SIM: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case NOTIFICATION:
		if (subtype != EAP_SIM_SUBTYPE_NOTIFICATION) {
			wpa_printf(MSG_INFO, "EAP-SIM: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	default:
		wpa_printf(MSG_INFO, "EAP-SIM: Unexpected state (%d) for "
			   "processing a response", data->state);
		return TRUE;
	}

	return FALSE;
}