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
struct ukbd_softc {int* sc_buffered_char; } ;

/* Variables and functions */
 int MOD_CONTROL_L ; 
 int MOD_CONTROL_R ; 
 int MOD_SHIFT_L ; 
 int MOD_SHIFT_R ; 
 int SCAN_PREFIX ; 
 int SCAN_PREFIX_CTL ; 
 int SCAN_PREFIX_E0 ; 
 int SCAN_PREFIX_E1 ; 
 int SCAN_PREFIX_SHIFT ; 
 int SCAN_PRESS ; 
 int SCAN_RELEASE ; 
 scalar_t__ nitems (int const*) ; 

__attribute__((used)) static int
ukbd_key2scan(struct ukbd_softc *sc, int code, int shift, int up)
{
	static const int scan[] = {
		/* 89 */
		0x11c,	/* Enter */
		/* 90-99 */
		0x11d,	/* Ctrl-R */
		0x135,	/* Divide */
		0x137,	/* PrintScreen */
		0x138,	/* Alt-R */
		0x147,	/* Home */
		0x148,	/* Up */
		0x149,	/* PageUp */
		0x14b,	/* Left */
		0x14d,	/* Right */
		0x14f,	/* End */
		/* 100-109 */
		0x150,	/* Down */
		0x151,	/* PageDown */
		0x152,	/* Insert */
		0x153,	/* Delete */
		0x146,	/* Pause/Break */
		0x15b,	/* Win_L(Super_L) */
		0x15c,	/* Win_R(Super_R) */
		0x15d,	/* Application(Menu) */

		/* SUN TYPE 6 USB KEYBOARD */
		0x168,	/* Sun Type 6 Help */
		0x15e,	/* Sun Type 6 Stop */
		/* 110 - 119 */
		0x15f,	/* Sun Type 6 Again */
		0x160,	/* Sun Type 6 Props */
		0x161,	/* Sun Type 6 Undo */
		0x162,	/* Sun Type 6 Front */
		0x163,	/* Sun Type 6 Copy */
		0x164,	/* Sun Type 6 Open */
		0x165,	/* Sun Type 6 Paste */
		0x166,	/* Sun Type 6 Find */
		0x167,	/* Sun Type 6 Cut */
		0x125,	/* Sun Type 6 Mute */
		/* 120 - 130 */
		0x11f,	/* Sun Type 6 VolumeDown */
		0x11e,	/* Sun Type 6 VolumeUp */
		0x120,	/* Sun Type 6 PowerDown */

		/* Japanese 106/109 keyboard */
		0x73,	/* Keyboard Intl' 1 (backslash / underscore) */
		0x70,	/* Keyboard Intl' 2 (Katakana / Hiragana) */
		0x7d,	/* Keyboard Intl' 3 (Yen sign) (Not using in jp106/109) */
		0x79,	/* Keyboard Intl' 4 (Henkan) */
		0x7b,	/* Keyboard Intl' 5 (Muhenkan) */
		0x5c,	/* Keyboard Intl' 6 (Keypad ,) (For PC-9821 layout) */
		0x71,   /* Apple Keyboard JIS (Kana) */
		0x72,   /* Apple Keyboard JIS (Eisu) */
	};

	if ((code >= 89) && (code < (int)(89 + nitems(scan)))) {
		code = scan[code - 89];
	}
	/* PrintScreen */
	if (code == 0x137 && (!(shift & (MOD_CONTROL_L | MOD_CONTROL_R |
	    MOD_SHIFT_L | MOD_SHIFT_R)))) {
		code |= SCAN_PREFIX_SHIFT;
	}
	/* Pause/Break */
	if ((code == 0x146) && (!(shift & (MOD_CONTROL_L | MOD_CONTROL_R)))) {
		code = (0x45 | SCAN_PREFIX_E1 | SCAN_PREFIX_CTL);
	}
	code |= (up ? SCAN_RELEASE : SCAN_PRESS);

	if (code & SCAN_PREFIX) {
		if (code & SCAN_PREFIX_CTL) {
			/* Ctrl */
			sc->sc_buffered_char[0] = (0x1d | (code & SCAN_RELEASE));
			sc->sc_buffered_char[1] = (code & ~SCAN_PREFIX);
		} else if (code & SCAN_PREFIX_SHIFT) {
			/* Shift */
			sc->sc_buffered_char[0] = (0x2a | (code & SCAN_RELEASE));
			sc->sc_buffered_char[1] = (code & ~SCAN_PREFIX_SHIFT);
		} else {
			sc->sc_buffered_char[0] = (code & ~SCAN_PREFIX);
			sc->sc_buffered_char[1] = 0;
		}
		return ((code & SCAN_PREFIX_E0) ? 0xe0 : 0xe1);
	}
	return (code);

}