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
struct uinput_cdev_state {int /*<<< orphan*/  ucs_lock; TYPE_1__ ucs_selp; int /*<<< orphan*/  ucs_evdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_EVDEV ; 
 int /*<<< orphan*/  evdev_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  knlist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seldrain (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
uinput_dtor(void *data)
{
	struct uinput_cdev_state *state = (struct uinput_cdev_state *)data;

	evdev_free(state->ucs_evdev);

	knlist_clear(&state->ucs_selp.si_note, 0);
	seldrain(&state->ucs_selp);
	knlist_destroy(&state->ucs_selp.si_note);
	sx_destroy(&state->ucs_lock);
	free(data, M_EVDEV);
}