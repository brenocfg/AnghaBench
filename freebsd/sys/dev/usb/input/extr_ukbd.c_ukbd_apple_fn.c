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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static uint8_t
ukbd_apple_fn(uint8_t keycode) {
	switch (keycode) {
	case 0x28: return 0x49; /* RETURN -> INSERT */
	case 0x2a: return 0x4c; /* BACKSPACE -> DEL */
	case 0x50: return 0x4a; /* LEFT ARROW -> HOME */
	case 0x4f: return 0x4d; /* RIGHT ARROW -> END */
	case 0x52: return 0x4b; /* UP ARROW -> PGUP */
	case 0x51: return 0x4e; /* DOWN ARROW -> PGDN */
	default: return keycode;
	}
}