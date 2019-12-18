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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct ukbd_softc {int sc_flags; int /*<<< orphan*/  sc_id_scrolllock; int /*<<< orphan*/  sc_loc_scrolllock; int /*<<< orphan*/  sc_id_capslock; int /*<<< orphan*/  sc_loc_capslock; int /*<<< orphan*/  sc_id_numlock; int /*<<< orphan*/  sc_loc_numlock; void* sc_led_size; int /*<<< orphan*/  sc_id_events; int /*<<< orphan*/  sc_loc_events; int /*<<< orphan*/  sc_id_win_r; int /*<<< orphan*/  sc_loc_win_r; int /*<<< orphan*/  sc_id_win_l; int /*<<< orphan*/  sc_loc_win_l; int /*<<< orphan*/  sc_id_alt_r; int /*<<< orphan*/  sc_loc_alt_r; int /*<<< orphan*/  sc_id_alt_l; int /*<<< orphan*/  sc_loc_alt_l; int /*<<< orphan*/  sc_id_shift_r; int /*<<< orphan*/  sc_loc_shift_r; int /*<<< orphan*/  sc_id_shift_l; int /*<<< orphan*/  sc_loc_shift_l; int /*<<< orphan*/  sc_id_ctrl_r; int /*<<< orphan*/  sc_loc_ctrl_r; int /*<<< orphan*/  sc_id_ctrl_l; int /*<<< orphan*/  sc_loc_ctrl_l; int /*<<< orphan*/  sc_id_apple_fn; int /*<<< orphan*/  sc_loc_apple_fn; int /*<<< orphan*/  sc_id_apple_eject; int /*<<< orphan*/  sc_loc_apple_eject; int /*<<< orphan*/  sc_kbd_id; void* sc_kbd_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  HID_USAGE2 (int,int) ; 
 int HIO_VARIABLE ; 
 int HUG_APPLE_EJECT ; 
 int HUP_CONSUMER ; 
 int HUP_KEYBOARD ; 
 int HUP_LEDS ; 
 int UKBD_FLAG_ALT_L ; 
 int UKBD_FLAG_ALT_R ; 
 int UKBD_FLAG_APPLE_EJECT ; 
 int UKBD_FLAG_APPLE_FN ; 
 int UKBD_FLAG_APPLE_SWAP ; 
 int UKBD_FLAG_CAPSLOCK ; 
 int UKBD_FLAG_CTRL_L ; 
 int UKBD_FLAG_CTRL_R ; 
 int UKBD_FLAG_EVENTS ; 
 int UKBD_FLAG_HID_MASK ; 
 int UKBD_FLAG_NUMLOCK ; 
 int UKBD_FLAG_SCROLLLOCK ; 
 int UKBD_FLAG_SHIFT_L ; 
 int UKBD_FLAG_SHIFT_R ; 
 int UKBD_FLAG_WIN_L ; 
 int UKBD_FLAG_WIN_R ; 
 int /*<<< orphan*/  hid_input ; 
 scalar_t__ hid_locate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_output ; 
 void* hid_report_size (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ukbd_parse_hid(struct ukbd_softc *sc, const uint8_t *ptr, uint32_t len)
{
	uint32_t flags;

	/* reset detected bits */
	sc->sc_flags &= ~UKBD_FLAG_HID_MASK;

	/* check if there is an ID byte */
	sc->sc_kbd_size = hid_report_size(ptr, len,
	    hid_input, &sc->sc_kbd_id);

	/* investigate if this is an Apple Keyboard */
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_CONSUMER, HUG_APPLE_EJECT),
	    hid_input, 0, &sc->sc_loc_apple_eject, &flags,
	    &sc->sc_id_apple_eject)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_APPLE_EJECT | 
			    UKBD_FLAG_APPLE_SWAP;
		DPRINTFN(1, "Found Apple eject-key\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(0xFFFF, 0x0003),
	    hid_input, 0, &sc->sc_loc_apple_fn, &flags,
	    &sc->sc_id_apple_fn)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_APPLE_FN;
		DPRINTFN(1, "Found Apple FN-key\n");
	}
	/* figure out some keys */
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE0),
	    hid_input, 0, &sc->sc_loc_ctrl_l, &flags,
	    &sc->sc_id_ctrl_l)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_CTRL_L;
		DPRINTFN(1, "Found left control\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE4),
	    hid_input, 0, &sc->sc_loc_ctrl_r, &flags,
	    &sc->sc_id_ctrl_r)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_CTRL_R;
		DPRINTFN(1, "Found right control\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE1),
	    hid_input, 0, &sc->sc_loc_shift_l, &flags,
	    &sc->sc_id_shift_l)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_SHIFT_L;
		DPRINTFN(1, "Found left shift\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE5),
	    hid_input, 0, &sc->sc_loc_shift_r, &flags,
	    &sc->sc_id_shift_r)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_SHIFT_R;
		DPRINTFN(1, "Found right shift\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE2),
	    hid_input, 0, &sc->sc_loc_alt_l, &flags,
	    &sc->sc_id_alt_l)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_ALT_L;
		DPRINTFN(1, "Found left alt\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE6),
	    hid_input, 0, &sc->sc_loc_alt_r, &flags,
	    &sc->sc_id_alt_r)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_ALT_R;
		DPRINTFN(1, "Found right alt\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE3),
	    hid_input, 0, &sc->sc_loc_win_l, &flags,
	    &sc->sc_id_win_l)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_WIN_L;
		DPRINTFN(1, "Found left GUI\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0xE7),
	    hid_input, 0, &sc->sc_loc_win_r, &flags,
	    &sc->sc_id_win_r)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_WIN_R;
		DPRINTFN(1, "Found right GUI\n");
	}
	/* figure out event buffer */
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_KEYBOARD, 0x00),
	    hid_input, 0, &sc->sc_loc_events, &flags,
	    &sc->sc_id_events)) {
		if (flags & HIO_VARIABLE) {
			DPRINTFN(1, "Ignoring keyboard event control\n");
		} else {
			sc->sc_flags |= UKBD_FLAG_EVENTS;
			DPRINTFN(1, "Found keyboard event array\n");
		}
	}

	/* figure out leds on keyboard */
	sc->sc_led_size = hid_report_size(ptr, len,
	    hid_output, NULL);

	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_LEDS, 0x01),
	    hid_output, 0, &sc->sc_loc_numlock, &flags,
	    &sc->sc_id_numlock)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_NUMLOCK;
		DPRINTFN(1, "Found keyboard numlock\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_LEDS, 0x02),
	    hid_output, 0, &sc->sc_loc_capslock, &flags,
	    &sc->sc_id_capslock)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_CAPSLOCK;
		DPRINTFN(1, "Found keyboard capslock\n");
	}
	if (hid_locate(ptr, len,
	    HID_USAGE2(HUP_LEDS, 0x03),
	    hid_output, 0, &sc->sc_loc_scrolllock, &flags,
	    &sc->sc_id_scrolllock)) {
		if (flags & HIO_VARIABLE)
			sc->sc_flags |= UKBD_FLAG_SCROLLLOCK;
		DPRINTFN(1, "Found keyboard scrolllock\n");
	}
}