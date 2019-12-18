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
struct eap_sim_data {scalar_t__ state; int num_chal; int /*<<< orphan*/  reauth_mac; int /*<<< orphan*/  nonce_s; int /*<<< orphan*/  nonce_mt; int /*<<< orphan*/  rand; int /*<<< orphan*/  reauth; } ;

/* Variables and functions */
 int EAP_SIM_MAC_LEN ; 
 int EAP_SIM_NONCE_MT_LEN ; 
 int EAP_SIM_NONCE_S_LEN ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int GSM_RAND_LEN ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/ * os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static u8 * eap_sim_get_session_id(struct eap_sm *sm, void *priv, size_t *len)
{
	struct eap_sim_data *data = priv;
	u8 *id;

	if (data->state != SUCCESS)
		return NULL;

	if (!data->reauth)
		*len = 1 + data->num_chal * GSM_RAND_LEN + EAP_SIM_NONCE_MT_LEN;
	else
		*len = 1 + EAP_SIM_NONCE_S_LEN + EAP_SIM_MAC_LEN;
	id = os_malloc(*len);
	if (id == NULL)
		return NULL;

	id[0] = EAP_TYPE_SIM;
	if (!data->reauth) {
		os_memcpy(id + 1, data->rand, data->num_chal * GSM_RAND_LEN);
		os_memcpy(id + 1 + data->num_chal * GSM_RAND_LEN,
			  data->nonce_mt, EAP_SIM_NONCE_MT_LEN);
	} else {
		os_memcpy(id + 1, data->nonce_s, EAP_SIM_NONCE_S_LEN);
		os_memcpy(id + 1 + EAP_SIM_NONCE_S_LEN, data->reauth_mac,
			  EAP_SIM_MAC_LEN);
	}
	wpa_hexdump(MSG_DEBUG, "EAP-SIM: Derived Session-Id", id, *len);

	return id;
}