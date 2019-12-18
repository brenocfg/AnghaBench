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
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ EVDEV_RCPT_HW_MOUSE ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_REL ; 
 int /*<<< orphan*/  EV_SYN ; 
 int /*<<< orphan*/  REL_HWHEEL ; 
 int /*<<< orphan*/  REL_WHEEL ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 int /*<<< orphan*/  SYN_REPORT ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * mbuttons ; 
 size_t nitems (int /*<<< orphan*/ *) ; 
 scalar_t__ uinput_get_rcpt_mask () ; 
 scalar_t__ uinput_write_event (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int32_t
uinput_rep_mouse(int32_t fd, int32_t x, int32_t y, int32_t z, int32_t t,
    int32_t buttons, int32_t obuttons)
{
	size_t i;
	int32_t rcpt_mask, mask;

	assert(fd >= 0);

	rcpt_mask = uinput_get_rcpt_mask();
	if (!(rcpt_mask & EVDEV_RCPT_HW_MOUSE))
		return (0);

	if ((x != 0 && uinput_write_event(fd, EV_REL, REL_X, x) < 0) ||
	    (y != 0 && uinput_write_event(fd, EV_REL, REL_Y, y) < 0) ||
	    (z != 0 && uinput_write_event(fd, EV_REL, REL_WHEEL, -z) < 0) ||
	    (t != 0 && uinput_write_event(fd, EV_REL, REL_HWHEEL, t) < 0))
		return (-1);

	for (i = 0; i < nitems(mbuttons); i++) {
		mask = 1 << i;
		if ((buttons & mask) == (obuttons & mask))
			continue;
		if (uinput_write_event(fd, EV_KEY, mbuttons[i],
		    (buttons & mask) != 0) < 0)
			return (-1);
	}

	if (uinput_write_event(fd, EV_SYN, SYN_REPORT, 0) < 0)
		return (-1);

	return (0);
}