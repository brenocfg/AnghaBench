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
struct TYPE_2__ {int /*<<< orphan*/  tls_out; } ;
struct eap_ttls_data {int phase2_success; scalar_t__ decision_succ; int ready_for_tnc; TYPE_1__ ssl; int /*<<< orphan*/  tnc_started; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {scalar_t__ methodState; scalar_t__ decision; int /*<<< orphan*/  allowNotifications; } ;

/* Variables and functions */
 scalar_t__ DECISION_COND_SUCC ; 
 scalar_t__ DECISION_FAIL ; 
 scalar_t__ DECISION_UNCOND_SUCC ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ METHOD_DONE ; 
 scalar_t__ METHOD_MAY_CONT ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eap_ttls_check_auth_status(struct eap_sm *sm,
				       struct eap_ttls_data *data,
				       struct eap_method_ret *ret)
{
	if (ret->methodState == METHOD_DONE) {
		ret->allowNotifications = FALSE;
		if (ret->decision == DECISION_UNCOND_SUCC ||
		    ret->decision == DECISION_COND_SUCC) {
			wpa_printf(MSG_DEBUG, "EAP-TTLS: Authentication "
				   "completed successfully");
			data->phase2_success = 1;
			data->decision_succ = ret->decision;
#ifdef EAP_TNC
			if (!data->ready_for_tnc && !data->tnc_started) {
				/*
				 * TNC may be required as the next
				 * authentication method within the tunnel.
				 */
				ret->methodState = METHOD_MAY_CONT;
				data->ready_for_tnc = 1;
			}
#endif /* EAP_TNC */
		}
	} else if (ret->methodState == METHOD_MAY_CONT &&
		   (ret->decision == DECISION_UNCOND_SUCC ||
		    ret->decision == DECISION_COND_SUCC)) {
			wpa_printf(MSG_DEBUG, "EAP-TTLS: Authentication "
				   "completed successfully (MAY_CONT)");
			data->phase2_success = 1;
			data->decision_succ = ret->decision;
	} else if (data->decision_succ != DECISION_FAIL &&
		   data->phase2_success &&
		   !data->ssl.tls_out) {
		/*
		 * This is needed to cover the case where the final Phase 2
		 * message gets fragmented since fragmentation clears
		 * decision back to FAIL.
		 */
		wpa_printf(MSG_DEBUG,
			   "EAP-TTLS: Restore success decision after fragmented frame sent completely");
		ret->decision = data->decision_succ;
	}
}