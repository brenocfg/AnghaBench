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
struct eap_method {int /*<<< orphan*/  isSuccess; int /*<<< orphan*/  isDone; int /*<<< orphan*/  process; int /*<<< orphan*/  check; int /*<<< orphan*/  buildReq; int /*<<< orphan*/  reset; int /*<<< orphan*/  init; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_SERVER_METHOD_INTERFACE_VERSION ; 
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  EAP_VENDOR_IETF ; 
 struct eap_method* eap_server_method_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int eap_server_method_register (struct eap_method*) ; 
 int /*<<< orphan*/  eap_tnc_buildReq ; 
 int /*<<< orphan*/  eap_tnc_check ; 
 int /*<<< orphan*/  eap_tnc_init ; 
 int /*<<< orphan*/  eap_tnc_isDone ; 
 int /*<<< orphan*/  eap_tnc_isSuccess ; 
 int /*<<< orphan*/  eap_tnc_process ; 
 int /*<<< orphan*/  eap_tnc_reset ; 

int eap_server_tnc_register(void)
{
	struct eap_method *eap;

	eap = eap_server_method_alloc(EAP_SERVER_METHOD_INTERFACE_VERSION,
				      EAP_VENDOR_IETF, EAP_TYPE_TNC, "TNC");
	if (eap == NULL)
		return -1;

	eap->init = eap_tnc_init;
	eap->reset = eap_tnc_reset;
	eap->buildReq = eap_tnc_buildReq;
	eap->check = eap_tnc_check;
	eap->process = eap_tnc_process;
	eap->isDone = eap_tnc_isDone;
	eap->isSuccess = eap_tnc_isSuccess;

	return eap_server_method_register(eap);
}