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
typedef  int /*<<< orphan*/  KBDC ;

/* Variables and functions */
 scalar_t__ ALLOW_DISABLE_KBD (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int KBD_KBD_CONTROL_BITS ; 
 int KB_CONF_NO_RESET ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reset_kbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kbd_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
atkbd_reset(KBDC kbdc, int flags, int c)
{
	/* reset keyboard hardware */
	if (!(flags & KB_CONF_NO_RESET) && !reset_kbd(kbdc)) {
		/*
		 * KEYBOARD ERROR
		 * Keyboard reset may fail either because the keyboard
		 * doen't exist, or because the keyboard doesn't pass
		 * the self-test, or the keyboard controller on the
		 * motherboard and the keyboard somehow fail to shake hands.
		 * It is just possible, particularly in the last case,
		 * that the keyboard controller may be left in a hung state.
		 * test_controller() and test_kbd_port() appear to bring
		 * the keyboard controller back (I don't know why and how,
		 * though.)
		 */
		empty_both_buffers(kbdc, 10);
		test_controller(kbdc);
		test_kbd_port(kbdc);
		/*
		 * We could disable the keyboard port and interrupt... but, 
		 * the keyboard may still exist (see above). 
		 */
		set_controller_command_byte(kbdc,
		    ALLOW_DISABLE_KBD(kbdc) ? 0xff : KBD_KBD_CONTROL_BITS, c);
		if (bootverbose)
			printf("atkbd: failed to reset the keyboard.\n");
		return (EIO);
	}
	return (0);
}