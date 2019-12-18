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
struct eapol_state_machine {struct eapol_state_machine* identity; int /*<<< orphan*/  radius_cui; scalar_t__ eap; } ;

/* Variables and functions */
 int /*<<< orphan*/  eap_server_sm_deinit (scalar_t__) ; 
 int /*<<< orphan*/  eapol_port_timers_tick ; 
 int /*<<< orphan*/  eapol_sm_step_cb ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct eapol_state_machine*,struct eapol_state_machine*) ; 
 int /*<<< orphan*/  os_free (struct eapol_state_machine*) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void eapol_auth_free(struct eapol_state_machine *sm)
{
	if (sm == NULL)
		return;

	eloop_cancel_timeout(eapol_port_timers_tick, NULL, sm);
	eloop_cancel_timeout(eapol_sm_step_cb, sm, NULL);
	if (sm->eap)
		eap_server_sm_deinit(sm->eap);

	wpabuf_free(sm->radius_cui);
	os_free(sm->identity);
	os_free(sm);
}