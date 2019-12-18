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
struct eap_peap_data {int /*<<< orphan*/ * key_data; int /*<<< orphan*/  ipmk; int /*<<< orphan*/  peap_version; scalar_t__ crypto_binding_used; int /*<<< orphan*/  phase2_success; } ;
typedef  int /*<<< orphan*/  csk ;

/* Variables and functions */
 size_t EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ peap_prfplus (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static u8 * eap_peap_getKey(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_peap_data *data = priv;
	u8 *key;

	if (data->key_data == NULL || !data->phase2_success)
		return NULL;

	key = os_malloc(EAP_TLS_KEY_LEN);
	if (key == NULL)
		return NULL;

	*len = EAP_TLS_KEY_LEN;

	if (data->crypto_binding_used) {
		u8 csk[128];
		/*
		 * Note: It looks like Microsoft implementation requires null
		 * termination for this label while the one used for deriving
		 * IPMK|CMK did not use null termination.
		 */
		if (peap_prfplus(data->peap_version, data->ipmk, 40,
				 "Session Key Generating Function",
				 (u8 *) "\00", 1, csk, sizeof(csk)) < 0) {
			os_free(key);
			return NULL;
		}
		wpa_hexdump_key(MSG_DEBUG, "EAP-PEAP: CSK", csk, sizeof(csk));
		os_memcpy(key, csk, EAP_TLS_KEY_LEN);
		wpa_hexdump(MSG_DEBUG, "EAP-PEAP: Derived key",
			    key, EAP_TLS_KEY_LEN);
		forced_memzero(csk, sizeof(csk));
	} else
		os_memcpy(key, data->key_data, EAP_TLS_KEY_LEN);

	return key;
}