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
 int ENXIO ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HAS_QUIRK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KBDC_DISABLE_KBD_PORT ; 
 int /*<<< orphan*/  KBDC_QUIRK_IGNORE_PROBE_RESULT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int KB_CONF_NO_PROBE_TEST ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int get_kbd_echo (int /*<<< orphan*/ ) ; 
 int kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_set_device_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setup_kbd_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_kbd_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_controller_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
probe_keyboard(KBDC kbdc, int flags)
{
	/*
	 * Don't try to print anything in this function.  The low-level 
	 * console may not have been initialized yet...
	 */
	int err;
	int c;
	int m;

	if (!kbdc_lock(kbdc, TRUE)) {
		/* driver error? */
		return ENXIO;
	}

	/* temporarily block data transmission from the keyboard */
	write_controller_command(kbdc, KBDC_DISABLE_KBD_PORT);

	/* flush any noise in the buffer */
	empty_both_buffers(kbdc, 100);

	/* save the current keyboard controller command byte */
	m = kbdc_get_device_mask(kbdc) & ~KBD_KBD_CONTROL_BITS;
	c = get_controller_command_byte(kbdc);
	if (c == -1) {
		/* CONTROLLER ERROR */
		kbdc_set_device_mask(kbdc, m);
		kbdc_lock(kbdc, FALSE);
		return ENXIO;
	}

	/* 
	 * The keyboard may have been screwed up by the boot block.
	 * We may just be able to recover from error by testing the controller
	 * and the keyboard port. The controller command byte needs to be
	 * saved before this recovery operation, as some controllers seem 
	 * to set the command byte to particular values.
	 */
	test_controller(kbdc);
	if (!(flags & KB_CONF_NO_PROBE_TEST))
		test_kbd_port(kbdc);

	err = get_kbd_echo(kbdc);

	/*
	 * Even if the keyboard doesn't seem to be present (err != 0),
	 * we shall enable the keyboard port and interrupt so that
	 * the driver will be operable when the keyboard is attached
	 * to the system later.  It is NOT recommended to hot-plug
	 * the AT keyboard, but many people do so...
	 */
	kbdc_set_device_mask(kbdc, m | KBD_KBD_CONTROL_BITS);
	setup_kbd_port(kbdc, TRUE, TRUE);
#if 0
	if (err == 0) {
		kbdc_set_device_mask(kbdc, m | KBD_KBD_CONTROL_BITS);
	} else {
		/* try to restore the command byte as before */
		set_controller_command_byte(kbdc,
		    ALLOW_DISABLE_KBD(kbdc) ? 0xff : KBD_KBD_CONTROL_BITS, c);
		kbdc_set_device_mask(kbdc, m);
	}
#endif

	kbdc_lock(kbdc, FALSE);
	return (HAS_QUIRK(kbdc, KBDC_QUIRK_IGNORE_PROBE_RESULT) ? 0 : err);
}