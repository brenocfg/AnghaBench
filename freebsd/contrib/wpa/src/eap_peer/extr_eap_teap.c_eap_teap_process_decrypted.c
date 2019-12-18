#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct wpabuf {int dummy; } ;
struct eap_teap_tlv_parse {scalar_t__ result; scalar_t__ iresult; scalar_t__ crypto_binding; scalar_t__ pac; int /*<<< orphan*/  pac_len; int /*<<< orphan*/  crypto_binding_len; int /*<<< orphan*/  eap_payload_tlv_len; scalar_t__ eap_payload_tlv; int /*<<< orphan*/  basic_auth_req_len; scalar_t__ basic_auth_req; } ;
struct eap_teap_data {int result_success_done; int /*<<< orphan*/  teap_version; int /*<<< orphan*/  ssl; scalar_t__ provisioning; void* on_tx_completion; scalar_t__ phase2_success; TYPE_1__* phase2_method; int /*<<< orphan*/  tls_cs; int /*<<< orphan*/  anon_provisioning; int /*<<< orphan*/  current_pac; scalar_t__ session_ticket_used; scalar_t__ inner_method_done; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {void* decision; void* methodState; } ;
typedef  enum teap_error_codes { ____Placeholder_teap_error_codes } teap_error_codes ;
struct TYPE_2__ {scalar_t__ vendor; int /*<<< orphan*/  method; } ;

/* Variables and functions */
 void* DECISION_COND_SUCC ; 
 void* DECISION_FAIL ; 
 void* DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  EAP_TYPE_TEAP ; 
 void* METHOD_DONE ; 
 void* METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int TEAP_ERROR_TUNNEL_COMPROMISE_ERROR ; 
 int TEAP_ERROR_UNEXPECTED_TLVS_EXCHANGED ; 
 scalar_t__ TEAP_STATUS_FAILURE ; 
 scalar_t__ TEAP_STATUS_SUCCESS ; 
 scalar_t__ eap_peer_tls_encrypt (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpabuf*,struct wpabuf**) ; 
 scalar_t__ eap_teap_allowed_anon_prov_cipher_suite (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_teap_allowed_anon_prov_phase2_method (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_teap_derive_msk (struct eap_teap_data*) ; 
 struct wpabuf* eap_teap_pac_request () ; 
 scalar_t__ eap_teap_parse_decrypted (struct wpabuf*,struct eap_teap_tlv_parse*,struct wpabuf**) ; 
 struct wpabuf* eap_teap_process_basic_auth_req (struct eap_sm*,struct eap_teap_data*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_teap_process_crypto_binding (struct eap_sm*,struct eap_teap_data*,struct eap_method_ret*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_teap_process_eap_payload_tlv (struct eap_sm*,struct eap_teap_data*,struct eap_method_ret*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_teap_process_pac (struct eap_sm*,struct eap_teap_data*,struct eap_method_ret*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct wpabuf* eap_teap_tlv_error (int) ; 
 struct wpabuf* eap_teap_tlv_result (scalar_t__,int) ; 
 int /*<<< orphan*/  wpa_hexdump_buf (int /*<<< orphan*/ ,char*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 struct wpabuf* wpabuf_alloc (int) ; 
 struct wpabuf* wpabuf_concat (struct wpabuf*,struct wpabuf*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

__attribute__((used)) static int eap_teap_process_decrypted(struct eap_sm *sm,
				      struct eap_teap_data *data,
				      struct eap_method_ret *ret,
				      u8 identifier,
				      struct wpabuf *decrypted,
				      struct wpabuf **out_data)
{
	struct wpabuf *resp = NULL, *tmp;
	struct eap_teap_tlv_parse tlv;
	int failed = 0;
	enum teap_error_codes error = 0;

	if (eap_teap_parse_decrypted(decrypted, &tlv, &resp) < 0) {
		/* Parsing failed - no response available */
		return 0;
	}

	if (resp) {
		/* Parsing rejected the message - send out an error response */
		goto send_resp;
	}

	if (tlv.result == TEAP_STATUS_FAILURE) {
		/* Server indicated failure - respond similarly per
		 * RFC 7170, 3.6.3. This authentication exchange cannot succeed
		 * and will be terminated with a cleartext EAP Failure. */
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Server rejected authentication");
		resp = eap_teap_tlv_result(TEAP_STATUS_FAILURE, 0);
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
		goto send_resp;
	}

	if ((tlv.iresult == TEAP_STATUS_SUCCESS ||
	     (!data->result_success_done &&
	      tlv.result == TEAP_STATUS_SUCCESS)) &&
	    !tlv.crypto_binding) {
		/* Result TLV or Intermediate-Result TLV indicating success,
		 * but no Crypto-Binding TLV */
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Result TLV or Intermediate-Result TLV indicating success, but no Crypto-Binding TLV");
		failed = 1;
		error = TEAP_ERROR_TUNNEL_COMPROMISE_ERROR;
		goto done;
	}

	if (tlv.iresult != TEAP_STATUS_SUCCESS &&
	    tlv.iresult != TEAP_STATUS_FAILURE &&
	    data->inner_method_done) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Inner EAP method exchange completed, but no Intermediate-Result TLV included");
		failed = 1;
		error = TEAP_ERROR_TUNNEL_COMPROMISE_ERROR;
		goto done;
	}

	if (tlv.basic_auth_req) {
		tmp = eap_teap_process_basic_auth_req(sm, data,
						      tlv.basic_auth_req,
						      tlv.basic_auth_req_len);
		if (!tmp)
			failed = 1;
		resp = wpabuf_concat(resp, tmp);
	} else if (tlv.eap_payload_tlv) {
		tmp = eap_teap_process_eap_payload_tlv(sm, data, ret,
						       tlv.eap_payload_tlv,
						       tlv.eap_payload_tlv_len);
		if (!tmp)
			failed = 1;
		resp = wpabuf_concat(resp, tmp);

		if (tlv.iresult == TEAP_STATUS_SUCCESS ||
		    tlv.iresult == TEAP_STATUS_FAILURE) {
			tmp = eap_teap_tlv_result(failed ?
						  TEAP_STATUS_FAILURE :
						  TEAP_STATUS_SUCCESS, 1);
			resp = wpabuf_concat(resp, tmp);
			if (tlv.iresult == TEAP_STATUS_FAILURE)
				failed = 1;
		}
	}

	if (tlv.crypto_binding) {
		if (tlv.iresult != TEAP_STATUS_SUCCESS &&
		    tlv.result != TEAP_STATUS_SUCCESS) {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: Unexpected Crypto-Binding TLV without Result TLV or Intermediate-Result TLV indicating success");
			failed = 1;
			error = TEAP_ERROR_UNEXPECTED_TLVS_EXCHANGED;
			goto done;
		}

		tmp = eap_teap_process_crypto_binding(sm, data, ret,
						      tlv.crypto_binding,
						      tlv.crypto_binding_len);
		if (!tmp) {
			failed = 1;
			error = TEAP_ERROR_TUNNEL_COMPROMISE_ERROR;
		} else {
			resp = wpabuf_concat(resp, tmp);
			if (tlv.result == TEAP_STATUS_SUCCESS && !failed)
				data->result_success_done = 1;
			if (tlv.iresult == TEAP_STATUS_SUCCESS && !failed)
				data->inner_method_done = 0;
		}
	}

	if (data->result_success_done && data->session_ticket_used &&
	    eap_teap_derive_msk(data) == 0) {
		/* Assume the server might accept authentication without going
		 * through inner authentication. */
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: PAC used - server may decide to skip inner authentication");
		ret->methodState = METHOD_MAY_CONT;
		ret->decision = DECISION_COND_SUCC;
	}

	if (tlv.pac) {
		if (tlv.result == TEAP_STATUS_SUCCESS) {
			tmp = eap_teap_process_pac(sm, data, ret,
						   tlv.pac, tlv.pac_len);
			resp = wpabuf_concat(resp, tmp);
		} else {
			wpa_printf(MSG_DEBUG,
				   "EAP-TEAP: PAC TLV without Result TLV acknowledging success");
			failed = 1;
			error = TEAP_ERROR_UNEXPECTED_TLVS_EXCHANGED;
		}
	}

	if (!data->current_pac && data->provisioning && !failed && !tlv.pac &&
	    tlv.crypto_binding &&
	    (!data->anon_provisioning ||
	     (data->phase2_success && data->phase2_method &&
	      data->phase2_method->vendor == 0 &&
	      eap_teap_allowed_anon_prov_cipher_suite(data->tls_cs) &&
	      eap_teap_allowed_anon_prov_phase2_method(
		      data->phase2_method->method))) &&
	    (tlv.iresult == TEAP_STATUS_SUCCESS ||
	     tlv.result == TEAP_STATUS_SUCCESS)) {
		/*
		 * Need to request Tunnel PAC when using authenticated
		 * provisioning.
		 */
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Request Tunnel PAC");
		tmp = eap_teap_pac_request();
		resp = wpabuf_concat(resp, tmp);
	}

done:
	if (failed) {
		tmp = eap_teap_tlv_result(TEAP_STATUS_FAILURE, 0);
		resp = wpabuf_concat(tmp, resp);

		if (error != 0) {
			tmp = eap_teap_tlv_error(error);
			resp = wpabuf_concat(tmp, resp);
		}

		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
	} else if (tlv.result == TEAP_STATUS_SUCCESS) {
		tmp = eap_teap_tlv_result(TEAP_STATUS_SUCCESS, 0);
		resp = wpabuf_concat(tmp, resp);
	}

	if (resp && tlv.result == TEAP_STATUS_SUCCESS && !failed &&
	    tlv.crypto_binding && data->phase2_success) {
		/* Successfully completed Phase 2 */
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Authentication completed successfully");
		ret->methodState = METHOD_MAY_CONT;
		data->on_tx_completion = data->provisioning ?
			METHOD_MAY_CONT : METHOD_DONE;
		ret->decision = DECISION_UNCOND_SUCC;
	}

	if (!resp) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: No recognized TLVs - send empty response packet");
		resp = wpabuf_alloc(1);
	}

send_resp:
	if (!resp)
		return 0;

	wpa_hexdump_buf(MSG_DEBUG, "EAP-TEAP: Encrypting Phase 2 data", resp);
	if (eap_peer_tls_encrypt(sm, &data->ssl, EAP_TYPE_TEAP,
				 data->teap_version, identifier,
				 resp, out_data)) {
		wpa_printf(MSG_INFO,
			   "EAP-TEAP: Failed to encrypt a Phase 2 frame");
	}
	wpabuf_free(resp);

	return 0;
}