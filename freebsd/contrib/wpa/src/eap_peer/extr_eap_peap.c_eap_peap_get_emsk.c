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
struct eap_peap_data {scalar_t__ key_data; scalar_t__ crypto_binding_used; int /*<<< orphan*/  phase2_success; } ;

/* Variables and functions */
 size_t EAP_EMSK_LEN ; 
 scalar_t__ EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/ * os_memdup (scalar_t__,size_t) ; 

__attribute__((used)) static u8 * eap_peap_get_emsk(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_peap_data *data = priv;
	u8 *key;

	if (!data->key_data || !data->phase2_success)
		return NULL;

	if (data->crypto_binding_used) {
		/* [MS-PEAP] does not define EMSK derivation */
		return NULL;
	}

	key = os_memdup(data->key_data + EAP_TLS_KEY_LEN, EAP_EMSK_LEN);
	if (!key)
		return NULL;

	*len = EAP_EMSK_LEN;

	return key;
}