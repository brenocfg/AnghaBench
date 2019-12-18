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
struct eap_sm {scalar_t__ eap_fast_prov; } ;
struct eap_fast_tlv_parse {scalar_t__ result; int pac_len; scalar_t__ iresult; scalar_t__ request_action; int /*<<< orphan*/  eap_payload_tlv_len; scalar_t__ eap_payload_tlv; int /*<<< orphan*/ * pac; int /*<<< orphan*/  crypto_binding_len; int /*<<< orphan*/ * crypto_binding; } ;
struct eap_fast_data {scalar_t__ state; int send_new_pac; scalar_t__ final_result; scalar_t__ anon_provisioning; } ;

/* Variables and functions */
 scalar_t__ ANON_PROV ; 
 scalar_t__ AUTH_PROV ; 
 scalar_t__ BOTH_PROV ; 
 scalar_t__ CRYPTO_BINDING ; 
 scalar_t__ EAP_TLV_ACTION_PROCESS_TLV ; 
 scalar_t__ EAP_TLV_RESULT_FAILURE ; 
 scalar_t__ EAP_TLV_RESULT_SUCCESS ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ PAC_TYPE_PAC_ACKNOWLEDGEMENT ; 
 int /*<<< orphan*/  PAC_TYPE_TUNNEL_PAC ; 
 scalar_t__ REQUEST_PAC ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ WPA_GET_BE16 (int /*<<< orphan*/ *) ; 
 scalar_t__ eap_fast_pac_type (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_fast_parse_tlvs (struct wpabuf*,struct eap_fast_tlv_parse*) ; 
 int /*<<< orphan*/  eap_fast_process_phase2_eap (struct eap_sm*,struct eap_fast_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,scalar_t__) ; 
 scalar_t__ eap_fast_validate_crypto_binding (struct eap_fast_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_fast_process_phase2_tlvs(struct eap_sm *sm,
					 struct eap_fast_data *data,
					 struct wpabuf *in_data)
{
	struct eap_fast_tlv_parse tlv;
	int check_crypto_binding = data->state == CRYPTO_BINDING;

	if (eap_fast_parse_tlvs(in_data, &tlv) < 0) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Failed to parse received "
			   "Phase 2 TLVs");
		return;
	}

	if (tlv.result == EAP_TLV_RESULT_FAILURE) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Result TLV indicated "
			   "failure");
		eap_fast_state(data, FAILURE);
		return;
	}

	if (data->state == REQUEST_PAC) {
		u16 type, len, res;
		if (tlv.pac == NULL || tlv.pac_len < 6) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: No PAC "
				   "Acknowledgement received");
			eap_fast_state(data, FAILURE);
			return;
		}

		type = WPA_GET_BE16(tlv.pac);
		len = WPA_GET_BE16(tlv.pac + 2);
		res = WPA_GET_BE16(tlv.pac + 4);

		if (type != PAC_TYPE_PAC_ACKNOWLEDGEMENT || len != 2 ||
		    res != EAP_TLV_RESULT_SUCCESS) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: PAC TLV did not "
				   "contain acknowledgement");
			eap_fast_state(data, FAILURE);
			return;
		}

		wpa_printf(MSG_DEBUG, "EAP-FAST: PAC-Acknowledgement received "
			   "- PAC provisioning succeeded");
		eap_fast_state(data, (data->anon_provisioning ||
				      data->send_new_pac == 2) ?
			       FAILURE : SUCCESS);
		return;
	}

	if (check_crypto_binding) {
		if (tlv.crypto_binding == NULL) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: No Crypto-Binding "
				   "TLV received");
			eap_fast_state(data, FAILURE);
			return;
		}

		if (data->final_result &&
		    tlv.result != EAP_TLV_RESULT_SUCCESS) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Crypto-Binding TLV "
				   "without Success Result");
			eap_fast_state(data, FAILURE);
			return;
		}

		if (!data->final_result &&
		    tlv.iresult != EAP_TLV_RESULT_SUCCESS) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Crypto-Binding TLV "
				   "without intermediate Success Result");
			eap_fast_state(data, FAILURE);
			return;
		}

		if (eap_fast_validate_crypto_binding(data, tlv.crypto_binding,
						     tlv.crypto_binding_len)) {
			eap_fast_state(data, FAILURE);
			return;
		}

		wpa_printf(MSG_DEBUG, "EAP-FAST: Valid Crypto-Binding TLV "
			   "received");
		if (data->final_result) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Authentication "
				   "completed successfully");
		}

		if (data->anon_provisioning &&
		    sm->eap_fast_prov != ANON_PROV &&
		    sm->eap_fast_prov != BOTH_PROV) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Client is trying to "
				   "use unauthenticated provisioning which is "
				   "disabled");
			eap_fast_state(data, FAILURE);
			return;
		}

		if (sm->eap_fast_prov != AUTH_PROV &&
		    sm->eap_fast_prov != BOTH_PROV &&
		    tlv.request_action == EAP_TLV_ACTION_PROCESS_TLV &&
		    eap_fast_pac_type(tlv.pac, tlv.pac_len,
				      PAC_TYPE_TUNNEL_PAC)) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Client is trying to "
				   "use authenticated provisioning which is "
				   "disabled");
			eap_fast_state(data, FAILURE);
			return;
		}

		if (data->anon_provisioning ||
		    (tlv.request_action == EAP_TLV_ACTION_PROCESS_TLV &&
		     eap_fast_pac_type(tlv.pac, tlv.pac_len,
				       PAC_TYPE_TUNNEL_PAC))) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Requested a new "
				   "Tunnel PAC");
			eap_fast_state(data, REQUEST_PAC);
		} else if (data->send_new_pac) {
			wpa_printf(MSG_DEBUG, "EAP-FAST: Server triggered "
				   "re-keying of Tunnel PAC");
			eap_fast_state(data, REQUEST_PAC);
		} else if (data->final_result)
			eap_fast_state(data, SUCCESS);
	}

	if (tlv.eap_payload_tlv) {
		eap_fast_process_phase2_eap(sm, data, tlv.eap_payload_tlv,
					    tlv.eap_payload_tlv_len);
	}
}