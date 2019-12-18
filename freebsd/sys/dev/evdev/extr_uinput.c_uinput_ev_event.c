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
typedef  scalar_t__ uint16_t ;
struct uinput_cdev_state {scalar_t__ ucs_state; } ;
struct evdev_dev {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ EV_LED ; 
 int /*<<< orphan*/  UINPUT_LOCK (struct uinput_cdev_state*) ; 
 scalar_t__ UINPUT_RUNNING ; 
 int /*<<< orphan*/  UINPUT_UNLOCK (struct uinput_cdev_state*) ; 
 struct uinput_cdev_state* evdev_get_softc (struct evdev_dev*) ; 
 int /*<<< orphan*/  evdev_push_event (struct evdev_dev*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uinput_enqueue_event (struct uinput_cdev_state*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uinput_notify (struct uinput_cdev_state*) ; 

__attribute__((used)) static void
uinput_ev_event(struct evdev_dev *evdev, uint16_t type, uint16_t code,
    int32_t value)
{
	struct uinput_cdev_state *state = evdev_get_softc(evdev);

	if (type == EV_LED)
		evdev_push_event(evdev, type, code, value);

	UINPUT_LOCK(state);
	if (state->ucs_state == UINPUT_RUNNING) {
		uinput_enqueue_event(state, type, code, value);
		uinput_notify(state);
	}
	UINPUT_UNLOCK(state);
}