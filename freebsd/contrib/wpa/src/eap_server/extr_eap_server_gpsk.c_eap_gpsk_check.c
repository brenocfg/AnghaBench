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
struct eap_gpsk_data {scalar_t__ state; } ;
typedef  int /*<<< orphan*/  Boolean ;

/* Variables and functions */
 scalar_t__ const EAP_GPSK_OPCODE_GPSK_2 ; 
 scalar_t__ const EAP_GPSK_OPCODE_GPSK_4 ; 
 int /*<<< orphan*/  EAP_TYPE_GPSK ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GPSK_1 ; 
 scalar_t__ GPSK_3 ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static Boolean eap_gpsk_check(struct eap_sm *sm, void *priv,
			      struct wpabuf *respData)
{
	struct eap_gpsk_data *data = priv;
	const u8 *pos;
	size_t len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_GPSK, respData, &len);
	if (pos == NULL || len < 1) {
		wpa_printf(MSG_INFO, "EAP-GPSK: Invalid frame");
		return TRUE;
	}

	wpa_printf(MSG_DEBUG, "EAP-GPSK: Received frame: opcode=%d", *pos);

	if (data->state == GPSK_1 && *pos == EAP_GPSK_OPCODE_GPSK_2)
		return FALSE;

	if (data->state == GPSK_3 && *pos == EAP_GPSK_OPCODE_GPSK_4)
		return FALSE;

	wpa_printf(MSG_INFO, "EAP-GPSK: Unexpected opcode=%d in state=%d",
		   *pos, data->state);

	return TRUE;
}