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
struct eapol_sm {void* eapTriggerStart; void* altReject; void* altAccept; void* portEnabled; void* eapReq; void* eapNoResp; void* eapResp; void* eapFail; void* eapRestart; void* eapSuccess; } ;
typedef  enum eapol_bool_var { ____Placeholder_eapol_bool_var } eapol_bool_var ;
typedef  void* Boolean ;

/* Variables and functions */
#define  EAPOL_altAccept 137 
#define  EAPOL_altReject 136 
#define  EAPOL_eapFail 135 
#define  EAPOL_eapNoResp 134 
#define  EAPOL_eapReq 133 
#define  EAPOL_eapResp 132 
#define  EAPOL_eapRestart 131 
#define  EAPOL_eapSuccess 130 
#define  EAPOL_eapTriggerStart 129 
#define  EAPOL_portEnabled 128 

__attribute__((used)) static void eapol_sm_set_bool(void *ctx, enum eapol_bool_var variable,
			      Boolean value)
{
	struct eapol_sm *sm = ctx;
	if (sm == NULL)
		return;
	switch (variable) {
	case EAPOL_eapSuccess:
		sm->eapSuccess = value;
		break;
	case EAPOL_eapRestart:
		sm->eapRestart = value;
		break;
	case EAPOL_eapFail:
		sm->eapFail = value;
		break;
	case EAPOL_eapResp:
		sm->eapResp = value;
		break;
	case EAPOL_eapNoResp:
		sm->eapNoResp = value;
		break;
	case EAPOL_eapReq:
		sm->eapReq = value;
		break;
	case EAPOL_portEnabled:
		sm->portEnabled = value;
		break;
	case EAPOL_altAccept:
		sm->altAccept = value;
		break;
	case EAPOL_altReject:
		sm->altReject = value;
		break;
	case EAPOL_eapTriggerStart:
		sm->eapTriggerStart = value;
		break;
	}
}