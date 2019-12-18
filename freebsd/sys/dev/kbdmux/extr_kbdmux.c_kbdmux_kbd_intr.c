#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_7__ {int /*<<< orphan*/  ks_task; int /*<<< orphan*/  ks_flags; } ;
typedef  TYPE_2__ kbdmux_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  KBDMUX_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  KBDMUX_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  TASK ; 
 int /*<<< orphan*/  kbdd_intr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
kbdmux_kbd_intr(void *xkbd, int pending)
{
	keyboard_t	*kbd = (keyboard_t *) xkbd;
	kbdmux_state_t	*state = (kbdmux_state_t *) kbd->kb_data;

	kbdd_intr(kbd, NULL);

	KBDMUX_LOCK(state);

	state->ks_flags &= ~TASK;
	wakeup(&state->ks_task);

	KBDMUX_UNLOCK(state);
}