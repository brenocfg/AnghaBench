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
struct eap_teap_data {int /*<<< orphan*/  emsk; int /*<<< orphan*/  success; } ;
struct eap_sm {int dummy; } ;

/* Variables and functions */
 size_t EAP_EMSK_LEN ; 
 int /*<<< orphan*/ * os_memdup (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u8 * eap_teap_get_emsk(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_teap_data *data = priv;
	u8 *key;

	if (!data->success)
		return NULL;

	key = os_memdup(data->emsk, EAP_EMSK_LEN);
	if (!key)
		return NULL;

	*len = EAP_EMSK_LEN;

	return key;
}