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
struct eap_ttls_data {int /*<<< orphan*/  id_len; scalar_t__ session_id; int /*<<< orphan*/  ssl; scalar_t__ key_data; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 scalar_t__ EAP_EMSK_LEN ; 
 scalar_t__ EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 scalar_t__ eap_peer_tls_derive_key (struct eap_sm*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ eap_peer_tls_derive_session_id (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  eap_ttls_free_key (struct eap_ttls_data*) ; 
 int /*<<< orphan*/  os_free (scalar_t__) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_ttls_v0_derive_key(struct eap_sm *sm,
				  struct eap_ttls_data *data)
{
	eap_ttls_free_key(data);
	data->key_data = eap_peer_tls_derive_key(sm, &data->ssl,
						 "ttls keying material",
						 NULL, 0,
						 EAP_TLS_KEY_LEN +
						 EAP_EMSK_LEN);
	if (!data->key_data) {
		wpa_printf(MSG_INFO, "EAP-TTLS: Failed to derive key");
		return -1;
	}

	wpa_hexdump_key(MSG_DEBUG, "EAP-TTLS: Derived key",
			data->key_data, EAP_TLS_KEY_LEN);
	wpa_hexdump_key(MSG_DEBUG, "EAP-TTLS: Derived EMSK",
			data->key_data + EAP_TLS_KEY_LEN,
			EAP_EMSK_LEN);

	os_free(data->session_id);
	data->session_id = eap_peer_tls_derive_session_id(sm, &data->ssl,
							  EAP_TYPE_TTLS,
	                                                  &data->id_len);
	if (data->session_id) {
		wpa_hexdump(MSG_DEBUG, "EAP-TTLS: Derived Session-Id",
			    data->session_id, data->id_len);
	} else {
		wpa_printf(MSG_ERROR, "EAP-TTLS: Failed to derive Session-Id");
	}

	return 0;
}