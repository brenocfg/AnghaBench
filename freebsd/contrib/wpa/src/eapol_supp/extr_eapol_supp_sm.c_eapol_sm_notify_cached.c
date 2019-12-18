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
struct eapol_sm {int /*<<< orphan*/  eap; int /*<<< orphan*/  eapSuccess; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  eap_notify_success (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eapol_sm_step (struct eapol_sm*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

void eapol_sm_notify_cached(struct eapol_sm *sm)
{
	if (sm == NULL)
		return;
	wpa_printf(MSG_DEBUG, "EAPOL: PMKSA caching was used - skip EAPOL");
	sm->eapSuccess = TRUE;
	eap_notify_success(sm->eap);
	eapol_sm_step(sm);
}