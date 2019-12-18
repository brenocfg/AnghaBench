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
struct eapol_state_machine {void* eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_sm_pending_cb (void*) ; 
 int /*<<< orphan*/  eapol_auth_step (struct eapol_state_machine*) ; 

int eapol_auth_eap_pending_cb(struct eapol_state_machine *sm, void *ctx)
{
	if (sm == NULL || ctx == NULL || ctx != sm->eap)
		return -1;

	eap_sm_pending_cb(sm->eap);
	eapol_auth_step(sm);

	return 0;
}