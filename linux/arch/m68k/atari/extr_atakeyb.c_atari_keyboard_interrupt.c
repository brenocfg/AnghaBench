#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int mid_ctrl; int key_ctrl; int key_data; } ;
struct TYPE_3__ {int state; int len; int* buf; } ;

/* Variables and functions */
 int ACIA_CTS ; 
 int ACIA_FE ; 
 int ACIA_IRQ ; 
 int ACIA_OVRN ; 
 int ACIA_PE ; 
 int ACIA_RDRF ; 
#define  AMOUSE 133 
 int BREAK_MASK ; 
#define  CLOCK 132 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 scalar_t__ IS_SYNC_CODE (int) ; 
#define  JOYSTICK 131 
#define  KEYBOARD 130 
 int /*<<< orphan*/  KTYP (int) ; 
 int KT_LATIN ; 
 int KT_LETTER ; 
 int KVAL (int) ; 
#define  RESYNC 129 
#define  RMOUSE 128 
 TYPE_2__ acia ; 
 int /*<<< orphan*/  atari_MIDI_interrupt_hook () ; 
 int /*<<< orphan*/  atari_input_keyboard_interrupt_hook (unsigned char,int) ; 
 int /*<<< orphan*/  atari_input_mouse_interrupt_hook (int*) ; 
 int /*<<< orphan*/  atari_joystick_interrupt (int*) ; 
 int /*<<< orphan*/  broken_keys ; 
 scalar_t__ ikbd_self_test ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__ kb_state ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 
 int /*<<< orphan*/  self_test_last_rcv ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t atari_keyboard_interrupt(int irq, void *dummy)
{
	u_char acia_stat;
	int scancode;
	int break_flag;

repeat:
	if (acia.mid_ctrl & ACIA_IRQ)
		if (atari_MIDI_interrupt_hook)
			atari_MIDI_interrupt_hook();
	acia_stat = acia.key_ctrl;
	/* check out if the interrupt came from this ACIA */
	if (!((acia_stat | acia.mid_ctrl) & ACIA_IRQ))
		return IRQ_HANDLED;

	if (acia_stat & ACIA_OVRN) {
		/* a very fast typist or a slow system, give a warning */
		/* ...happens often if interrupts were disabled for too long */
		pr_debug("Keyboard overrun\n");
		scancode = acia.key_data;
		if (ikbd_self_test)
			/* During self test, don't do resyncing, just process the code */
			goto interpret_scancode;
		else if (IS_SYNC_CODE(scancode)) {
			/* This code seem already to be the start of a new packet or a
			 * single scancode */
			kb_state.state = KEYBOARD;
			goto interpret_scancode;
		} else {
			/* Go to RESYNC state and skip this byte */
			kb_state.state = RESYNC;
			kb_state.len = 1;	/* skip max. 1 another byte */
			goto repeat;
		}
	}

	if (acia_stat & ACIA_RDRF) {
		/* received a character */
		scancode = acia.key_data;	/* get it or reset the ACIA, I'll get it! */
	interpret_scancode:
		switch (kb_state.state) {
		case KEYBOARD:
			switch (scancode) {
			case 0xF7:
				kb_state.state = AMOUSE;
				kb_state.len = 0;
				break;

			case 0xF8:
			case 0xF9:
			case 0xFA:
			case 0xFB:
				kb_state.state = RMOUSE;
				kb_state.len = 1;
				kb_state.buf[0] = scancode;
				break;

			case 0xFC:
				kb_state.state = CLOCK;
				kb_state.len = 0;
				break;

			case 0xFE:
			case 0xFF:
				kb_state.state = JOYSTICK;
				kb_state.len = 1;
				kb_state.buf[0] = scancode;
				break;

			case 0xF1:
				/* during self-test, note that 0xf1 received */
				if (ikbd_self_test) {
					++ikbd_self_test;
					self_test_last_rcv = jiffies;
					break;
				}
				/* FALL THROUGH */

			default:
				break_flag = scancode & BREAK_MASK;
				scancode &= ~BREAK_MASK;
				if (ikbd_self_test) {
					/* Scancodes sent during the self-test stand for broken
					 * keys (keys being down). The code *should* be a break
					 * code, but nevertheless some AT keyboard interfaces send
					 * make codes instead. Therefore, simply ignore
					 * break_flag...
					 */
					int keyval, keytyp;

					set_bit(scancode, broken_keys);
					self_test_last_rcv = jiffies;
					/* new Linux scancodes; approx. */
					keyval = scancode;
					keytyp = KTYP(keyval) - 0xf0;
					keyval = KVAL(keyval);

					pr_warn("Key with scancode %d ", scancode);
					if (keytyp == KT_LATIN || keytyp == KT_LETTER) {
						if (keyval < ' ')
							pr_cont("('^%c') ", keyval + '@');
						else
							pr_cont("('%c') ", keyval);
					}
					pr_cont("is broken -- will be ignored.\n");
					break;
				} else if (test_bit(scancode, broken_keys))
					break;

				if (atari_input_keyboard_interrupt_hook)
					atari_input_keyboard_interrupt_hook((unsigned char)scancode, !break_flag);
				break;
			}
			break;

		case AMOUSE:
			kb_state.buf[kb_state.len++] = scancode;
			if (kb_state.len == 5) {
				kb_state.state = KEYBOARD;
				/* not yet used */
				/* wake up someone waiting for this */
			}
			break;

		case RMOUSE:
			kb_state.buf[kb_state.len++] = scancode;
			if (kb_state.len == 3) {
				kb_state.state = KEYBOARD;
				if (atari_input_mouse_interrupt_hook)
					atari_input_mouse_interrupt_hook(kb_state.buf);
			}
			break;

		case JOYSTICK:
			kb_state.buf[1] = scancode;
			kb_state.state = KEYBOARD;
#ifdef FIXED_ATARI_JOYSTICK
			atari_joystick_interrupt(kb_state.buf);
#endif
			break;

		case CLOCK:
			kb_state.buf[kb_state.len++] = scancode;
			if (kb_state.len == 6) {
				kb_state.state = KEYBOARD;
				/* wake up someone waiting for this.
				   But will this ever be used, as Linux keeps its own time.
				   Perhaps for synchronization purposes? */
				/* wake_up_interruptible(&clock_wait); */
			}
			break;

		case RESYNC:
			if (kb_state.len <= 0 || IS_SYNC_CODE(scancode)) {
				kb_state.state = KEYBOARD;
				goto interpret_scancode;
			}
			kb_state.len--;
			break;
		}
	}

#if 0
	if (acia_stat & ACIA_CTS)
		/* cannot happen */;
#endif

	if (acia_stat & (ACIA_FE | ACIA_PE)) {
		pr_err("Error in keyboard communication\n");
	}

	/* handle_scancode() can take a lot of time, so check again if
	 * some character arrived
	 */
	goto repeat;
}