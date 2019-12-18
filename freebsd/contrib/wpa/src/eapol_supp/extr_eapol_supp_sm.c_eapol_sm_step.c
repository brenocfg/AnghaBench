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
struct eapol_sm {scalar_t__ cb_status; TYPE_1__* ctx; int /*<<< orphan*/  eap; void* changed; int /*<<< orphan*/  eap_proxy; scalar_t__ use_eap_proxy; } ;
typedef  enum eapol_supp_result { ____Placeholder_eapol_supp_result } eapol_supp_result ;
struct TYPE_2__ {int /*<<< orphan*/  cb_ctx; int /*<<< orphan*/  (* cb ) (struct eapol_sm*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ EAPOL_CB_IN_PROGRESS ; 
 scalar_t__ EAPOL_CB_SUCCESS ; 
 int EAPOL_SUPP_RESULT_EXPECTED_FAILURE ; 
 int EAPOL_SUPP_RESULT_FAILURE ; 
 int EAPOL_SUPP_RESULT_SUCCESS ; 
 void* FALSE ; 
 int /*<<< orphan*/  KEY_RX ; 
 int /*<<< orphan*/  SM_STEP_RUN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUPP_BE ; 
 int /*<<< orphan*/  SUPP_PAE ; 
 void* TRUE ; 
 scalar_t__ eap_peer_sm_step (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_peer_was_failure_expected (int /*<<< orphan*/ ) ; 
 scalar_t__ eap_proxy_sm_step (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_step_timeout ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_sm*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_sm*) ; 
 int /*<<< orphan*/  stub1 (struct eapol_sm*,int,int /*<<< orphan*/ ) ; 

void eapol_sm_step(struct eapol_sm *sm)
{
	int i;

	/* In theory, it should be ok to run this in loop until !changed.
	 * However, it is better to use a limit on number of iterations to
	 * allow events (e.g., SIGTERM) to stop the program cleanly if the
	 * state machine were to generate a busy loop. */
	for (i = 0; i < 100; i++) {
		sm->changed = FALSE;
		SM_STEP_RUN(SUPP_PAE);
		SM_STEP_RUN(KEY_RX);
		SM_STEP_RUN(SUPP_BE);
#ifdef CONFIG_EAP_PROXY
		if (sm->use_eap_proxy) {
			/* Drive the EAP proxy state machine */
			if (eap_proxy_sm_step(sm->eap_proxy, sm->eap))
				sm->changed = TRUE;
		} else
#endif /* CONFIG_EAP_PROXY */
		if (eap_peer_sm_step(sm->eap))
			sm->changed = TRUE;
		if (!sm->changed)
			break;
	}

	if (sm->changed) {
		/* restart EAPOL state machine step from timeout call in order
		 * to allow other events to be processed. */
		eloop_cancel_timeout(eapol_sm_step_timeout, NULL, sm);
		eloop_register_timeout(0, 0, eapol_sm_step_timeout, NULL, sm);
	}

	if (sm->ctx->cb && sm->cb_status != EAPOL_CB_IN_PROGRESS) {
		enum eapol_supp_result result;
		if (sm->cb_status == EAPOL_CB_SUCCESS)
			result = EAPOL_SUPP_RESULT_SUCCESS;
		else if (eap_peer_was_failure_expected(sm->eap))
			result = EAPOL_SUPP_RESULT_EXPECTED_FAILURE;
		else
			result = EAPOL_SUPP_RESULT_FAILURE;
		sm->cb_status = EAPOL_CB_IN_PROGRESS;
		sm->ctx->cb(sm, result, sm->ctx->cb_ctx);
	}
}