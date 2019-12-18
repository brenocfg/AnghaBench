#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ kb_data; } ;
typedef  TYPE_1__ keyboard_t ;
struct TYPE_7__ {int /*<<< orphan*/  ks_timer; } ;
typedef  TYPE_2__ atkbd_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),void*) ; 
 int hz ; 
 scalar_t__ kbdd_check_char (TYPE_1__*) ; 
 int /*<<< orphan*/  kbdd_intr (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ kbdd_lock (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static void
atkbd_timeout(void *arg)
{
	atkbd_state_t *state;
	keyboard_t *kbd;
	int s;

	/*
	 * The original text of the following comments are extracted 
	 * from syscons.c (1.287)
	 * 
	 * With release 2.1 of the Xaccel server, the keyboard is left
	 * hanging pretty often. Apparently an interrupt from the
	 * keyboard is lost, and I don't know why (yet).
	 * This ugly hack calls the low-level interrupt routine if input
	 * is ready for the keyboard and conveniently hides the problem. XXX
	 *
	 * Try removing anything stuck in the keyboard controller; whether
	 * it's a keyboard scan code or mouse data. The low-level
	 * interrupt routine doesn't read the mouse data directly, 
	 * but the keyboard controller driver will, as a side effect.
	 */
	/*
	 * And here is bde's original comment about this:
	 *
	 * This is necessary to handle edge triggered interrupts - if we
	 * returned when our IRQ is high due to unserviced input, then there
	 * would be no more keyboard IRQs until the keyboard is reset by
	 * external powers.
	 *
	 * The keyboard apparently unwedges the irq in most cases.
	 */
	s = spltty();
	kbd = (keyboard_t *)arg;
	if (kbdd_lock(kbd, TRUE)) {
		/*
		 * We have seen the lock flag is not set. Let's reset
		 * the flag early, otherwise the LED update routine fails
		 * which may want the lock during the interrupt routine.
		 */
		kbdd_lock(kbd, FALSE);
		if (kbdd_check_char(kbd))
			kbdd_intr(kbd, NULL);
	}
	splx(s);
	state = (atkbd_state_t *)kbd->kb_data;
	callout_reset(&state->ks_timer, hz / 10, atkbd_timeout, arg);
}