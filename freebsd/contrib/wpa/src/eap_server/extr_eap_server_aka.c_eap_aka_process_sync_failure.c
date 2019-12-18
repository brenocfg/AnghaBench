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
struct wpabuf {int dummy; } ;
struct eap_sm {int /*<<< orphan*/  eap_sim_db_priv; } ;
struct eap_sim_attrs {int /*<<< orphan*/ * auts; } ;
struct eap_aka_data {int auts_reported; void* notification; int /*<<< orphan*/  rand; int /*<<< orphan*/  permanent; } ;

/* Variables and functions */
 void* EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  NOTIFICATION ; 
 int /*<<< orphan*/  eap_aka_fullauth (struct eap_sm*,struct eap_aka_data*) ; 
 int /*<<< orphan*/  eap_aka_state (struct eap_aka_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ eap_sim_db_resynchronize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_aka_process_sync_failure(struct eap_sm *sm,
					 struct eap_aka_data *data,
					 struct wpabuf *respData,
					 struct eap_sim_attrs *attr)
{
	wpa_printf(MSG_DEBUG, "EAP-AKA: Processing Synchronization-Failure");

	if (attr->auts == NULL) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Synchronization-Failure "
			   "message did not include valid AT_AUTS");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}

	/* Avoid re-reporting AUTS when processing pending EAP packet by
	 * maintaining a local flag stating whether this AUTS has already been
	 * reported. */
	if (!data->auts_reported &&
	    eap_sim_db_resynchronize(sm->eap_sim_db_priv, data->permanent,
				     attr->auts, data->rand)) {
		wpa_printf(MSG_WARNING, "EAP-AKA: Resynchronization failed");
		data->notification = EAP_SIM_GENERAL_FAILURE_BEFORE_AUTH;
		eap_aka_state(data, NOTIFICATION);
		return;
	}
	data->auts_reported = 1;

	/* Remain in CHALLENGE state to re-try after resynchronization */
	eap_aka_fullauth(sm, data);
}