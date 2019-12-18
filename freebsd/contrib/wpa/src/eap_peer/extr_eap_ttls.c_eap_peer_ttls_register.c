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
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 
 int /*<<< orphan*/  eap_ttls_deinit ; 
 int /*<<< orphan*/  eap_ttls_deinit_for_reauth ; 
 int /*<<< orphan*/  eap_ttls_getKey ; 
 int /*<<< orphan*/  eap_ttls_get_emsk ; 
 int /*<<< orphan*/  eap_ttls_get_session_id ; 
 int /*<<< orphan*/  eap_ttls_get_status ; 
 int /*<<< orphan*/  eap_ttls_has_reauth_data ; 
 int /*<<< orphan*/  eap_ttls_init ; 
 int /*<<< orphan*/  eap_ttls_init_for_reauth ; 
 int /*<<< orphan*/  eap_ttls_isKeyAvailable ; 
 int /*<<< orphan*/  eap_ttls_process ; 

int eap_peer_ttls_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_TTLS, "TTLS");
	if (eap == NULL)
		return -1;

	eap->init = eap_ttls_init;
	eap->deinit = eap_ttls_deinit;
	eap->process = eap_ttls_process;
	eap->isKeyAvailable = eap_ttls_isKeyAvailable;
	eap->getKey = eap_ttls_getKey;
	eap->getSessionId = eap_ttls_get_session_id;
	eap->get_status = eap_ttls_get_status;
	eap->has_reauth_data = eap_ttls_has_reauth_data;
	eap->deinit_for_reauth = eap_ttls_deinit_for_reauth;
	eap->init_for_reauth = eap_ttls_init_for_reauth;
	eap->get_emsk = eap_ttls_get_emsk;

	return eap_peer_method_register(eap);
}