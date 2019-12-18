#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct eap_sm {scalar_t__ workaround; int /*<<< orphan*/  ssl_ctx; scalar_t__ waiting_ext_cert_check; } ;
struct eap_peer_config {scalar_t__ pending_ext_cert_check; } ;
struct TYPE_5__ {int /*<<< orphan*/  conn; } ;
struct eap_peap_data {int peap_version; int force_peap_version; int phase2_success; struct wpabuf* pending_phase2_req; scalar_t__ resuming; int /*<<< orphan*/  id_len; scalar_t__ session_id; TYPE_1__ ssl; scalar_t__ key_data; scalar_t__ force_new_label; struct wpabuf* pending_resp; } ;
struct eap_method_ret {scalar_t__ methodState; void* allowNotifications; void* decision; } ;
struct eap_hdr {int identifier; } ;

/* Variables and functions */
 void* DECISION_COND_SUCC ; 
 void* DECISION_FAIL ; 
 scalar_t__ EAP_EMSK_LEN ; 
 int EAP_TLS_FLAGS_START ; 
 scalar_t__ EAP_TLS_KEY_LEN ; 
 int EAP_TLS_VERSION_MASK ; 
 int /*<<< orphan*/  EAP_TYPE_PEAP ; 
 scalar_t__ EXT_CERT_CHECK_BAD ; 
 scalar_t__ EXT_CERT_CHECK_GOOD ; 
 void* FALSE ; 
 scalar_t__ METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 struct eap_peer_config* eap_get_config (struct eap_sm*) ; 
 int eap_peap_decrypt (struct eap_sm*,struct eap_peap_data*,struct eap_method_ret*,struct eap_hdr const*,struct wpabuf*,struct wpabuf**) ; 
 int /*<<< orphan*/  eap_peap_free_key (struct eap_peap_data*) ; 
 struct wpabuf* eap_peer_tls_build_ack (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ eap_peer_tls_derive_key (struct eap_sm*,TYPE_1__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eap_peer_tls_derive_session_id (struct eap_sm*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int eap_peer_tls_process_helper (struct eap_sm*,TYPE_1__*,int /*<<< orphan*/ ,int,int,struct wpabuf*,struct wpabuf**) ; 
 int* eap_peer_tls_process_init (struct eap_sm*,TYPE_1__*,int /*<<< orphan*/ ,struct eap_method_ret*,struct wpabuf const*,size_t*,int*) ; 
 int /*<<< orphan*/  os_free (scalar_t__) ; 
 scalar_t__ tls_connection_established (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  wpabuf_clear_free (struct wpabuf*) ; 
 struct eap_hdr* wpabuf_head (struct wpabuf const*) ; 
 int /*<<< orphan*/  wpabuf_set (struct wpabuf*,int const*,size_t) ; 

__attribute__((used)) static struct wpabuf * eap_peap_process(struct eap_sm *sm, void *priv,
					struct eap_method_ret *ret,
					const struct wpabuf *reqData)
{
	const struct eap_hdr *req;
	size_t left;
	int res;
	u8 flags, id;
	struct wpabuf *resp;
	const u8 *pos;
	struct eap_peap_data *data = priv;
	struct wpabuf msg;

	pos = eap_peer_tls_process_init(sm, &data->ssl, EAP_TYPE_PEAP, ret,
					reqData, &left, &flags);
	if (pos == NULL)
		return NULL;
	req = wpabuf_head(reqData);
	id = req->identifier;

	if (flags & EAP_TLS_FLAGS_START) {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Start (server ver=%d, own "
			   "ver=%d)", flags & EAP_TLS_VERSION_MASK,
			data->peap_version);
		if ((flags & EAP_TLS_VERSION_MASK) < data->peap_version)
			data->peap_version = flags & EAP_TLS_VERSION_MASK;
		if (data->force_peap_version >= 0 &&
		    data->force_peap_version != data->peap_version) {
			wpa_printf(MSG_WARNING, "EAP-PEAP: Failed to select "
				   "forced PEAP version %d",
				   data->force_peap_version);
			ret->methodState = METHOD_DONE;
			ret->decision = DECISION_FAIL;
			ret->allowNotifications = FALSE;
			return NULL;
		}
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Using PEAP version %d",
			   data->peap_version);
		left = 0; /* make sure that this frame is empty, even though it
			   * should always be, anyway */
	}

	wpabuf_set(&msg, pos, left);

	resp = NULL;
	if (tls_connection_established(sm->ssl_ctx, data->ssl.conn) &&
	    !data->resuming) {
		res = eap_peap_decrypt(sm, data, ret, req, &msg, &resp);
	} else {
		if (sm->waiting_ext_cert_check && data->pending_resp) {
			struct eap_peer_config *config = eap_get_config(sm);

			if (config->pending_ext_cert_check ==
			    EXT_CERT_CHECK_GOOD) {
				wpa_printf(MSG_DEBUG,
					   "EAP-PEAP: External certificate check succeeded - continue handshake");
				resp = data->pending_resp;
				data->pending_resp = NULL;
				sm->waiting_ext_cert_check = 0;
				return resp;
			}

			if (config->pending_ext_cert_check ==
			    EXT_CERT_CHECK_BAD) {
				wpa_printf(MSG_DEBUG,
					   "EAP-PEAP: External certificate check failed - force authentication failure");
				ret->methodState = METHOD_DONE;
				ret->decision = DECISION_FAIL;
				sm->waiting_ext_cert_check = 0;
				return NULL;
			}

			wpa_printf(MSG_DEBUG,
				   "EAP-PEAP: Continuing to wait external server certificate validation");
			return NULL;
		}

		res = eap_peer_tls_process_helper(sm, &data->ssl,
						  EAP_TYPE_PEAP,
						  data->peap_version, id, &msg,
						  &resp);

		if (res < 0) {
			wpa_printf(MSG_DEBUG,
				   "EAP-PEAP: TLS processing failed");
			ret->methodState = METHOD_DONE;
			ret->decision = DECISION_FAIL;
			return resp;
		}


		if (sm->waiting_ext_cert_check) {
			wpa_printf(MSG_DEBUG,
				   "EAP-PEAP: Waiting external server certificate validation");
			wpabuf_clear_free(data->pending_resp);
			data->pending_resp = resp;
			return NULL;
		}

		if (tls_connection_established(sm->ssl_ctx, data->ssl.conn)) {
			char *label;
			wpa_printf(MSG_DEBUG,
				   "EAP-PEAP: TLS done, proceed to Phase 2");
			eap_peap_free_key(data);
			/* draft-josefsson-ppext-eap-tls-eap-05.txt
			 * specifies that PEAPv1 would use "client PEAP
			 * encryption" as the label. However, most existing
			 * PEAPv1 implementations seem to be using the old
			 * label, "client EAP encryption", instead. Use the old
			 * label by default, but allow it to be configured with
			 * phase1 parameter peaplabel=1. */
			if (data->force_new_label)
				label = "client PEAP encryption";
			else
				label = "client EAP encryption";
			wpa_printf(MSG_DEBUG, "EAP-PEAP: using label '%s' in "
				   "key derivation", label);
			data->key_data =
				eap_peer_tls_derive_key(sm, &data->ssl, label,
							NULL, 0,
							EAP_TLS_KEY_LEN +
							EAP_EMSK_LEN);
			if (data->key_data) {
				wpa_hexdump_key(MSG_DEBUG,
						"EAP-PEAP: Derived key",
						data->key_data,
						EAP_TLS_KEY_LEN);
				wpa_hexdump_key(MSG_DEBUG,
						"EAP-PEAP: Derived EMSK",
						data->key_data +
						EAP_TLS_KEY_LEN,
						EAP_EMSK_LEN);
			} else {
				wpa_printf(MSG_DEBUG, "EAP-PEAP: Failed to "
					   "derive key");
			}

			os_free(data->session_id);
			data->session_id =
				eap_peer_tls_derive_session_id(sm, &data->ssl,
							       EAP_TYPE_PEAP,
							       &data->id_len);
			if (data->session_id) {
				wpa_hexdump(MSG_DEBUG,
					    "EAP-PEAP: Derived Session-Id",
					    data->session_id, data->id_len);
			} else {
				wpa_printf(MSG_ERROR, "EAP-PEAP: Failed to "
					   "derive Session-Id");
			}

			if (sm->workaround && data->resuming) {
				/*
				 * At least few RADIUS servers (Aegis v1.1.6;
				 * but not v1.1.4; and Cisco ACS) seem to be
				 * terminating PEAPv1 (Aegis) or PEAPv0 (Cisco
				 * ACS) session resumption with outer
				 * EAP-Success. This does not seem to follow
				 * draft-josefsson-pppext-eap-tls-eap-05.txt
				 * section 4.2, so only allow this if EAP
				 * workarounds are enabled.
				 */
				wpa_printf(MSG_DEBUG, "EAP-PEAP: Workaround - "
					   "allow outer EAP-Success to "
					   "terminate PEAP resumption");
				ret->decision = DECISION_COND_SUCC;
				data->phase2_success = 1;
			}

			data->resuming = 0;
		}

		if (res == 2) {
			/*
			 * Application data included in the handshake message.
			 */
			wpabuf_clear_free(data->pending_phase2_req);
			data->pending_phase2_req = resp;
			resp = NULL;
			res = eap_peap_decrypt(sm, data, ret, req, &msg,
					       &resp);
		}
	}

	if (ret->methodState == METHOD_DONE) {
		ret->allowNotifications = FALSE;
	}

	if (res == 1) {
		wpabuf_clear_free(resp);
		return eap_peer_tls_build_ack(id, EAP_TYPE_PEAP,
					      data->peap_version);
	}

	return resp;
}