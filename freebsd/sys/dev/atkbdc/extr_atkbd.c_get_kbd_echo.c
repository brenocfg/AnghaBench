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
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KBDC_ECHO ; 
 scalar_t__ KBD_ECHO ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 scalar_t__ read_kbd_data (int /*<<< orphan*/ ) ; 
 scalar_t__ setup_kbd_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kbd_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_kbd_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_kbd_echo(KBDC kbdc)
{
	/* enable the keyboard port, but disable the keyboard intr. */
	if (setup_kbd_port(kbdc, TRUE, FALSE))
		/* CONTROLLER ERROR: there is very little we can do... */
		return ENXIO;

	/* see if something is present */
	write_kbd_command(kbdc, KBDC_ECHO);
	if (read_kbd_data(kbdc) != KBD_ECHO) {
		empty_both_buffers(kbdc, 10);
		test_controller(kbdc);
		test_kbd_port(kbdc);
		return ENXIO;
	}

	/* enable the keyboard port and intr. */
	if (setup_kbd_port(kbdc, TRUE, TRUE)) {
		/*
		 * CONTROLLER ERROR 
		 * This is serious; the keyboard intr is left disabled! 
		 */
		return ENXIO;
	}

	return 0;
}