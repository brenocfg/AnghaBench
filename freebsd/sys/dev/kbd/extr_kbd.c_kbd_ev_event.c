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
typedef  scalar_t__ uint16_t ;
struct TYPE_5__ {int kb_delay2; int kb_delay1; } ;
typedef  TYPE_1__ keyboard_t ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int CLKED ; 
 scalar_t__ EV_LED ; 
 scalar_t__ EV_REP ; 
 int KBD_LED_VAL (TYPE_1__*) ; 
 int /*<<< orphan*/  KDSETLED ; 
 int /*<<< orphan*/  KDSETREPEAT ; 
#define  LED_CAPSL 130 
#define  LED_NUML 129 
#define  LED_SCROLLL 128 
 int NLKED ; 
 scalar_t__ REP_DELAY ; 
 scalar_t__ REP_PERIOD ; 
 int SLKED ; 
 int /*<<< orphan*/  kbdd_ioctl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
kbd_ev_event(keyboard_t *kbd, uint16_t type, uint16_t code, int32_t value)
{
	int delay[2], led = 0, leds, oleds;

	if (type == EV_LED) {
		leds = oleds = KBD_LED_VAL(kbd);
		switch (code) {
		case LED_CAPSL:
			led = CLKED;
			break;
		case LED_NUML:
			led = NLKED;
			break;
		case LED_SCROLLL:
			led = SLKED;
			break;
		}

		if (value)
			leds |= led;
		else
			leds &= ~led;

		if (leds != oleds)
			kbdd_ioctl(kbd, KDSETLED, (caddr_t)&leds);

	} else if (type == EV_REP && code == REP_DELAY) {
		delay[0] = value;
		delay[1] = kbd->kb_delay2;
		kbdd_ioctl(kbd, KDSETREPEAT, (caddr_t)delay);
	} else if (type == EV_REP && code == REP_PERIOD) {
		delay[0] = kbd->kb_delay1;
		delay[1] = value;
		kbdd_ioctl(kbd, KDSETREPEAT, (caddr_t)delay);
	}
}