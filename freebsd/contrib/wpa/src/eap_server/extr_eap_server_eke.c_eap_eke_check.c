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
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_eke_data {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ COMMIT ; 
 scalar_t__ CONFIRM ; 
 scalar_t__ EAP_EKE_COMMIT ; 
 scalar_t__ EAP_EKE_CONFIRM ; 
 scalar_t__ EAP_EKE_FAILURE ; 
 scalar_t__ EAP_EKE_ID ; 
 int /*<<< orphan*/  EAP_TYPE_EKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDENTITY ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static Boolean eap_eke_check(struct eap_sm *sm, void *priv,
			     struct wpabuf *respData)
{
	struct eap_eke_data *data = priv;
	size_t len;
	const u8 *pos;
	u8 eke_exch;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_EKE, respData, &len);
	if (pos == NULL || len < 1) {
		wpa_printf(MSG_INFO, "EAP-EKE: Invalid frame");
		return TRUE;
	}

	eke_exch = *pos;
	wpa_printf(MSG_DEBUG, "EAP-EKE: Received frame: EKE-Exch=%d", eke_exch);

	if (data->state == IDENTITY && eke_exch == EAP_EKE_ID)
		return FALSE;

	if (data->state == COMMIT && eke_exch == EAP_EKE_COMMIT)
		return FALSE;

	if (data->state == CONFIRM && eke_exch == EAP_EKE_CONFIRM)
		return FALSE;

	if (eke_exch == EAP_EKE_FAILURE)
		return FALSE;

	wpa_printf(MSG_INFO, "EAP-EKE: Unexpected EKE-Exch=%d in state=%d",
		   eke_exch, data->state);

	return TRUE;
}