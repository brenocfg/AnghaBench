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
typedef  scalar_t__ u16 ;
struct wpabuf {int dummy; } ;
struct eap_teap_tlv_parse {scalar_t__ result; int pac_len; scalar_t__ iresult; scalar_t__ request_action; int /*<<< orphan*/  eap_payload_tlv_len; scalar_t__ eap_payload_tlv; int /*<<< orphan*/  basic_auth_resp_len; scalar_t__ basic_auth_resp; scalar_t__ pac; int /*<<< orphan*/  crypto_binding_len; int /*<<< orphan*/  crypto_binding; scalar_t__ nak; } ;
struct eap_teap_data {scalar_t__ state; scalar_t__ final_result; scalar_t__ send_new_pac; scalar_t__ anon_provisioning; } ;
struct eap_sm {scalar_t__ eap_fast_prov; int eap_teap_auth; } ;

/* Variables and functions */
 scalar_t__ ANON_PROV ; 
 scalar_t__ AUTH_PROV ; 
 scalar_t__ BOTH_PROV ; 
 scalar_t__ CRYPTO_BINDING ; 
 scalar_t__ FAILURE ; 
 scalar_t__ FAILURE_SEND_RESULT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PAC_TYPE_PAC_ACKNOWLEDGEMENT ; 
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 scalar_t__ REQUEST_PAC ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ TEAP_REQUEST_ACTION_PROCESS_TLV ; 
 scalar_t__ TEAP_STATUS_FAILURE ; 
 scalar_t__ TEAP_STATUS_SUCCESS ; 
 scalar_t__ WPA_GET_BE16 (scalar_t__) ; 
 int /*<<< orphan*/  WPA_GET_BE32 (scalar_t__) ; 
 scalar_t__ eap_teap_pac_type (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_teap_parse_tlvs (struct wpabuf*,struct eap_teap_tlv_parse*) ; 
 int /*<<< orphan*/  eap_teap_process_basic_auth_resp (struct eap_sm*,struct eap_teap_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_process_phase2_eap (struct eap_sm*,struct eap_teap_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_teap_state (struct eap_teap_data*,scalar_t__) ; 
 scalar_t__ eap_teap_validate_crypto_binding (struct eap_teap_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void eap_teap_process_phase2_tlvs(struct eap_sm *sm,
					 struct eap_teap_data *data,
					 struct wpabuf *in_data)
{
	struct eap_teap_tlv_parse tlv;
	int check_crypto_binding = data->state == CRYPTO_BINDING;

	if (eap_teap_parse_tlvs(in_data, &tlv) < 0) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Failed to parse received Phase 2 TLVs");
		return;
	}

	if (tlv.result == TEAP_STATUS_FAILURE) {
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Result TLV indicated failure");
		eap_teap_state(data, FAILURE);
		return;
	}

	if (tlv.nak) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Peer NAK'ed Vendor-Id %u NAK-Type %u",
			   WPA_GET_BE32(tlv.nak), WPA_GET_BE16(tlv.nak + 4));
		eap_teap_state(data, FAILURE_SEND_RESULT);
		return;
	}

	if (data->state == REQUEST_PAC) {
		u16 type, len, res;

		if (!tlv.pac || tlv.pac_len < 6) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: No PAC Acknowledgement received");
			eap_teap_state(data, FAILURE);
			return;
		}

		type = WPA_GET_BE16(tlv.pac);
		len = WPA_GET_BE16(tlv.pac + 2);
		res = WPA_GET_BE16(tlv.pac + 4);

		if (type != PAC_TYPE_PAC_ACKNOWLEDGEMENT || len != 2 ||
		    res != TEAP_STATUS_SUCCESS) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: PAC TLV did not contain acknowledgement");
			eap_teap_state(data, FAILURE);
			return;
		}

		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: PAC-Acknowledgement received - PAC provisioning succeeded");
		eap_teap_state(data, SUCCESS);
		return;
	}

	if (check_crypto_binding) {
		if (!tlv.crypto_binding) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: No Crypto-Binding TLV received");
			eap_teap_state(data, FAILURE);
			return;
		}

		if (data->final_result &&
		    tlv.result != TEAP_STATUS_SUCCESS) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Crypto-Binding TLV without Success Result");
			eap_teap_state(data, FAILURE);
			return;
		}

		if (!data->final_result &&
		    tlv.iresult != TEAP_STATUS_SUCCESS) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Crypto-Binding TLV without intermediate Success Result");
			eap_teap_state(data, FAILURE);
			return;
		}

		if (eap_teap_validate_crypto_binding(data, tlv.crypto_binding,
						     tlv.crypto_binding_len)) {
			eap_teap_state(data, FAILURE);
			return;
		}

		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Valid Crypto-Binding TLV received");
		if (data->final_result) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Authentication completed successfully");
		}

		if (data->anon_provisioning &&
		    sm->eap_fast_prov != ANON_PROV &&
		    sm->eap_fast_prov != BOTH_PROV) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Client is trying to use unauthenticated provisioning which is disabled");
			eap_teap_state(data, FAILURE);
			return;
		}

		if (sm->eap_fast_prov != AUTH_PROV &&
		    sm->eap_fast_prov != BOTH_PROV &&
		    tlv.request_action == TEAP_REQUEST_ACTION_PROCESS_TLV &&
		    eap_teap_pac_type(tlv.pac, tlv.pac_len,
				      PAC_TYPE_TUNNEL_PAC)) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Client is trying to use authenticated provisioning which is disabled");
			eap_teap_state(data, FAILURE);
			return;
		}

		if (data->anon_provisioning ||
		    (tlv.request_action == TEAP_REQUEST_ACTION_PROCESS_TLV &&
		     eap_teap_pac_type(tlv.pac, tlv.pac_len,
				       PAC_TYPE_TUNNEL_PAC))) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Requested a new Tunnel PAC");
			eap_teap_state(data, REQUEST_PAC);
		} else if (data->send_new_pac) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Server triggered re-keying of Tunnel PAC");
			eap_teap_state(data, REQUEST_PAC);
		} else if (data->final_result)
			eap_teap_state(data, SUCCESS);
	}

	if (tlv.basic_auth_resp) {
		if (sm->eap_teap_auth != 1) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Unexpected Basic-Password-Auth-Resp when trying to use inner EAP");
			eap_teap_state(data, FAILURE);
			return;
		}
		eap_teap_process_basic_auth_resp(sm, data, tlv.basic_auth_resp,
						 tlv.basic_auth_resp_len);
	}

	if (tlv.eap_payload_tlv) {
		if (sm->eap_teap_auth == 1) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Unexpected EAP Payload TLV when trying to use Basic-Password-Auth");
			eap_teap_state(data, FAILURE);
			return;
		}
		eap_teap_process_phase2_eap(sm, data, tlv.eap_payload_tlv,
					    tlv.eap_payload_tlv_len);
	}
}