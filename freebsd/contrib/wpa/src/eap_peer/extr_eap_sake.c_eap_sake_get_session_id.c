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
struct eap_sake_data {scalar_t__ state; int /*<<< orphan*/  rand_s; } ;

/* Variables and functions */
 int EAP_SAKE_RAND_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_SAKE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u8 * eap_sake_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_sake_data *data = priv;
	u8 *id;

	if (data->state != SUCCESS)
		return NULL;

	*len = 1 + 2 * EAP_SAKE_RAND_LEN;
	id = os_malloc(*len);
	if (id == NULL)
		return NULL;

	id[0] = EAP_TYPE_SAKE;
	os_memcpy(id + 1, data->rand_s, EAP_SAKE_RAND_LEN);
	os_memcpy(id + 1 + EAP_SAKE_RAND_LEN, data->rand_s, EAP_SAKE_RAND_LEN);
	wpa_hexdump(MSG_DEBUG, "EAP-SAKE: Derived Session-Id", id, *len);

	return id;
}