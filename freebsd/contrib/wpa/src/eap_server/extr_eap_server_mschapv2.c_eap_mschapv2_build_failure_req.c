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
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_mschapv2_hdr {int /*<<< orphan*/  ms_length; int /*<<< orphan*/  mschapv2_id; int /*<<< orphan*/  op_code; } ;
struct eap_mschapv2_data {int /*<<< orphan*/  resp_mschapv2_id; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  EAP_TYPE_MSCHAPV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSCHAPV2_OP_FAILURE ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_MSGDUMP ; 
 int /*<<< orphan*/  WPA_PUT_BE16 (int /*<<< orphan*/ ,size_t) ; 
 struct wpabuf* eap_msg_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int os_strlen (char*) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct eap_mschapv2_hdr* wpabuf_put (struct wpabuf*,int) ; 
 int /*<<< orphan*/  wpabuf_put_data (struct wpabuf*,char*,int) ; 

__attribute__((used)) static struct wpabuf * eap_mschapv2_build_failure_req(
	struct eap_sm *sm, struct eap_mschapv2_data *data, u8 id)
{
	struct wpabuf *req;
	struct eap_mschapv2_hdr *ms;
	char *message = "E=691 R=0 C=00000000000000000000000000000000 V=3 "
		"M=FAILED";
	size_t ms_len;

	ms_len = sizeof(*ms) + os_strlen(message);
	req = eap_msg_alloc(EAP_VENDOR_IETF, EAP_TYPE_MSCHAPV2, ms_len,
			    EAP_CODE_REQUEST, id);
	if (req == NULL) {
		wpa_printf(MSG_ERROR, "EAP-MSCHAPV2: Failed to allocate memory"
			   " for request");
		data->state = FAILURE;
		return NULL;
	}

	ms = wpabuf_put(req, sizeof(*ms));
	ms->op_code = MSCHAPV2_OP_FAILURE;
	ms->mschapv2_id = data->resp_mschapv2_id;
	WPA_PUT_BE16(ms->ms_length, ms_len);

	wpabuf_put_data(req, message, os_strlen(message));

	wpa_hexdump_ascii(MSG_MSGDUMP, "EAP-MSCHAPV2: Failure Request Message",
			  (u8 *) message, os_strlen(message));

	return req;
}