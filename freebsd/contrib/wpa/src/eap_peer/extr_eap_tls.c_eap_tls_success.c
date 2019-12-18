#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {scalar_t__ tls_v13; scalar_t__ tls_out; } ;
struct eap_tls_data {int /*<<< orphan*/  id_len; scalar_t__ session_id; TYPE_1__ ssl; scalar_t__ key_data; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_COND_SUCC ; 
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 scalar_t__ EAP_EMSK_LEN ; 
 scalar_t__ EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  const EAP_TYPE_TLS ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_peer_tls_derive_key (struct eap_sm*,TYPE_1__*,char const*,int /*<<< orphan*/  const*,size_t,scalar_t__) ; 
 scalar_t__ eap_peer_tls_derive_session_id (struct eap_sm*,TYPE_1__*,int /*<<< orphan*/  const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_tls_free_key (struct eap_tls_data*) ; 
 int /*<<< orphan*/  os_free (scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_tls_success(struct eap_sm *sm, struct eap_tls_data *data,
			    struct eap_method_ret *ret)
{
	const char *label;
	const u8 eap_tls13_context[] = { EAP_TYPE_TLS };
	const u8 *context = NULL;
	size_t context_len = 0;

	wpa_printf(MSG_DEBUG, "EAP-TLS: Done");

	if (data->ssl.tls_out) {
		wpa_printf(MSG_DEBUG, "EAP-TLS: Fragment(s) remaining");
		return;
	}

	if (data->ssl.tls_v13) {
		label = "EXPORTER_EAP_TLS_Key_Material";
		context = eap_tls13_context;
		context_len = 1;

		/* A possible NewSessionTicket may be received before
		 * EAP-Success, so need to allow it to be received. */
		ret->methodState = METHOD_MAY_CONT;
		ret->decision = DECISION_COND_SUCC;
	} else {
		label = "client EAP encryption";

		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_UNCOND_SUCC;
	}

	eap_tls_free_key(data);
	data->key_data = eap_peer_tls_derive_key(sm, &data->ssl, label,
						 context, context_len,
						 EAP_TLS_KEY_LEN +
						 EAP_EMSK_LEN);
	if (data->key_data) {
		wpa_hexdump_key(MSG_DEBUG, "EAP-TLS: Derived key",
				data->key_data, EAP_TLS_KEY_LEN);
		wpa_hexdump_key(MSG_DEBUG, "EAP-TLS: Derived EMSK",
				data->key_data + EAP_TLS_KEY_LEN,
				EAP_EMSK_LEN);
	} else {
		wpa_printf(MSG_INFO, "EAP-TLS: Failed to derive key");
	}

	os_free(data->session_id);
	data->session_id = eap_peer_tls_derive_session_id(sm, &data->ssl,
							  EAP_TYPE_TLS,
			                                  &data->id_len);
	if (data->session_id) {
		wpa_hexdump(MSG_DEBUG, "EAP-TLS: Derived Session-Id",
			    data->session_id, data->id_len);
	} else {
		wpa_printf(MSG_ERROR, "EAP-TLS: Failed to derive Session-Id");
	}
}