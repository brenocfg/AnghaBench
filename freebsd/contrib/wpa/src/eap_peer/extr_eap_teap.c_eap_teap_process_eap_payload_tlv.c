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
struct eap_teap_data {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int dummy; } ;
struct eap_hdr {int /*<<< orphan*/  code; int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_CODE_REQUEST ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 size_t be_to_host16 (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_teap_phase2_request (struct eap_sm*,struct eap_teap_data*,struct eap_method_ret*,struct eap_hdr*,struct wpabuf**) ; 
 struct wpabuf* eap_teap_tlv_eap_payload (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static struct wpabuf * eap_teap_process_eap_payload_tlv(
	struct eap_sm *sm, struct eap_teap_data *data,
	struct eap_method_ret *ret,
	u8 *eap_payload_tlv, size_t eap_payload_tlv_len)
{
	struct eap_hdr *hdr;
	struct wpabuf *resp = NULL;

	if (eap_payload_tlv_len < sizeof(*hdr)) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: too short EAP Payload TLV (len=%lu)",
			   (unsigned long) eap_payload_tlv_len);
		return NULL;
	}

	hdr = (struct eap_hdr *) eap_payload_tlv;
	if (be_to_host16(hdr->length) > eap_payload_tlv_len) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: EAP packet overflow in EAP Payload TLV");
		return NULL;
	}

	if (hdr->code != EAP_CODE_REQUEST) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Unexpected code=%d in Phase 2 EAP header",
			   hdr->code);
		return NULL;
	}

	if (eap_teap_phase2_request(sm, data, ret, hdr, &resp)) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Phase 2 Request processing failed");
		return NULL;
	}

	return eap_teap_tlv_eap_payload(resp);
}