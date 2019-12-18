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
typedef  int /*<<< orphan*/  u8 ;
struct eap_sm {int dummy; } ;
struct eap_fast_data {TYPE_1__* phase2_method; int /*<<< orphan*/ * phase2_priv; } ;
struct TYPE_2__ {scalar_t__ vendor; scalar_t__ method; int /*<<< orphan*/ * (* getKey ) (struct eap_sm*,int /*<<< orphan*/ *,size_t*) ;int /*<<< orphan*/  (* isKeyAvailable ) (struct eap_sm*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 scalar_t__ EAP_TYPE_MSCHAPV2 ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  stub1 (struct eap_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stub2 (struct eap_sm*,int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_fast_get_phase2_key(struct eap_sm *sm,
				   struct eap_fast_data *data,
				   u8 *isk, size_t isk_len)
{
	u8 *key;
	size_t key_len;

	os_memset(isk, 0, isk_len);

	if (data->phase2_method == NULL || data->phase2_priv == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Phase 2 method not "
			   "available");
		return -1;
	}

	if (data->phase2_method->isKeyAvailable == NULL ||
	    data->phase2_method->getKey == NULL)
		return 0;

	if (!data->phase2_method->isKeyAvailable(sm, data->phase2_priv) ||
	    (key = data->phase2_method->getKey(sm, data->phase2_priv,
					       &key_len)) == NULL) {
		wpa_printf(MSG_DEBUG, "EAP-FAST: Could not get key material "
			   "from Phase 2");
		return -1;
	}

	if (key_len > isk_len)
		key_len = isk_len;
	if (key_len == 32 &&
	    data->phase2_method->vendor == EAP_VENDOR_IETF &&
	    data->phase2_method->method == EAP_TYPE_MSCHAPV2) {
		/*
		 * EAP-FAST uses reverse order for MS-MPPE keys when deriving
		 * MSK from EAP-MSCHAPv2. Swap the keys here to get the correct
		 * ISK for EAP-FAST cryptobinding.
		 */
		os_memcpy(isk, key + 16, 16);
		os_memcpy(isk + 16, key, 16);
	} else
		os_memcpy(isk, key, key_len);
	os_free(key);

	return 0;
}