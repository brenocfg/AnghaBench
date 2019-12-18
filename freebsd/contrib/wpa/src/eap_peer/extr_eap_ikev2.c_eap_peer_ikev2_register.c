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
struct eap_method {int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isKeyAvailable; int /*<<< orphan*/  process; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PEER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_IKEV2 ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  eap_ikev2_deinit ; 
 int /*<<< orphan*/  eap_ikev2_getKey ; 
 int /*<<< orphan*/  eap_ikev2_get_emsk ; 
 int /*<<< orphan*/  eap_ikev2_get_session_id ; 
 int /*<<< orphan*/  eap_ikev2_init ; 
 int /*<<< orphan*/  eap_ikev2_isKeyAvailable ; 
 int /*<<< orphan*/  eap_ikev2_process ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 

int eap_peer_ikev2_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_IKEV2,
				    "IKEV2");
	if (eap == NULL)
		return -1;

	eap->init = eap_ikev2_init;
	eap->deinit = eap_ikev2_deinit;
	eap->process = eap_ikev2_process;
	eap->isKeyAvailable = eap_ikev2_isKeyAvailable;
	eap->getKey = eap_ikev2_getKey;
	eap->get_emsk = eap_ikev2_get_emsk;
	eap->getSessionId = eap_ikev2_get_session_id;

	return eap_peer_method_register(eap);
}