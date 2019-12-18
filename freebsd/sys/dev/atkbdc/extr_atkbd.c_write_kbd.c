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
 int EBUSY ; 
 int EIO ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KBDC_ENABLE_KBD ; 
 scalar_t__ KBD_ACK ; 
 int KBD_AUX_CONTROL_BITS ; 
 int KBD_DISABLE_AUX_INT ; 
 int KBD_DISABLE_AUX_PORT ; 
 int KBD_DISABLE_KBD_INT ; 
 int KBD_DISABLE_KBD_PORT ; 
 int KBD_KBD_CONTROL_BITS ; 
 int /*<<< orphan*/  TRUE ; 
 int c ; 
 int get_controller_command_byte (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_get_device_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbdc_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_kbd_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ send_kbd_command_and_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_controller_command_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int spltty () ; 
 int /*<<< orphan*/  splx (int) ; 

__attribute__((used)) static int
write_kbd(KBDC kbdc, int command, int data)
{
	int s;

	/* prevent the timeout routine from polling the keyboard */
	if (!kbdc_lock(kbdc, TRUE)) 
		return EBUSY;

	/* disable the keyboard and mouse interrupt */
	s = spltty();
#if 0
	c = get_controller_command_byte(kbdc);
	if ((c == -1) 
	    || !set_controller_command_byte(kbdc, 
		kbdc_get_device_mask(kbdc),
		KBD_DISABLE_KBD_PORT | KBD_DISABLE_KBD_INT
		| KBD_DISABLE_AUX_PORT | KBD_DISABLE_AUX_INT)) {
		/* CONTROLLER ERROR */
		kbdc_lock(kbdc, FALSE);
		splx(s);
		return EIO;
	}
	/* 
	 * Now that the keyboard controller is told not to generate 
	 * the keyboard and mouse interrupts, call `splx()' to allow 
	 * the other tty interrupts. The clock interrupt may also occur, 
	 * but the timeout routine (`scrn_timer()') will be blocked 
	 * by the lock flag set via `kbdc_lock()'
	 */
	splx(s);
#endif
	if (send_kbd_command_and_data(kbdc, command, data) != KBD_ACK)
		send_kbd_command(kbdc, KBDC_ENABLE_KBD);
#if 0
	/* restore the interrupts */
	if (!set_controller_command_byte(kbdc, kbdc_get_device_mask(kbdc),
	    c & (KBD_KBD_CONTROL_BITS | KBD_AUX_CONTROL_BITS))) { 
		/* CONTROLLER ERROR */
	}
#else
	splx(s);
#endif
	kbdc_lock(kbdc, FALSE);

	return 0;
}