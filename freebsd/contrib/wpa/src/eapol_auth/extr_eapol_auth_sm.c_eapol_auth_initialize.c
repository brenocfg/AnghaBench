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
struct eapol_state_machine {void* initializing; void* initialize; } ;

/* Variables and functions */
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  eapol_port_timers_tick ; 
 int /*<<< orphan*/  eapol_sm_step_run (struct eapol_state_machine*) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_state_machine*) ; 
 int /*<<< orphan*/  eloop_register_timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct eapol_state_machine*) ; 

__attribute__((used)) static void eapol_auth_initialize(struct eapol_state_machine *sm)
{
	sm->initializing = TRUE;
	/* Initialize the state machines by asserting initialize and then
	 * deasserting it after one step */
	sm->initialize = TRUE;
	eapol_sm_step_run(sm);
	sm->initialize = FALSE;
	eapol_sm_step_run(sm);
	sm->initializing = FALSE;

	/* Start one second tick for port timers state machine */
	eloop_cancel_timeout(eapol_port_timers_tick, NULL, sm);
	eloop_register_timeout(1, 0, eapol_port_timers_tick, NULL, sm);
}