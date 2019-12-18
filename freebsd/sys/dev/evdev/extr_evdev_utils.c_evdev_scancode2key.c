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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_PAUSE ; 
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/ * evdev_at_set1_scancodes ; 

uint16_t
evdev_scancode2key(int *state, int scancode)
{
	uint16_t keycode;

	/* translate the scan code into a keycode */
	keycode = evdev_at_set1_scancodes[scancode & 0x7f];
	switch (*state) {
	case 0x00:	/* normal scancode */
		switch(scancode) {
		case 0xE0:
		case 0xE1:
			*state = scancode;
			return (NONE);
		}
		break;
	case 0xE0:		/* 0xE0 prefix */
		*state = 0;
		keycode = evdev_at_set1_scancodes[0x80 + (scancode & 0x7f)];
		break;
	case 0xE1:	/* 0xE1 prefix */
		/*
		 * The pause/break key on the 101 keyboard produces:
		 * E1-1D-45 E1-9D-C5
		 * Ctrl-pause/break produces:
		 * E0-46 E0-C6 (See above.)
		 */
		*state = 0;
		if ((scancode & 0x7f) == 0x1D)
			*state = scancode;
		return (NONE);
		/* NOT REACHED */
	case 0x1D:	/* pause / break */
	case 0x9D:
		if ((*state ^ scancode) & 0x80)
			return (NONE);
		*state = 0;
		if ((scancode & 0x7f) != 0x45)
			return (NONE);
		keycode = KEY_PAUSE;
		break;
	}

	return (keycode);
}