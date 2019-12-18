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
struct eap_method {int /*<<< orphan*/  get_error_code; int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  get_identity; int /*<<< orphan*/  init_for_reauth; int /*<<< orphan*/  deinit_for_reauth; int /*<<< orphan*/  has_reauth_data; int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isKeyAvailable; int /*<<< orphan*/  process; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PEER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_SIM ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 
 int /*<<< orphan*/  eap_sim_deinit ; 
 int /*<<< orphan*/  eap_sim_deinit_for_reauth ; 
 int /*<<< orphan*/  eap_sim_getKey ; 
 int /*<<< orphan*/  eap_sim_get_emsk ; 
 int /*<<< orphan*/  eap_sim_get_error_code ; 
 int /*<<< orphan*/  eap_sim_get_identity ; 
 int /*<<< orphan*/  eap_sim_get_session_id ; 
 int /*<<< orphan*/  eap_sim_has_reauth_data ; 
 int /*<<< orphan*/  eap_sim_init ; 
 int /*<<< orphan*/  eap_sim_init_for_reauth ; 
 int /*<<< orphan*/  eap_sim_isKeyAvailable ; 
 int /*<<< orphan*/  eap_sim_process ; 

int eap_peer_sim_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_SIM, "SIM");
	if (eap == NULL)
		return -1;

	eap->init = eap_sim_init;
	eap->deinit = eap_sim_deinit;
	eap->process = eap_sim_process;
	eap->isKeyAvailable = eap_sim_isKeyAvailable;
	eap->getKey = eap_sim_getKey;
	eap->getSessionId = eap_sim_get_session_id;
	eap->has_reauth_data = eap_sim_has_reauth_data;
	eap->deinit_for_reauth = eap_sim_deinit_for_reauth;
	eap->init_for_reauth = eap_sim_init_for_reauth;
	eap->get_identity = eap_sim_get_identity;
	eap->get_emsk = eap_sim_get_emsk;
	eap->get_error_code = eap_sim_get_error_code;

	return eap_peer_method_register(eap);
}