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
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_teap_data {int anon_provisioning; TYPE_1__ ssl; int /*<<< orphan*/  tls_cs; } ;
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
typedef  int /*<<< orphan*/  cipher ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PHASE2_START ; 
 scalar_t__ eap_teap_derive_key_auth (struct eap_sm*,struct eap_teap_data*) ; 
 int /*<<< orphan*/  eap_teap_state (struct eap_teap_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_strstr (char*,char*) ; 
 int /*<<< orphan*/  tls_connection_get_cipher_suite (int /*<<< orphan*/ ) ; 
 scalar_t__ tls_get_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_teap_phase1_done(struct eap_sm *sm, struct eap_teap_data *data)
{
	char cipher[64];

	wpa_printf(MSG_DEBUG, "EAP-TEAP: Phase 1 done, starting Phase 2");

	data->tls_cs = tls_connection_get_cipher_suite(data->ssl.conn);
	wpa_printf(MSG_DEBUG, "EAP-TEAP: TLS cipher suite 0x%04x",
		   data->tls_cs);

	if (tls_get_cipher(sm->ssl_ctx, data->ssl.conn, cipher, sizeof(cipher))
	    < 0) {
		wpa_printf(MSG_DEBUG,
			   "EAP-TEAP: Failed to get cipher information");
		eap_teap_state(data, FAILURE);
		return -1;
	}
	data->anon_provisioning = os_strstr(cipher, "ADH") != NULL;

	if (data->anon_provisioning)
		wpa_printf(MSG_DEBUG, "EAP-TEAP: Anonymous provisioning");

	if (eap_teap_derive_key_auth(sm, data) < 0) {
		eap_teap_state(data, FAILURE);
		return -1;
	}

	eap_teap_state(data, PHASE2_START);

	return 0;
}