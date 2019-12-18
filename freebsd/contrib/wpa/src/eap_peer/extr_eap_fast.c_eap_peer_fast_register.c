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
struct eap_method {int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  init_for_reauth; int /*<<< orphan*/  deinit_for_reauth; int /*<<< orphan*/  has_reauth_data; int /*<<< orphan*/  get_status; int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isKeyAvailable; int /*<<< orphan*/  process; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PEER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_FAST ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  eap_fast_deinit ; 
 int /*<<< orphan*/  eap_fast_deinit_for_reauth ; 
 int /*<<< orphan*/  eap_fast_getKey ; 
 int /*<<< orphan*/  eap_fast_get_emsk ; 
 int /*<<< orphan*/  eap_fast_get_session_id ; 
 int /*<<< orphan*/  eap_fast_get_status ; 
 int /*<<< orphan*/  eap_fast_has_reauth_data ; 
 int /*<<< orphan*/  eap_fast_init ; 
 int /*<<< orphan*/  eap_fast_init_for_reauth ; 
 int /*<<< orphan*/  eap_fast_isKeyAvailable ; 
 int /*<<< orphan*/  eap_fast_process ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 

int eap_peer_fast_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_FAST, "FAST");
	if (eap == NULL)
		return -1;

	eap->init = eap_fast_init;
	eap->deinit = eap_fast_deinit;
	eap->process = eap_fast_process;
	eap->isKeyAvailable = eap_fast_isKeyAvailable;
	eap->getKey = eap_fast_getKey;
	eap->getSessionId = eap_fast_get_session_id;
	eap->get_status = eap_fast_get_status;
#if 0
	eap->has_reauth_data = eap_fast_has_reauth_data;
	eap->deinit_for_reauth = eap_fast_deinit_for_reauth;
	eap->init_for_reauth = eap_fast_init_for_reauth;
#endif
	eap->get_emsk = eap_fast_get_emsk;

	return eap_peer_method_register(eap);
}