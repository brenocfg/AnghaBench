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
struct eap_method {int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  isSuccess; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isDone; int /*<<< orphan*/  process; int /*<<< orphan*/  check; int /*<<< orphan*/  buildReq; int /*<<< orphan*/  reset; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SERVER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_TTLS ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct eap_method* eap_server_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_server_method_register (struct eap_method*) ; 
 int /*<<< orphan*/  eap_ttls_buildReq ; 
 int /*<<< orphan*/  eap_ttls_check ; 
 int /*<<< orphan*/  eap_ttls_getKey ; 
 int /*<<< orphan*/  eap_ttls_get_emsk ; 
 int /*<<< orphan*/  eap_ttls_get_session_id ; 
 int /*<<< orphan*/  eap_ttls_init ; 
 int /*<<< orphan*/  eap_ttls_isDone ; 
 int /*<<< orphan*/  eap_ttls_isSuccess ; 
 int /*<<< orphan*/  eap_ttls_process ; 
 int /*<<< orphan*/  eap_ttls_reset ; 

int eap_server_ttls_register(void)
{
	struct eap_method *eap;

	eap = eap_server_method_alloc(EAP_SERVER_METHOD_INTERFACE_VERSION,
				      EAP_VENDOR_IETF, EAP_TYPE_TTLS, "TTLS");
	if (eap == NULL)
		return -1;

	eap->init = eap_ttls_init;
	eap->reset = eap_ttls_reset;
	eap->buildReq = eap_ttls_buildReq;
	eap->check = eap_ttls_check;
	eap->process = eap_ttls_process;
	eap->isDone = eap_ttls_isDone;
	eap->getKey = eap_ttls_getKey;
	eap->isSuccess = eap_ttls_isSuccess;
	eap->getSessionId = eap_ttls_get_session_id;
	eap->get_emsk = eap_ttls_get_emsk;

	return eap_server_method_register(eap);
}