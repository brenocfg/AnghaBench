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
struct eapol_sm {int /*<<< orphan*/  eapTriggerStart; int /*<<< orphan*/  altReject; int /*<<< orphan*/  altAccept; int /*<<< orphan*/  portEnabled; int /*<<< orphan*/  eapReq; int /*<<< orphan*/  eapNoResp; int /*<<< orphan*/  eapResp; int /*<<< orphan*/  eapFail; int /*<<< orphan*/  eapRestart; int /*<<< orphan*/  eapSuccess; } ;
typedef  enum eapol_bool_var { ____Placeholder_eapol_bool_var } eapol_bool_var ;
typedef  int /*<<< orphan*/  Boolean ;

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
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static Boolean eapol_sm_get_bool(void *ctx, enum eapol_bool_var variable)
{
	struct eapol_sm *sm = ctx;
	if (sm == NULL)
		return FALSE;
	switch (variable) {
	case EAPOL_eapSuccess:
		return sm->eapSuccess;
	case EAPOL_eapRestart:
		return sm->eapRestart;
	case EAPOL_eapFail:
		return sm->eapFail;
	case EAPOL_eapResp:
		return sm->eapResp;
	case EAPOL_eapNoResp:
		return sm->eapNoResp;
	case EAPOL_eapReq:
		return sm->eapReq;
	case EAPOL_portEnabled:
		return sm->portEnabled;
	case EAPOL_altAccept:
		return sm->altAccept;
	case EAPOL_altReject:
		return sm->altReject;
	case EAPOL_eapTriggerStart:
		return sm->eapTriggerStart;
	}
	return FALSE;
}