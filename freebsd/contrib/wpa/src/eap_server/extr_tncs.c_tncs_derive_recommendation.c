#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tncs_data {int done; int recommendation; int /*<<< orphan*/  connectionID; struct tnc_if_imv* imv; scalar_t__ tncs_message; TYPE_1__* imv_data; } ;
struct tnc_if_imv {size_t imvID; struct tnc_if_imv* next; } ;
typedef  enum tncs_process_res { ____Placeholder_tncs_process_res } tncs_process_res ;
typedef  enum IMV_Action_Recommendation { ____Placeholder_IMV_Action_Recommendation } IMV_Action_Recommendation ;
struct TYPE_2__ {scalar_t__ recommendation; } ;
typedef  scalar_t__ TNC_IMV_Action_Recommendation ;
typedef  int /*<<< orphan*/  TNC_ConnectionState ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int TNCCS_PROCESS_ERROR ; 
 int TNCCS_PROCESS_OK_NO_RECOMMENDATION ; 
 int TNCCS_RECOMMENDATION_ALLOW ; 
 int TNCCS_RECOMMENDATION_ISOLATE ; 
 int TNCCS_RECOMMENDATION_NO_ACCESS ; 
 int TNCCS_RECOMMENDATION_NO_RECOMMENDATION ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_ALLOWED ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_ISOLATED ; 
 int /*<<< orphan*/  TNC_CONNECTION_STATE_ACCESS_NONE ; 
#define  TNC_IMV_ACTION_RECOMMENDATION_ALLOW 131 
#define  TNC_IMV_ACTION_RECOMMENDATION_ISOLATE 130 
#define  TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS 129 
#define  TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION 128 
 int /*<<< orphan*/  TNC_TNCCS_RECOMMENDATION ; 
 int /*<<< orphan*/  os_free (scalar_t__) ; 
 int /*<<< orphan*/  os_snprintf (scalar_t__,int,char*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  tncs_imv_notify_connection_change (struct tnc_if_imv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tncs_solicit_recommendation (struct tncs_data*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static enum tncs_process_res tncs_derive_recommendation(struct tncs_data *tncs)
{
	enum IMV_Action_Recommendation rec;
	struct tnc_if_imv *imv;
	TNC_ConnectionState state;
	char *txt;

	wpa_printf(MSG_DEBUG, "TNC: No more messages from IMVs");

	if (tncs->done)
		return TNCCS_PROCESS_OK_NO_RECOMMENDATION;

	tncs_solicit_recommendation(tncs);

	/* Select the most restrictive recommendation */
	rec = TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION;
	for (imv = tncs->imv; imv; imv = imv->next) {
		TNC_IMV_Action_Recommendation irec;
		irec = tncs->imv_data[imv->imvID].recommendation;
		if (irec == TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS)
			rec = TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS;
		if (irec == TNC_IMV_ACTION_RECOMMENDATION_ISOLATE &&
		    rec != TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS)
			rec = TNC_IMV_ACTION_RECOMMENDATION_ISOLATE;
		if (irec == TNC_IMV_ACTION_RECOMMENDATION_ALLOW &&
		    rec == TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION)
			rec = TNC_IMV_ACTION_RECOMMENDATION_ALLOW;
	}

	wpa_printf(MSG_DEBUG, "TNC: Recommendation: %d", rec);
	tncs->recommendation = rec;
	tncs->done = 1;

	txt = NULL;
	switch (rec) {
	case TNC_IMV_ACTION_RECOMMENDATION_ALLOW:
	case TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION:
		txt = "allow";
		state = TNC_CONNECTION_STATE_ACCESS_ALLOWED;
		break;
	case TNC_IMV_ACTION_RECOMMENDATION_ISOLATE:
		txt = "isolate";
		state = TNC_CONNECTION_STATE_ACCESS_ISOLATED;
		break;
	case TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS:
		txt = "none";
		state = TNC_CONNECTION_STATE_ACCESS_NONE;
		break;
	default:
		state = TNC_CONNECTION_STATE_ACCESS_ALLOWED;
		break;
	}

	if (txt) {
		os_free(tncs->tncs_message);
		tncs->tncs_message = os_zalloc(200);
		if (tncs->tncs_message) {
			os_snprintf(tncs->tncs_message, 199,
				    "<TNCC-TNCS-Message><Type>%08X</Type>"
				    "<XML><TNCCS-Recommendation type=\"%s\">"
				    "</TNCCS-Recommendation></XML>"
				    "</TNCC-TNCS-Message>",
				    TNC_TNCCS_RECOMMENDATION, txt);
		}
	}

	for (imv = tncs->imv; imv; imv = imv->next) {
		tncs_imv_notify_connection_change(imv, tncs->connectionID,
						  state);
	}

	switch (rec) {
	case TNC_IMV_ACTION_RECOMMENDATION_ALLOW:
		return TNCCS_RECOMMENDATION_ALLOW;
	case TNC_IMV_ACTION_RECOMMENDATION_NO_ACCESS:
		return TNCCS_RECOMMENDATION_NO_ACCESS;
	case TNC_IMV_ACTION_RECOMMENDATION_ISOLATE:
		return TNCCS_RECOMMENDATION_ISOLATE;
	case TNC_IMV_ACTION_RECOMMENDATION_NO_RECOMMENDATION:
		return TNCCS_RECOMMENDATION_NO_RECOMMENDATION;
	default:
		return TNCCS_PROCESS_ERROR;
	}
}