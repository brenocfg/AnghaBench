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
struct eap_ttls_data {scalar_t__ state; int tnc_started; } ;
struct eap_sm {int /*<<< orphan*/  tnc; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAP_TYPE_TNC ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  PHASE2_METHOD ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ eap_ttls_phase2_eap_init (struct eap_sm*,struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_ttls_state (struct eap_ttls_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_ttls_start_tnc(struct eap_sm *sm, struct eap_ttls_data *data)
{
#ifdef EAP_SERVER_TNC
	if (!sm->tnc || data->state != SUCCESS || data->tnc_started)
		return;

	wpa_printf(MSG_DEBUG, "EAP-TTLS: Initialize TNC");
	if (eap_ttls_phase2_eap_init(sm, data, EAP_TYPE_TNC)) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS: Failed to initialize TNC");
		eap_ttls_state(data, FAILURE);
		return;
	}

	data->tnc_started = 1;
	eap_ttls_state(data, PHASE2_METHOD);
#endif /* EAP_SERVER_TNC */
}