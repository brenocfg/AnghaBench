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
struct eap_peap_data {int /*<<< orphan*/ * key_data; } ;

/* Variables and functions */
 scalar_t__ EAP_EMSK_LEN ; 
 scalar_t__ EAP_TLS_KEY_LEN ; 
 int /*<<< orphan*/  bin_clear_free (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void eap_peap_free_key(struct eap_peap_data *data)
{
	if (data->key_data) {
		bin_clear_free(data->key_data, EAP_TLS_KEY_LEN + EAP_EMSK_LEN);
		data->key_data = NULL;
	}
}