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
struct eapol_sm {int /*<<< orphan*/  eap; void* altAccept; void* eapSuccess; } ;
typedef  void* Boolean ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  eap_notify_success (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*,void*) ; 

void eapol_sm_notify_eap_success(struct eapol_sm *sm, Boolean success)
{
	if (sm == NULL)
		return;
	wpa_printf(MSG_DEBUG, "EAPOL: External notification - "
		   "EAP success=%d", success);
	sm->eapSuccess = success;
	sm->altAccept = success;
	if (success)
		eap_notify_success(sm->eap);
	eapol_sm_step(sm);
}