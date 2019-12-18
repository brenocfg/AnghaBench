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
struct eap_sm {int /*<<< orphan*/  ssl_ctx; } ;
struct TYPE_2__ {int /*<<< orphan*/  conn; } ;
struct eap_fast_data {int anon_provisioning; TYPE_1__ ssl; } ;
typedef  int /*<<< orphan*/  cipher ;

/* Variables and functions */
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PHASE2_START ; 
 int /*<<< orphan*/  eap_fast_derive_key_auth (struct eap_sm*,struct eap_fast_data*) ; 
 int /*<<< orphan*/  eap_fast_derive_key_provisioning (struct eap_sm*,struct eap_fast_data*) ; 
 int /*<<< orphan*/  eap_fast_state (struct eap_fast_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * os_strstr (char*,char*) ; 
 scalar_t__ tls_get_cipher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_fast_phase1_done(struct eap_sm *sm, struct eap_fast_data *data)
{
	char cipher[64];

	wpa_printf(MSG_DEBUG, "EAP-FAST: Phase1 done, starting Phase2");

	if (tls_get_cipher(sm->ssl_ctx, data->ssl.conn, cipher, sizeof(cipher))
	    < 0) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Failed to get cipher "
			   "information");
		eap_fast_state(data, FAILURE);
		return -1;
	}
	data->anon_provisioning = os_strstr(cipher, "ADH") != NULL;

	if (data->anon_provisioning) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Anonymous provisioning");
		eap_fast_derive_key_provisioning(sm, data);
	} else
		eap_fast_derive_key_auth(sm, data);

	eap_fast_state(data, PHASE2_START);

	return 0;
}