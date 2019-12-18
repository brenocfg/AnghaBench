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
struct eap_sm {int dummy; } ;
struct eap_peap_data {scalar_t__ state; int /*<<< orphan*/  ssl; scalar_t__ crypto_binding_used; } ;

/* Variables and functions */
 size_t EAP_EMSK_LEN ; 
 int EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * eap_server_tls_derive_key (struct eap_sm*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u8 * eap_peap_get_emsk(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_peap_data *data = priv;
	u8 *eapKeyData, *emsk;

	if (data->state != SUCCESS)
		return NULL;

	if (data->crypto_binding_used) {
		/* [MS-PEAP] does not define EMSK derivation */
		return NULL;
	}

	/* TODO: PEAPv1 - different label in some cases */
	eapKeyData = eap_server_tls_derive_key(sm, &data->ssl,
					       "client EAP encryption", NULL, 0,
					       EAP_TLS_KEY_LEN + EAP_EMSK_LEN);
	if (eapKeyData) {
		emsk = os_memdup(eapKeyData + EAP_TLS_KEY_LEN, EAP_EMSK_LEN);
		bin_clear_free(eapKeyData, EAP_TLS_KEY_LEN + EAP_EMSK_LEN);
		if (!emsk)
			return NULL;
		*len = EAP_EMSK_LEN;
		wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Derived EMSK",
			    emsk, EAP_EMSK_LEN);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Failed to derive EMSK");
		emsk = NULL;
	}

	return emsk;
}