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
struct eap_mschapv2_data {scalar_t__ state; int /*<<< orphan*/  master_key; int /*<<< orphan*/  master_key_valid; } ;

/* Variables and functions */
 int MSCHAPV2_KEY_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ get_asymetric_start_key (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u8 * eap_mschapv2_getKey(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_mschapv2_data *data = priv;
	u8 *key;

	if (data->state != SUCCESS || !data->master_key_valid)
		return NULL;

	*len = 2 * MSCHAPV2_KEY_LEN;
	key = os_malloc(*len);
	if (key == NULL)
		return NULL;
	/* MSK = server MS-MPPE-Recv-Key | MS-MPPE-Send-Key */
	if (get_asymetric_start_key(data->master_key, key, MSCHAPV2_KEY_LEN, 0,
				    1) < 0 ||
	    get_asymetric_start_key(data->master_key, key + MSCHAPV2_KEY_LEN,
				    MSCHAPV2_KEY_LEN, 1, 1) < 0) {
		os_free(key);
		return NULL;
	}
	wpa_hexdump_key(MSG_DEBUG, "EAP-MSCHAPV2: Derived key", key, *len);

	return key;
}