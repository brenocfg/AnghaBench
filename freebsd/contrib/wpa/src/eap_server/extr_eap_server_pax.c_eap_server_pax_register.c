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
struct eap_method {int /*<<< orphan*/  getSessionId; int /*<<< orphan*/  get_emsk; int /*<<< orphan*/  isSuccess; int /*<<< orphan*/  getKey; int /*<<< orphan*/  isDone; int /*<<< orphan*/  process; int /*<<< orphan*/  check; int /*<<< orphan*/  buildReq; int /*<<< orphan*/  reset; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SERVER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_PAX ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  eap_pax_buildReq ; 
 int /*<<< orphan*/  eap_pax_check ; 
 int /*<<< orphan*/  eap_pax_getKey ; 
 int /*<<< orphan*/  eap_pax_get_emsk ; 
 int /*<<< orphan*/  eap_pax_get_session_id ; 
 int /*<<< orphan*/  eap_pax_init ; 
 int /*<<< orphan*/  eap_pax_isDone ; 
 int /*<<< orphan*/  eap_pax_isSuccess ; 
 int /*<<< orphan*/  eap_pax_process ; 
 int /*<<< orphan*/  eap_pax_reset ; 
 struct eap_method* eap_server_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_server_method_register (struct eap_method*) ; 

int eap_server_pax_register(void)
{
	struct eap_method *eap;

	eap = eap_server_method_alloc(EAP_SERVER_METHOD_INTERFACE_VERSION,
				      EAP_VENDOR_IETF, EAP_TYPE_PAX, "PAX");
	if (eap == NULL)
		return -1;

	eap->init = eap_pax_init;
	eap->reset = eap_pax_reset;
	eap->buildReq = eap_pax_buildReq;
	eap->check = eap_pax_check;
	eap->process = eap_pax_process;
	eap->isDone = eap_pax_isDone;
	eap->getKey = eap_pax_getKey;
	eap->isSuccess = eap_pax_isSuccess;
	eap->get_emsk = eap_pax_get_emsk;
	eap->getSessionId = eap_pax_get_session_id;

	return eap_server_method_register(eap);
}