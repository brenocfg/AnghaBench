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
struct ttls_parse_avp {scalar_t__* mschapv2; scalar_t__ eapdata; scalar_t__ mschapv2_error; } ;
struct eap_ttls_data {int phase2_success; scalar_t__ ident; int /*<<< orphan*/  auth_response; int /*<<< orphan*/  auth_response_valid; } ;
struct eap_sm {int dummy; } ;
struct eap_method_ret {int /*<<< orphan*/  decision; void* methodState; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  DECISION_UNCOND_SUCC ; 
 void* METHOD_DONE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 scalar_t__ mschapv2_verify_auth_response (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int eap_ttls_process_phase2_mschapv2(struct eap_sm *sm,
					    struct eap_ttls_data *data,
					    struct eap_method_ret *ret,
					    struct ttls_parse_avp *parse)
{
#ifdef EAP_MSCHAPv2
	if (parse->mschapv2_error) {
		wpa_printf(MSG_DEBUG, "EAP-TTLS/MSCHAPV2: Received "
			   "MS-CHAP-Error - failed");
		ret->methodState = METHOD_DONE;
		ret->decision = DECISION_FAIL;
		/* Reply with empty data to ACK error */
		return 1;
	}

	if (parse->mschapv2 == NULL) {
#ifdef EAP_TNC
		if (data->phase2_success && parse->eapdata) {
			/*
			 * Allow EAP-TNC to be started after successfully
			 * completed MSCHAPV2.
			 */
			return 1;
		}
#endif /* EAP_TNC */
		wpa_printf(MSG_WARNING, "EAP-TTLS: no MS-CHAP2-Success AVP "
			   "received for Phase2 MSCHAPV2");
		return -1;
	}
	if (parse->mschapv2[0] != data->ident) {
		wpa_printf(MSG_WARNING, "EAP-TTLS: Ident mismatch for Phase 2 "
			   "MSCHAPV2 (received Ident 0x%02x, expected 0x%02x)",
			   parse->mschapv2[0], data->ident);
		return -1;
	}
	if (!data->auth_response_valid ||
	    mschapv2_verify_auth_response(data->auth_response,
					  parse->mschapv2 + 1, 42)) {
		wpa_printf(MSG_WARNING, "EAP-TTLS: Invalid authenticator "
			   "response in Phase 2 MSCHAPV2 success request");
		return -1;
	}

	wpa_printf(MSG_INFO, "EAP-TTLS: Phase 2 MSCHAPV2 "
		   "authentication succeeded");
	ret->methodState = METHOD_DONE;
	ret->decision = DECISION_UNCOND_SUCC;
	data->phase2_success = 1;

	/*
	 * Reply with empty data; authentication server will reply
	 * with EAP-Success after this.
	 */
	return 1;
#else /* EAP_MSCHAPv2 */
	wpa_printf(MSG_ERROR, "EAP-TTLS: MSCHAPv2 not included in the build");
	return -1;
#endif /* EAP_MSCHAPv2 */
}