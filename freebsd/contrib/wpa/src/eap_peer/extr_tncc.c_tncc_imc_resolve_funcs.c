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
struct tnc_if_imc {void* Terminate; void* BatchEnding; void* ReceiveMessage; void* NotifyConnectionChange; int /*<<< orphan*/ * ProvideBindFunction; int /*<<< orphan*/ * BeginHandshake; int /*<<< orphan*/ * Initialize; void* dlhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 void* tncc_get_sym (void*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tncc_imc_resolve_funcs(struct tnc_if_imc *imc)
{
	void *handle = imc->dlhandle;

	/* Mandatory IMC functions */
	imc->Initialize = tncc_get_sym(handle, "TNC_IMC_Initialize");
	if (imc->Initialize == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMC does not export "
			   "TNC_IMC_Initialize");
		return -1;
	}

	imc->BeginHandshake = tncc_get_sym(handle, "TNC_IMC_BeginHandshake");
	if (imc->BeginHandshake == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMC does not export "
			   "TNC_IMC_BeginHandshake");
		return -1;
	}

	imc->ProvideBindFunction =
		tncc_get_sym(handle, "TNC_IMC_ProvideBindFunction");
	if (imc->ProvideBindFunction == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMC does not export "
			   "TNC_IMC_ProvideBindFunction");
		return -1;
	}

	/* Optional IMC functions */
	imc->NotifyConnectionChange =
		tncc_get_sym(handle, "TNC_IMC_NotifyConnectionChange");
	imc->ReceiveMessage = tncc_get_sym(handle, "TNC_IMC_ReceiveMessage");
	imc->BatchEnding = tncc_get_sym(handle, "TNC_IMC_BatchEnding");
	imc->Terminate = tncc_get_sym(handle, "TNC_IMC_Terminate");

	return 0;
}