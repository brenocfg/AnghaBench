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
struct TYPE_2__ {int /*<<< orphan*/  e; } ;
struct eap_pax_data {scalar_t__ state; TYPE_1__ rand; int /*<<< orphan*/  mk; int /*<<< orphan*/  mac_id; } ;

/* Variables and functions */
 size_t EAP_EMSK_LEN ; 
 int /*<<< orphan*/  EAP_PAX_MK_LEN ; 
 int EAP_PAX_RAND_LEN ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  eap_pax_kdf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 

__attribute__((used)) static u8 * eap_pax_get_emsk(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_pax_data *data = priv;
	u8 *key;

	if (data->state != SUCCESS)
		return NULL;

	key = os_malloc(EAP_EMSK_LEN);
	if (key == NULL)
		return NULL;

	*len = EAP_EMSK_LEN;
	eap_pax_kdf(data->mac_id, data->mk, EAP_PAX_MK_LEN,
		    "Extended Master Session Key",
		    data->rand.e, 2 * EAP_PAX_RAND_LEN,
		    EAP_EMSK_LEN, key);

	return key;
}