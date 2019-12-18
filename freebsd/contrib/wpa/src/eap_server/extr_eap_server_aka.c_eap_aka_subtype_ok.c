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
struct eap_aka_data {int state; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
#define  CHALLENGE 131 
 scalar_t__ EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT ; 
 scalar_t__ EAP_AKA_SUBTYPE_CHALLENGE ; 
 scalar_t__ EAP_AKA_SUBTYPE_CLIENT_ERROR ; 
 scalar_t__ EAP_AKA_SUBTYPE_IDENTITY ; 
 scalar_t__ EAP_AKA_SUBTYPE_NOTIFICATION ; 
 scalar_t__ EAP_AKA_SUBTYPE_REAUTHENTICATION ; 
 scalar_t__ EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE ; 
 int /*<<< orphan*/  FALSE ; 
#define  IDENTITY 130 
 int /*<<< orphan*/  MSG_INFO ; 
#define  NOTIFICATION 129 
#define  REAUTH 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static Boolean eap_aka_subtype_ok(struct eap_aka_data *data, u8 subtype)
{
	if (subtype == EAP_AKA_SUBTYPE_CLIENT_ERROR ||
	    subtype == EAP_AKA_SUBTYPE_AUTHENTICATION_REJECT)
		return FALSE;

	switch (data->state) {
	case IDENTITY:
		if (subtype != EAP_AKA_SUBTYPE_IDENTITY) {
			wpa_printf(MSG_INFO, "EAP-AKA: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case CHALLENGE:
		if (subtype != EAP_AKA_SUBTYPE_CHALLENGE &&
		    subtype != EAP_AKA_SUBTYPE_SYNCHRONIZATION_FAILURE) {
			wpa_printf(MSG_INFO, "EAP-AKA: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case REAUTH:
		if (subtype != EAP_AKA_SUBTYPE_REAUTHENTICATION) {
			wpa_printf(MSG_INFO, "EAP-AKA: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	case NOTIFICATION:
		if (subtype != EAP_AKA_SUBTYPE_NOTIFICATION) {
			wpa_printf(MSG_INFO, "EAP-AKA: Unexpected response "
				   "subtype %d", subtype);
			return TRUE;
		}
		break;
	default:
		wpa_printf(MSG_INFO, "EAP-AKA: Unexpected state (%d) for "
			   "processing a response", data->state);
		return TRUE;
	}

	return FALSE;
}