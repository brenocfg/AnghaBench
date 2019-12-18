#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
typedef  scalar_t__ u_int ;
struct TYPE_5__ {scalar_t__ kb_type; int /*<<< orphan*/  kb_count; scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_6__ {int ks_flags; scalar_t__ ks_composed_char; scalar_t__ ks_mode; int ks_prefix; int /*<<< orphan*/  ks_accents; int /*<<< orphan*/  ks_state; int /*<<< orphan*/ * ks_evdev; int /*<<< orphan*/  ks_evdev_state; int /*<<< orphan*/  kbdc; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int ALTS ; 
 int COMPOSE ; 
 int CTLS ; 
 scalar_t__ ERRKEY ; 
 int EVDEV_RCPT_HW_KBD ; 
 int /*<<< orphan*/  EV_KEY ; 
 scalar_t__ KB_101 ; 
 scalar_t__ KB_84 ; 
 int KEY_RESERVED ; 
 scalar_t__ K_CODE ; 
 scalar_t__ K_RAW ; 
 scalar_t__ NOKEY ; 
 int SHIFTS ; 
 scalar_t__ UCHAR_MAX ; 
 int /*<<< orphan*/  evdev_push_event (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int evdev_rcpt_mask ; 
 int evdev_scancode2key (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  evdev_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ genkbd_keyaction (TYPE_1__*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int read_kbd_data (int /*<<< orphan*/ ) ; 
 int read_kbd_data_no_wait (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
atkbd_read_char(keyboard_t *kbd, int wait)
{
	atkbd_state_t *state;
	u_int action;
	int scancode;
	int keycode;

	state = (atkbd_state_t *)kbd->kb_data;
next_code:
	/* do we have a composed char to return? */
	if (!(state->ks_flags & COMPOSE) && (state->ks_composed_char > 0)) {
		action = state->ks_composed_char;
		state->ks_composed_char = 0;
		if (action > UCHAR_MAX)
			return ERRKEY;
		return action;
	}

	/* see if there is something in the keyboard port */
	if (wait) {
		do {
			scancode = read_kbd_data(state->kbdc);
		} while (scancode == -1);
	} else {
		scancode = read_kbd_data_no_wait(state->kbdc);
		if (scancode == -1)
			return NOKEY;
	}
	++kbd->kb_count;

#if KBDIO_DEBUG >= 10
	printf("atkbd_read_char(): scancode:0x%x\n", scancode);
#endif

#ifdef EVDEV_SUPPORT
	/* push evdev event */
	if (evdev_rcpt_mask & EVDEV_RCPT_HW_KBD && state->ks_evdev != NULL) {
		keycode = evdev_scancode2key(&state->ks_evdev_state,
		    scancode);

		if (keycode != KEY_RESERVED) {
			evdev_push_event(state->ks_evdev, EV_KEY,
			    (uint16_t)keycode, scancode & 0x80 ? 0 : 1);
			evdev_sync(state->ks_evdev);
		}
	}
#endif

	/* return the byte as is for the K_RAW mode */
	if (state->ks_mode == K_RAW)
		return scancode;

	/* translate the scan code into a keycode */
	keycode = scancode & 0x7F;
	switch (state->ks_prefix) {
	case 0x00:	/* normal scancode */
		switch(scancode) {
		case 0xB8:	/* left alt (compose key) released */
			if (state->ks_flags & COMPOSE) {
				state->ks_flags &= ~COMPOSE;
				if (state->ks_composed_char > UCHAR_MAX)
					state->ks_composed_char = 0;
			}
			break;
		case 0x38:	/* left alt (compose key) pressed */
			if (!(state->ks_flags & COMPOSE)) {
				state->ks_flags |= COMPOSE;
				state->ks_composed_char = 0;
			}
			break;
		case 0xE0:
		case 0xE1:
			state->ks_prefix = scancode;
			goto next_code;
		}
		break;
	case 0xE0:		/* 0xE0 prefix */
		state->ks_prefix = 0;
		switch (keycode) {
		case 0x1C:	/* right enter key */
			keycode = 0x59;
			break;
		case 0x1D:	/* right ctrl key */
			keycode = 0x5A;
			break;
		case 0x35:	/* keypad divide key */
			keycode = 0x5B;
			break;
		case 0x37:	/* print scrn key */
			keycode = 0x5C;
			break;
		case 0x38:	/* right alt key (alt gr) */
			keycode = 0x5D;
			break;
		case 0x46:	/* ctrl-pause/break on AT 101 (see below) */
			keycode = 0x68;
			break;
		case 0x47:	/* grey home key */
			keycode = 0x5E;
			break;
		case 0x48:	/* grey up arrow key */
			keycode = 0x5F;
			break;
		case 0x49:	/* grey page up key */
			keycode = 0x60;
			break;
		case 0x4B:	/* grey left arrow key */
			keycode = 0x61;
			break;
		case 0x4D:	/* grey right arrow key */
			keycode = 0x62;
			break;
		case 0x4F:	/* grey end key */
			keycode = 0x63;
			break;
		case 0x50:	/* grey down arrow key */
			keycode = 0x64;
			break;
		case 0x51:	/* grey page down key */
			keycode = 0x65;
			break;
		case 0x52:	/* grey insert key */
			keycode = 0x66;
			break;
		case 0x53:	/* grey delete key */
			keycode = 0x67;
			break;
			/* the following 3 are only used on the MS "Natural" keyboard */
		case 0x5b:	/* left Window key */
			keycode = 0x69;
			break;
		case 0x5c:	/* right Window key */
			keycode = 0x6a;
			break;
		case 0x5d:	/* menu key */
			keycode = 0x6b;
			break;
		case 0x5e:	/* power key */
			keycode = 0x6d;
			break;
		case 0x5f:	/* sleep key */
			keycode = 0x6e;
			break;
		case 0x63:	/* wake key */
			keycode = 0x6f;
			break;
		default:	/* ignore everything else */
			goto next_code;
		}
		break;
   	case 0xE1:	/* 0xE1 prefix */
		/* 
		 * The pause/break key on the 101 keyboard produces:
		 * E1-1D-45 E1-9D-C5
		 * Ctrl-pause/break produces:
		 * E0-46 E0-C6 (See above.)
		 */
		state->ks_prefix = 0;
		if (keycode == 0x1D)
			state->ks_prefix = 0x1D;
		goto next_code;
		/* NOT REACHED */
   	case 0x1D:	/* pause / break */
		state->ks_prefix = 0;
		if (keycode != 0x45)
			goto next_code;
		keycode = 0x68;
		break;
	}

	if (kbd->kb_type == KB_84) {
		switch (keycode) {
		case 0x37:	/* *(numpad)/print screen */
			if (state->ks_flags & SHIFTS)
				keycode = 0x5c;	/* print screen */
			break;
		case 0x45:	/* num lock/pause */
			if (state->ks_flags & CTLS)
				keycode = 0x68;	/* pause */
			break;
		case 0x46:	/* scroll lock/break */
			if (state->ks_flags & CTLS)
				keycode = 0x6c;	/* break */
			break;
		}
	} else if (kbd->kb_type == KB_101) {
		switch (keycode) {
		case 0x5c:	/* print screen */
			if (state->ks_flags & ALTS)
				keycode = 0x54;	/* sysrq */
			break;
		case 0x68:	/* pause/break */
			if (state->ks_flags & CTLS)
				keycode = 0x6c;	/* break */
			break;
		}
	}

	/* return the key code in the K_CODE mode */
	if (state->ks_mode == K_CODE)
		return (keycode | (scancode & 0x80));

	/* compose a character code */
	if (state->ks_flags & COMPOSE) {
		switch (keycode | (scancode & 0x80)) {
		/* key pressed, process it */
		case 0x47: case 0x48: case 0x49:	/* keypad 7,8,9 */
			state->ks_composed_char *= 10;
			state->ks_composed_char += keycode - 0x40;
			if (state->ks_composed_char > UCHAR_MAX)
				return ERRKEY;
			goto next_code;
		case 0x4B: case 0x4C: case 0x4D:	/* keypad 4,5,6 */
			state->ks_composed_char *= 10;
			state->ks_composed_char += keycode - 0x47;
			if (state->ks_composed_char > UCHAR_MAX)
				return ERRKEY;
			goto next_code;
		case 0x4F: case 0x50: case 0x51:	/* keypad 1,2,3 */
			state->ks_composed_char *= 10;
			state->ks_composed_char += keycode - 0x4E;
			if (state->ks_composed_char > UCHAR_MAX)
				return ERRKEY;
			goto next_code;
		case 0x52:				/* keypad 0 */
			state->ks_composed_char *= 10;
			if (state->ks_composed_char > UCHAR_MAX)
				return ERRKEY;
			goto next_code;

		/* key released, no interest here */
		case 0xC7: case 0xC8: case 0xC9:	/* keypad 7,8,9 */
		case 0xCB: case 0xCC: case 0xCD:	/* keypad 4,5,6 */
		case 0xCF: case 0xD0: case 0xD1:	/* keypad 1,2,3 */
		case 0xD2:				/* keypad 0 */
			goto next_code;

		case 0x38:				/* left alt key */
			break;

		default:
			if (state->ks_composed_char > 0) {
				state->ks_flags &= ~COMPOSE;
				state->ks_composed_char = 0;
				return ERRKEY;
			}
			break;
		}
	}

	/* keycode to key action */
	action = genkbd_keyaction(kbd, keycode, scancode & 0x80,
				  &state->ks_state, &state->ks_accents);
	if (action == NOKEY)
		goto next_code;
	else
		return action;
}