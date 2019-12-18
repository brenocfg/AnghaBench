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

/* Variables and functions */
 int CTLS ; 
 int SCAN_PREFIX_CTL ; 
 int const SCAN_PREFIX_E0 ; 
 int SCAN_PREFIX_E1 ; 
#define  SCAN_PREFIX_SHIFT 128 
 int SCAN_PRESS ; 
 int SCAN_RELEASE ; 
 int SHIFTS ; 
 int nitems (int const*) ; 

__attribute__((used)) static int
keycode2scancode(int keycode, int shift, int up)
{
	static const int scan[] = {
		/* KP enter, right ctrl, KP divide */
		0x1c , 0x1d , 0x35 ,
		/* print screen */
		0x37 | SCAN_PREFIX_SHIFT,
		/* right alt, home, up, page up, left, right, end */
		0x38, 0x47, 0x48, 0x49, 0x4b, 0x4d, 0x4f,
		/* down, page down, insert, delete */
		0x50, 0x51, 0x52, 0x53,
		/* pause/break (see also below) */
		0x46,
		/*
		 * MS: left window, right window, menu
		 * also Sun: left meta, right meta, compose
		 */
		0x5b, 0x5c, 0x5d,
		/* Sun type 6 USB */
		/* help, stop, again, props, undo, front, copy */
		0x68, 0x5e, 0x5f, 0x60,	0x61, 0x62, 0x63,
		/* open, paste, find, cut, audiomute, audiolower, audioraise */
		0x64, 0x65, 0x66, 0x67, 0x25, 0x1f, 0x1e,
		/* power */
		0x20
	};
	int scancode;

	scancode = keycode;
	if ((keycode >= 89) && (keycode < 89 + nitems(scan)))
	scancode = scan[keycode - 89] | SCAN_PREFIX_E0;
	/* pause/break */
	if ((keycode == 104) && !(shift & CTLS))
		scancode = 0x45 | SCAN_PREFIX_E1 | SCAN_PREFIX_CTL;
	if (shift & SHIFTS)
		scancode &= ~SCAN_PREFIX_SHIFT;
	return (scancode | (up ? SCAN_RELEASE : SCAN_PRESS));
}