#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* press_str; char* repeat_str; } ;
struct TYPE_4__ {int /*<<< orphan*/  press_data; int /*<<< orphan*/  (* press_fct ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_2__ kbd; TYPE_1__ std; } ;
struct logical_input {int mask; int value; scalar_t__ type; int high_timer; scalar_t__ fall_timer; int /*<<< orphan*/  state; TYPE_3__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  INPUT_ST_FALLING ; 
 int /*<<< orphan*/  INPUT_ST_LOW ; 
 scalar_t__ INPUT_TYPE_KBD ; 
 scalar_t__ INPUT_TYPE_STD ; 
 scalar_t__ KEYPAD_REP_DELAY ; 
 int KEYPAD_REP_START ; 
 scalar_t__ inputs_stable ; 
 int /*<<< orphan*/  keypad_send_key (char*,int) ; 
 int keypressed ; 
 int phys_curr ; 
 int phys_prev ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int input_state_high(struct logical_input *input)
{
#if 0
	/* FIXME:
	 * this is an invalid test. It tries to catch
	 * transitions from single-key to multiple-key, but
	 * doesn't take into account the contacts polarity.
	 * The only solution to the problem is to parse keys
	 * from the most complex to the simplest combinations,
	 * and mark them as 'caught' once a combination
	 * matches, then unmatch it for all other ones.
	 */

	/* try to catch dangerous transitions cases :
	 * someone adds a bit, so this signal was a false
	 * positive resulting from a transition. We should
	 * invalidate the signal immediately and not call the
	 * release function.
	 * eg: 0 -(press A)-> A -(press B)-> AB : don't match A's release.
	 */
	if (((phys_prev & input->mask) == input->value) &&
	    ((phys_curr & input->mask) >  input->value)) {
		input->state = INPUT_ST_LOW; /* invalidate */
		return 1;
	}
#endif

	if ((phys_curr & input->mask) == input->value) {
		if ((input->type == INPUT_TYPE_STD) &&
		    (input->high_timer == 0)) {
			input->high_timer++;
			if (input->u.std.press_fct)
				input->u.std.press_fct(input->u.std.press_data);
		} else if (input->type == INPUT_TYPE_KBD) {
			/* will turn on the light */
			keypressed = 1;

			if (input->high_timer == 0) {
				char *press_str = input->u.kbd.press_str;

				if (press_str[0]) {
					int s = sizeof(input->u.kbd.press_str);

					keypad_send_key(press_str, s);
				}
			}

			if (input->u.kbd.repeat_str[0]) {
				char *repeat_str = input->u.kbd.repeat_str;

				if (input->high_timer >= KEYPAD_REP_START) {
					int s = sizeof(input->u.kbd.repeat_str);

					input->high_timer -= KEYPAD_REP_DELAY;
					keypad_send_key(repeat_str, s);
				}
				/* we will need to come back here soon */
				inputs_stable = 0;
			}

			if (input->high_timer < 255)
				input->high_timer++;
		}
		return 1;
	}

	/* else signal falling down. Let's fall through. */
	input->state = INPUT_ST_FALLING;
	input->fall_timer = 0;

	return 0;
}