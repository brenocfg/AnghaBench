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
struct wpabuf {int dummy; } ;
struct eap_sm {int dummy; } ;
struct eap_peap_data {int crypto_binding_used; scalar_t__ crypto_binding; scalar_t__ tlv_request; scalar_t__ crypto_binding_sent; } ;

/* Variables and functions */
#define  EAP_TLV_CRYPTO_BINDING_TLV 129 
 int EAP_TLV_RESULT_FAILURE ; 
 int EAP_TLV_RESULT_SUCCESS ; 
#define  EAP_TLV_RESULT_TLV 128 
 int /*<<< orphan*/  EAP_TYPE_TLV ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ REQUIRE_BINDING ; 
 int /*<<< orphan*/  SUCCESS ; 
 scalar_t__ TLV_REQ_SUCCESS ; 
 int WPA_GET_BE16 (int const*) ; 
 int* eap_hdr_validate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,size_t*) ; 
 int /*<<< orphan*/  eap_peap_state (struct eap_peap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_peap_valid_session (struct eap_sm*,struct eap_peap_data*) ; 
 scalar_t__ eap_tlv_validate_cryptobinding (struct eap_sm*,struct eap_peap_data*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_peap_process_phase2_tlv(struct eap_sm *sm,
					struct eap_peap_data *data,
					struct wpabuf *in_data)
{
	const u8 *pos;
	size_t left;
	const u8 *result_tlv = NULL, *crypto_tlv = NULL;
	size_t result_tlv_len = 0, crypto_tlv_len = 0;
	int tlv_type, mandatory, tlv_len;

	pos = eap_hdr_validate(EAP_VENDOR_IETF, EAP_TYPE_TLV, in_data, &left);
	if (pos == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Invalid EAP-TLV header");
		return;
	}

	/* Parse TLVs */
	wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Received TLVs", pos, left);
	while (left >= 4) {
		mandatory = !!(pos[0] & 0x80);
		tlv_type = pos[0] & 0x3f;
		tlv_type = (tlv_type << 8) | pos[1];
		tlv_len = ((int) pos[2] << 8) | pos[3];
		pos += 4;
		left -= 4;
		if ((size_t) tlv_len > left) {
			wpa_printf(MSG_DEBUG, "EAP-PEAP: TLV underrun "
				   "(tlv_len=%d left=%lu)", tlv_len,
				   (unsigned long) left);
			eap_peap_state(data, FAILURE);
			return;
		}
		switch (tlv_type) {
		case EAP_TLV_RESULT_TLV:
			result_tlv = pos;
			result_tlv_len = tlv_len;
			break;
		case EAP_TLV_CRYPTO_BINDING_TLV:
			crypto_tlv = pos;
			crypto_tlv_len = tlv_len;
			break;
		default:
			wpa_printf(MSG_DEBUG, "EAP-PEAP: Unsupported TLV Type "
				   "%d%s", tlv_type,
				   mandatory ? " (mandatory)" : "");
			if (mandatory) {
				eap_peap_state(data, FAILURE);
				return;
			}
			/* Ignore this TLV, but process other TLVs */
			break;
		}

		pos += tlv_len;
		left -= tlv_len;
	}
	if (left) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Last TLV too short in "
			   "Request (left=%lu)", (unsigned long) left);
		eap_peap_state(data, FAILURE);
		return;
	}

	/* Process supported TLVs */
	if (crypto_tlv && data->crypto_binding_sent) {
		wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Cryptobinding TLV",
			    crypto_tlv, crypto_tlv_len);
		if (eap_tlv_validate_cryptobinding(sm, data, crypto_tlv - 4,
						   crypto_tlv_len + 4) < 0) {
			eap_peap_state(data, FAILURE);
			return;
		}
		data->crypto_binding_used = 1;
	} else if (!crypto_tlv && data->crypto_binding_sent &&
		   data->crypto_binding == REQUIRE_BINDING) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: No cryptobinding TLV");
		eap_peap_state(data, FAILURE);
		return;
	}

	if (result_tlv) {
		int status;
		const char *requested;

		wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Result TLV",
			    result_tlv, result_tlv_len);
		if (result_tlv_len < 2) {
			wpa_printf(MSG_INFO, "EAP-PEAP: Too short Result TLV "
				   "(len=%lu)",
				   (unsigned long) result_tlv_len);
			eap_peap_state(data, FAILURE);
			return;
		}
		requested = data->tlv_request == TLV_REQ_SUCCESS ? "Success" :
			"Failure";
		status = WPA_GET_BE16(result_tlv);
		if (status == EAP_TLV_RESULT_SUCCESS) {
			wpa_printf(MSG_INFO, "EAP-PEAP: TLV Result - Success "
				   "- requested %s", requested);
			if (data->tlv_request == TLV_REQ_SUCCESS) {
				eap_peap_state(data, SUCCESS);
				eap_peap_valid_session(sm, data);
			} else {
				eap_peap_state(data, FAILURE);
			}

		} else if (status == EAP_TLV_RESULT_FAILURE) {
			wpa_printf(MSG_INFO, "EAP-PEAP: TLV Result - Failure "
				   "- requested %s", requested);
			eap_peap_state(data, FAILURE);
		} else {
			wpa_printf(MSG_INFO, "EAP-PEAP: Unknown TLV Result "
				   "Status %d", status);
			eap_peap_state(data, FAILURE);
		}
	}
}