#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct eap_sm {scalar_t__ currentMethod; size_t user_eap_method_index; int currentId; int /*<<< orphan*/ * identity; int /*<<< orphan*/  initiate_reauth_start_sent; TYPE_3__* user; void* start_reauth; void* update_user; int /*<<< orphan*/  identity_len; int /*<<< orphan*/  eap_method_priv; TYPE_1__* m; int /*<<< orphan*/  eap_server; } ;
struct TYPE_6__ {TYPE_2__* methods; } ;
struct TYPE_5__ {scalar_t__ vendor; scalar_t__ method; } ;
struct TYPE_4__ {scalar_t__ (* isSuccess ) (struct eap_sm*,int /*<<< orphan*/ ) ;scalar_t__ (* isDone ) (struct eap_sm*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int DECISION_CONTINUE ; 
 int DECISION_FAILURE ; 
 int DECISION_INITIATE_REAUTH_START ; 
 int DECISION_PASSTHROUGH ; 
 int DECISION_SUCCESS ; 
 size_t EAP_MAX_METHODS ; 
 scalar_t__ EAP_TYPE_IDENTITY ; 
 scalar_t__ EAP_TYPE_NONE ; 
 scalar_t__ EAP_VENDOR_IETF ; 
 void* FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 scalar_t__ eap_get_erp_send_reauth_start (struct eap_sm*) ; 
 scalar_t__ eap_user_get (struct eap_sm*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct eap_sm*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct eap_sm*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct eap_sm*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int eap_sm_Policy_getDecision(struct eap_sm *sm)
{
	if (!sm->eap_server && sm->identity && !sm->start_reauth) {
		wpa_printf(MSG_DEBUG, "EAP: getDecision: -> PASSTHROUGH");
		return DECISION_PASSTHROUGH;
	}

	if (sm->m && sm->currentMethod != EAP_TYPE_IDENTITY &&
	    sm->m->isSuccess(sm, sm->eap_method_priv)) {
		wpa_printf(MSG_DEBUG, "EAP: getDecision: method succeeded -> "
			   "SUCCESS");
		sm->update_user = TRUE;
		return DECISION_SUCCESS;
	}

	if (sm->m && sm->m->isDone(sm, sm->eap_method_priv) &&
	    !sm->m->isSuccess(sm, sm->eap_method_priv)) {
		wpa_printf(MSG_DEBUG, "EAP: getDecision: method failed -> "
			   "FAILURE");
		sm->update_user = TRUE;
		return DECISION_FAILURE;
	}

	if ((sm->user == NULL || sm->update_user) && sm->identity &&
	    !sm->start_reauth) {
		/*
		 * Allow Identity method to be started once to allow identity
		 * selection hint to be sent from the authentication server,
		 * but prevent a loop of Identity requests by only allowing
		 * this to happen once.
		 */
		int id_req = 0;
		if (sm->user && sm->currentMethod == EAP_TYPE_IDENTITY &&
		    sm->user->methods[0].vendor == EAP_VENDOR_IETF &&
		    sm->user->methods[0].method == EAP_TYPE_IDENTITY)
			id_req = 1;
		if (eap_user_get(sm, sm->identity, sm->identity_len, 0) != 0) {
			wpa_printf(MSG_DEBUG, "EAP: getDecision: user not "
				   "found from database -> FAILURE");
			return DECISION_FAILURE;
		}
		if (id_req && sm->user &&
		    sm->user->methods[0].vendor == EAP_VENDOR_IETF &&
		    sm->user->methods[0].method == EAP_TYPE_IDENTITY) {
			wpa_printf(MSG_DEBUG, "EAP: getDecision: stop "
				   "identity request loop -> FAILURE");
			sm->update_user = TRUE;
			return DECISION_FAILURE;
		}
		sm->update_user = FALSE;
	}
	sm->start_reauth = FALSE;

	if (sm->user && sm->user_eap_method_index < EAP_MAX_METHODS &&
	    (sm->user->methods[sm->user_eap_method_index].vendor !=
	     EAP_VENDOR_IETF ||
	     sm->user->methods[sm->user_eap_method_index].method !=
	     EAP_TYPE_NONE)) {
		wpa_printf(MSG_DEBUG, "EAP: getDecision: another method "
			   "available -> CONTINUE");
		return DECISION_CONTINUE;
	}

	if (!sm->identity && eap_get_erp_send_reauth_start(sm) &&
	    !sm->initiate_reauth_start_sent) {
		wpa_printf(MSG_DEBUG,
			   "EAP: getDecision: send EAP-Initiate/Re-auth-Start");
		return DECISION_INITIATE_REAUTH_START;
	}

	if (sm->identity == NULL || sm->currentId == -1) {
		wpa_printf(MSG_DEBUG, "EAP: getDecision: no identity known "
			   "yet -> CONTINUE");
		return DECISION_CONTINUE;
	}

	wpa_printf(MSG_DEBUG, "EAP: getDecision: no more methods available -> "
		   "FAILURE");
	return DECISION_FAILURE;
}