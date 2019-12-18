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
struct eapol_state_machine {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  eapol_sm_step_cb ; 
 int /*<<< orphan*/  eloop_register_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct eapol_state_machine*,int /*<<< orphan*/ *) ; 

void eapol_auth_step(struct eapol_state_machine *sm)
{
	/*
	 * Run eapol_sm_step_run from a registered timeout to make sure that
	 * other possible timeouts/events are processed and to avoid long
	 * function call chains.
	 */

	eloop_register_timeout(0, 0, eapol_sm_step_cb, sm, NULL);
}