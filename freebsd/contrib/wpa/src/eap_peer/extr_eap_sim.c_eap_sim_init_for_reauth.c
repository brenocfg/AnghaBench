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
struct eap_sm {int dummy; } ;
struct eap_sim_data {scalar_t__ num_notification; scalar_t__ num_id_req; int /*<<< orphan*/  nonce_mt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONTINUE ; 
 int /*<<< orphan*/  EAP_SIM_NONCE_MT_LEN ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  eap_sim_deinit (struct eap_sm*,struct eap_sim_data*) ; 
 int /*<<< orphan*/  eap_sim_state (struct eap_sim_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ random_get_bytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void * eap_sim_init_for_reauth(struct eap_sm *sm, void *priv)
{
	struct eap_sim_data *data = priv;
	if (random_get_bytes(data->nonce_mt, EAP_SIM_NONCE_MT_LEN)) {
		wpa_printf(MSG_WARNING, "EAP-SIM: Failed to get random data "
			   "for NONCE_MT");
		eap_sim_deinit(sm, data);
		return NULL;
	}
	data->num_id_req = 0;
	data->num_notification = 0;
	eap_sim_state(data, CONTINUE);
	return priv;
}