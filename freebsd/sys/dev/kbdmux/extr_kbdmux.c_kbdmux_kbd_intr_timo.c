#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ ks_inq_length; int ks_flags; int /*<<< orphan*/  ks_timo; } ;
typedef  TYPE_1__ kbdmux_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBDMUX_LOCK_ASSERT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ KBDMUX_QUEUE_INTR (TYPE_1__*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int TASK ; 
 int /*<<< orphan*/  TICKS ; 
 int /*<<< orphan*/  callout_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_deactivate (int /*<<< orphan*/ *) ; 
 scalar_t__ callout_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*) ; 

void
kbdmux_kbd_intr_timo(void *xstate)
{
	kbdmux_state_t	*state = (kbdmux_state_t *) xstate;

	KBDMUX_LOCK_ASSERT(state, MA_OWNED);

	if (callout_pending(&state->ks_timo))
		return; /* callout was reset */

	if (!callout_active(&state->ks_timo))
		return; /* callout was stopped */

	callout_deactivate(&state->ks_timo);

	/* queue interrupt task if needed */
	if (state->ks_inq_length > 0 && !(state->ks_flags & TASK) &&
	    KBDMUX_QUEUE_INTR(state) == 0)
		state->ks_flags |= TASK;

	/* re-schedule timeout */
	callout_reset(&state->ks_timo, TICKS, kbdmux_kbd_intr_timo, state);
}