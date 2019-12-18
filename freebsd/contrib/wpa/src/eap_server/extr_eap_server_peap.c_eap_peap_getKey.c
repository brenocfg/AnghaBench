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
struct eap_peap_data {scalar_t__ state; int /*<<< orphan*/  ssl; int /*<<< orphan*/  ipmk; int /*<<< orphan*/  peap_version; scalar_t__ crypto_binding_used; } ;
typedef  int /*<<< orphan*/  csk ;

/* Variables and functions */
 scalar_t__ EAP_EMSK_LEN ; 
 size_t EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * eap_server_tls_derive_key (struct eap_sm*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ peap_prfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static u8 * eap_peap_getKey(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_peap_data *data = priv;
	u8 *eapKeyData;

	if (data->state != SUCCESS)
		return NULL;

	if (data->crypto_binding_used) {
		u8 csk[128];
		/*
		 * Note: It looks like Microsoft implementation requires null
		 * termination for this label while the one used for deriving
		 * IPMK|CMK did not use null termination.
		 */
		if (peap_prfplus(data->peap_version, data->ipmk, 40,
				 "Session Key Generating Function",
				 (u8 *) "\00", 1, csk, sizeof(csk)) < 0)
			return NULL;
		wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: CSK", csk, sizeof(csk));
		eapKeyData = os_malloc(EAP_TLS_KEY_LEN);
		if (eapKeyData) {
			os_memcpy(eapKeyData, csk, EAP_TLS_KEY_LEN);
			*len = EAP_TLS_KEY_LEN;
			wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Derived key",
				    eapKeyData, EAP_TLS_KEY_LEN);
		} else {
			wpa_printf(MSG_DEBUG, "EAP-PEAP: Failed to derive "
				   "key");
		}

		forced_memzero(csk, sizeof(csk));

		return eapKeyData;
	}

	/* TODO: PEAPv1 - different label in some cases */
	eapKeyData = eap_server_tls_derive_key(sm, &data->ssl,
					       "client EAP encryption", NULL, 0,
					       EAP_TLS_KEY_LEN + EAP_EMSK_LEN);
	if (eapKeyData) {
		os_memset(eapKeyData + EAP_TLS_KEY_LEN, 0, EAP_EMSK_LEN);
		*len = EAP_TLS_KEY_LEN;
		wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Derived key",
			    eapKeyData, EAP_TLS_KEY_LEN);
	} else {
		wpa_printf(MSG_DEBUG, "EAP-PEAP: Failed to derive key");
	}

	return eapKeyData;
}