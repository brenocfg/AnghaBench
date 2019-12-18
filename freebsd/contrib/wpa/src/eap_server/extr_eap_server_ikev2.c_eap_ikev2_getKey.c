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
struct eap_ikev2_data {scalar_t__ state; int /*<<< orphan*/  keymat; int /*<<< orphan*/  keymat_ok; } ;

/* Variables and functions */
 scalar_t__ DONE ; 
 size_t EAP_MSK_LEN ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static u8 * eap_ikev2_getKey(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_ikev2_data *data = priv;
	u8 *key;

	if (data->state != DONE || !data->keymat_ok)
		return NULL;

	key = os_malloc(EAP_MSK_LEN);
	if (key) {
		os_memcpy(key, data->keymat, EAP_MSK_LEN);
		*len = EAP_MSK_LEN;
	}

	return key;
}