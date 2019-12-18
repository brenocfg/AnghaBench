#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct uinput_cdev_state {int ucs_blocked; int ucs_selected; TYPE_1__ ucs_selp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KNOTE_LOCKED (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINPUT_LOCK_ASSERT (struct uinput_cdev_state*) ; 
 int /*<<< orphan*/  selwakeup (TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup (struct uinput_cdev_state*) ; 

__attribute__((used)) static void
uinput_notify(struct uinput_cdev_state *state)
{

	UINPUT_LOCK_ASSERT(state);

	if (state->ucs_blocked) {
		state->ucs_blocked = false;
		wakeup(state);
	}
	if (state->ucs_selected) {
		state->ucs_selected = false;
		selwakeup(&state->ucs_selp);
	}
	KNOTE_LOCKED(&state->ucs_selp.si_note, 0);
}