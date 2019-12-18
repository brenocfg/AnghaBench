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
 int /*<<< orphan*/  eapol_sm_step_run (struct eapol_state_machine*) ; 

__attribute__((used)) static void eapol_sm_step_cb(void *eloop_ctx, void *timeout_ctx)
{
	struct eapol_state_machine *sm = eloop_ctx;
	eapol_sm_step_run(sm);
}