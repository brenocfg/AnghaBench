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
 scalar_t__ EVDEV_RCPT_HW_KBD ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  EV_SYN ; 
 scalar_t__ NONE ; 
 scalar_t__ SYN_REPORT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__* consmap ; 
 scalar_t__ nitems (scalar_t__*) ; 
 scalar_t__ uinput_get_rcpt_mask () ; 
 scalar_t__ uinput_write_event (scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

int32_t
uinput_rep_cons(int32_t fd, int32_t key, int32_t make)
{
	int32_t rcpt_mask;

	assert(fd >= 0);

	rcpt_mask = uinput_get_rcpt_mask();
	if (!(rcpt_mask & EVDEV_RCPT_HW_KBD))
		return (0);

	if (key >= 0 && key < (int32_t)nitems(consmap) &&
	    consmap[key] != NONE) {
		if (uinput_write_event(fd, EV_KEY, consmap[key], make) > 0 &&
		    uinput_write_event(fd, EV_SYN, SYN_REPORT, 0) > 0)
			return (0);
	}
	return (-1);
}