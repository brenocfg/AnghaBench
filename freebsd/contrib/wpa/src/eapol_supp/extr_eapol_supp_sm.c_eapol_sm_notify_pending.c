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
struct eapol_sm {void* eapReq; void* eapolEap; scalar_t__ eapReqData; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 void* TRUE ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void eapol_sm_notify_pending(void *ctx)
{
	struct eapol_sm *sm = ctx;
	if (sm == NULL)
		return;
	if (sm->eapReqData && !sm->eapReq) {
		wpa_printf(MSG_DEBUG, "EAPOL: received notification from EAP "
			   "state machine - retrying pending EAP Request");
		sm->eapolEap = TRUE;
		sm->eapReq = TRUE;
		eapol_sm_step(sm);
	}
}