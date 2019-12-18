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
struct TYPE_6__ {int /*<<< orphan*/  ks_task; int /*<<< orphan*/  ks_flags; } ;
typedef  TYPE_1__ vkbd_state_t ;
struct TYPE_7__ {scalar_t__ kb_data; } ;
typedef  TYPE_2__ keyboard_t ;

/* Variables and functions */
 int /*<<< orphan*/  TASK ; 
 int /*<<< orphan*/  VKBD_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VKBD_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  kbdd_intr (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

void
vkbd_dev_intr(void *xkbd, int pending)
{
	keyboard_t	*kbd = (keyboard_t *) xkbd;
	vkbd_state_t	*state = (vkbd_state_t *) kbd->kb_data;

	kbdd_intr(kbd, NULL);

	VKBD_LOCK(state);

	state->ks_flags &= ~TASK;
	wakeup(&state->ks_task);

	VKBD_UNLOCK(state);
}