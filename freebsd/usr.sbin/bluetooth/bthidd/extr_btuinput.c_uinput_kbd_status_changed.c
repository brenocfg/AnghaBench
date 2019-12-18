#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct input_event {int type; int /*<<< orphan*/  value; int /*<<< orphan*/  code; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  ie ;
typedef  TYPE_1__* bthid_session_p ;
struct TYPE_3__ {scalar_t__ vkbd; } ;

/* Variables and functions */
#define  EV_LED 129 
#define  EV_REP 128 
 int /*<<< orphan*/  KDGETLED ; 
 int /*<<< orphan*/  KDSETLED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ioctl (scalar_t__,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/ * led_codes ; 
 int /*<<< orphan*/  memcpy (struct input_event*,int /*<<< orphan*/ *,int) ; 
 size_t nitems (int /*<<< orphan*/ *) ; 

int32_t
uinput_kbd_status_changed(bthid_session_p s, uint8_t *data, int32_t len)
{
	struct input_event ie;
	int32_t leds, oleds;
	size_t i;

	assert(s != NULL);
	assert(s->vkbd >= 0);
	assert(len == sizeof(struct input_event));

	memcpy(&ie, data, sizeof(ie));
	switch (ie.type) {
	case EV_LED:
		ioctl(s->vkbd, KDGETLED, &oleds);
		leds = oleds;
		for (i = 0; i < nitems(led_codes); i++) {
			if (led_codes[i] == ie.code) {
				if (ie.value)
					leds |= 1 << i;
				else
					leds &= ~(1 << i);
				if (leds != oleds)
					ioctl(s->vkbd, KDSETLED, leds);
				break;
			}
		}
		break;
	case EV_REP:
		/* FALLTHROUGH. Repeats are handled by evdev subsystem */
	default:
		break;
	}

	return (0);
}