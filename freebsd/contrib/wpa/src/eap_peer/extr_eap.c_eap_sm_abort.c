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
struct eap_sm {int /*<<< orphan*/ * eapSessionId; int /*<<< orphan*/ * eapRespData; int /*<<< orphan*/ * lastRespData; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAPOL_eapSuccess ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  eap_sm_free_key (struct eap_sm*) ; 
 int /*<<< orphan*/  eapol_set_bool (struct eap_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ *) ; 

void eap_sm_abort(struct eap_sm *sm)
{
	wpabuf_free(sm->lastRespData);
	sm->lastRespData = NULL;
	wpabuf_free(sm->eapRespData);
	sm->eapRespData = NULL;
	eap_sm_free_key(sm);
	os_free(sm->eapSessionId);
	sm->eapSessionId = NULL;

	/* This is not clearly specified in the EAP statemachines draft, but
	 * it seems necessary to make sure that some of the EAPOL variables get
	 * cleared for the next authentication. */
	eapol_set_bool(sm, EAPOL_eapSuccess, FALSE);
}