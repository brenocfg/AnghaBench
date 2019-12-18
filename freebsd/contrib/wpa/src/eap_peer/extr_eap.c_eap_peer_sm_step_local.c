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
struct eap_sm {int EAP_state; int /*<<< orphan*/  eapRespData; int /*<<< orphan*/  decision; int /*<<< orphan*/  methodState; int /*<<< orphan*/  ignore; int /*<<< orphan*/  reqMethod; int /*<<< orphan*/  selectedMethod; int /*<<< orphan*/  force_disabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECISION_FAIL ; 
 int /*<<< orphan*/  DISCARD ; 
 int /*<<< orphan*/  EAP ; 
 int /*<<< orphan*/  EAPOL_portEnabled ; 
#define  EAP_DISABLED 140 
#define  EAP_DISCARD 139 
#define  EAP_FAILURE 138 
#define  EAP_GET_METHOD 137 
#define  EAP_IDENTITY 136 
#define  EAP_IDLE 135 
#define  EAP_INITIALIZE 134 
#define  EAP_METHOD 133 
#define  EAP_NOTIFICATION 132 
#define  EAP_RECEIVED 131 
#define  EAP_RETRANSMIT 130 
#define  EAP_SEND_RESPONSE 129 
#define  EAP_SUCCESS 128 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  IDLE ; 
 int /*<<< orphan*/  INITIALIZE ; 
 int /*<<< orphan*/  METHOD ; 
 int /*<<< orphan*/  METHOD_DONE ; 
 int /*<<< orphan*/  SEND_RESPONSE ; 
 int /*<<< orphan*/  SM_ENTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eap_peer_sm_step_idle (struct eap_sm*) ; 
 int /*<<< orphan*/  eap_peer_sm_step_received (struct eap_sm*) ; 
 int /*<<< orphan*/  eapol_get_bool (struct eap_sm*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void eap_peer_sm_step_local(struct eap_sm *sm)
{
	switch (sm->EAP_state) {
	case EAP_INITIALIZE:
		SM_ENTER(EAP, IDLE);
		break;
	case EAP_DISABLED:
		if (eapol_get_bool(sm, EAPOL_portEnabled) &&
		    !sm->force_disabled)
			SM_ENTER(EAP, INITIALIZE);
		break;
	case EAP_IDLE:
		eap_peer_sm_step_idle(sm);
		break;
	case EAP_RECEIVED:
		eap_peer_sm_step_received(sm);
		break;
	case EAP_GET_METHOD:
		if (sm->selectedMethod == sm->reqMethod)
			SM_ENTER(EAP, METHOD);
		else
			SM_ENTER(EAP, SEND_RESPONSE);
		break;
	case EAP_METHOD:
		/*
		 * Note: RFC 4137 uses methodState == DONE && decision == FAIL
		 * as the condition. eapRespData == NULL here is used to allow
		 * final EAP method response to be sent without having to change
		 * all methods to either use methodState MAY_CONT or leaving
		 * decision to something else than FAIL in cases where the only
		 * expected response is EAP-Failure.
		 */
		if (sm->ignore)
			SM_ENTER(EAP, DISCARD);
		else if (sm->methodState == METHOD_DONE &&
			 sm->decision == DECISION_FAIL && !sm->eapRespData)
			SM_ENTER(EAP, FAILURE);
		else
			SM_ENTER(EAP, SEND_RESPONSE);
		break;
	case EAP_SEND_RESPONSE:
		SM_ENTER(EAP, IDLE);
		break;
	case EAP_DISCARD:
		SM_ENTER(EAP, IDLE);
		break;
	case EAP_IDENTITY:
		SM_ENTER(EAP, SEND_RESPONSE);
		break;
	case EAP_NOTIFICATION:
		SM_ENTER(EAP, SEND_RESPONSE);
		break;
	case EAP_RETRANSMIT:
		SM_ENTER(EAP, SEND_RESPONSE);
		break;
	case EAP_SUCCESS:
		break;
	case EAP_FAILURE:
		break;
	}
}