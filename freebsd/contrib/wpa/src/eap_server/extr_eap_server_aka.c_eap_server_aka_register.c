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
 int /*<<< orphan*/  EAP_TYPE_AKA ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 int /*<<< orphan*/  eap_aka_buildReq ; 
 int /*<<< orphan*/  eap_aka_check ; 
 int /*<<< orphan*/  eap_aka_getKey ; 
 int /*<<< orphan*/  eap_aka_get_emsk ; 
 int /*<<< orphan*/  eap_aka_get_session_id ; 
 int /*<<< orphan*/  eap_aka_init ; 
 int /*<<< orphan*/  eap_aka_isDone ; 
 int /*<<< orphan*/  eap_aka_isSuccess ; 
 int /*<<< orphan*/  eap_aka_process ; 
 int /*<<< orphan*/  eap_aka_reset ; 
 struct eap_method* eap_server_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_server_method_register (struct eap_method*) ; 

int eap_server_aka_register(void)
{
	struct eap_method *eap;

	eap = eap_server_method_alloc(EAP_SERVER_METHOD_INTERFACE_VERSION,
				      EAP_VENDOR_IETF, EAP_TYPE_AKA, "AKA");
	if (eap == NULL)
		return -1;

	eap->init = eap_aka_init;
	eap->reset = eap_aka_reset;
	eap->buildReq = eap_aka_buildReq;
	eap->check = eap_aka_check;
	eap->process = eap_aka_process;
	eap->isDone = eap_aka_isDone;
	eap->getKey = eap_aka_getKey;
	eap->isSuccess = eap_aka_isSuccess;
	eap->get_emsk = eap_aka_get_emsk;
	eap->getSessionId = eap_aka_get_session_id;

	return eap_server_method_register(eap);
}