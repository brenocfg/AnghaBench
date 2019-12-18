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
struct eap_method {int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isKeyAvailable; int /*<<< orphan*/  process; int /*<<< orphan*/  deinit; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_PEER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_SAKE ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct eap_method* eap_peer_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_peer_method_register (struct eap_method*) ; 
 int /*<<< orphan*/  eap_sake_deinit ; 
 int /*<<< orphan*/  eap_sake_getKey ; 
 int /*<<< orphan*/  eap_sake_get_emsk ; 
 int /*<<< orphan*/  eap_sake_get_session_id ; 
 int /*<<< orphan*/  eap_sake_init ; 
 int /*<<< orphan*/  eap_sake_isKeyAvailable ; 
 int /*<<< orphan*/  eap_sake_process ; 

int eap_peer_sake_register(void)
{
	struct eap_method *eap;

	eap = eap_peer_method_alloc(EAP_PEER_METHOD_INTERFACE_VERSION,
				    EAP_VENDOR_IETF, EAP_TYPE_SAKE, "SAKE");
	if (eap == NULL)
		return -1;

	eap->init = eap_sake_init;
	eap->deinit = eap_sake_deinit;
	eap->process = eap_sake_process;
	eap->isKeyAvailable = eap_sake_isKeyAvailable;
	eap->getKey = eap_sake_getKey;
	eap->getSessionId = eap_sake_get_session_id;
	eap->get_emsk = eap_sake_get_emsk;

	return eap_peer_method_register(eap);
}