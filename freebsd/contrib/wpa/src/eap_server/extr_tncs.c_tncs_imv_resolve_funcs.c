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
struct tnc_if_imv {void* Terminate; void* BatchEnding; void* ReceiveMessage; void* NotifyConnectionChange; int /*<<< orphan*/ * ProvideBindFunction; int /*<<< orphan*/ * SolicitRecommendation; int /*<<< orphan*/ * Initialize; void* dlhandle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_ERROR ; 
 void* tncs_get_sym (void*,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int tncs_imv_resolve_funcs(struct tnc_if_imv *imv)
{
	void *handle = imv->dlhandle;

	/* Mandatory IMV functions */
	imv->Initialize = tncs_get_sym(handle, "TNC_IMV_Initialize");
	if (imv->Initialize == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMV does not export "
			   "TNC_IMV_Initialize");
		return -1;
	}

	imv->SolicitRecommendation = tncs_get_sym(
		handle, "TNC_IMV_SolicitRecommendation");
	if (imv->SolicitRecommendation == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMV does not export "
			   "TNC_IMV_SolicitRecommendation");
		return -1;
	}

	imv->ProvideBindFunction =
		tncs_get_sym(handle, "TNC_IMV_ProvideBindFunction");
	if (imv->ProvideBindFunction == NULL) {
		wpa_printf(MSG_ERROR, "TNC: IMV does not export "
			   "TNC_IMV_ProvideBindFunction");
		return -1;
	}

	/* Optional IMV functions */
	imv->NotifyConnectionChange =
		tncs_get_sym(handle, "TNC_IMV_NotifyConnectionChange");
	imv->ReceiveMessage = tncs_get_sym(handle, "TNC_IMV_ReceiveMessage");
	imv->BatchEnding = tncs_get_sym(handle, "TNC_IMV_BatchEnding");
	imv->Terminate = tncs_get_sym(handle, "TNC_IMV_Terminate");

	return 0;
}