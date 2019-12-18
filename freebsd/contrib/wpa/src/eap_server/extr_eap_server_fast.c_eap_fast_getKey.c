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
struct eap_fast_data {scalar_t__ state; int /*<<< orphan*/  simck; } ;

/* Variables and functions */
 size_t EAP_FAST_KEY_LEN ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ eap_fast_derive_eap_msk (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 

__attribute__((used)) static u8 * eap_fast_getKey(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_fast_data *data = priv;
	u8 *eapKeyData;

	if (data->state != SUCCESS)
		return NULL;

	eapKeyData = os_malloc(EAP_FAST_KEY_LEN);
	if (eapKeyData == NULL)
		return NULL;

	if (eap_fast_derive_eap_msk(data->simck, eapKeyData) < 0) {
		os_free(eapKeyData);
		return NULL;
	}
	*len = EAP_FAST_KEY_LEN;

	return eapKeyData;
}