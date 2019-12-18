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
struct eap_method {int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  init_for_reauth; int /*<<< orphan*/  deinit_for_reauth; int /*<<< orphan*/  has_reauth_data; int /*<<< orphan*/  get_status; int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isKeyAvailable; int /*<<< orphan*/  process; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PEER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_PEAP ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  eap_peap_deinit ; 
 int /*<<< orphan*/  eap_peap_deinit_for_reauth ; 
 int /*<<< orphan*/  eap_peap_getKey ; 
 int /*<<< orphan*/  eap_peap_get_emsk ; 
 int /*<<< orphan*/  eap_peap_get_session_id ; 
 int /*<<< orphan*/  eap_peap_get_status ; 
 int /*<<< orphan*/  eap_peap_has_reauth_data ; 
 int /*<<< orphan*/  eap_peap_init ; 
 int /*<<< orphan*/  eap_peap_init_for_reauth ; 
 int /*<<< orphan*/  eap_peap_isKeyAvailable ; 
 int /*<<< orphan*/  eap_peap_process ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 

int eap_peer_peap_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_PEAP, "PEAP");
	if (eap == NULL)
		return -1;

	eap->init = eap_peap_init;
	eap->deinit = eap_peap_deinit;
	eap->process = eap_peap_process;
	eap->isKeyAvailable = eap_peap_isKeyAvailable;
	eap->getKey = eap_peap_getKey;
	eap->get_emsk = eap_peap_get_emsk;
	eap->get_status = eap_peap_get_status;
	eap->has_reauth_data = eap_peap_has_reauth_data;
	eap->deinit_for_reauth = eap_peap_deinit_for_reauth;
	eap->init_for_reauth = eap_peap_init_for_reauth;
	eap->getSessionId = eap_peap_get_session_id;

	return eap_peer_method_register(eap);
}