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
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  VLOG (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  empty_both_buffers (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  reset_kbd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_controller (int /*<<< orphan*/ ) ; 
 scalar_t__ test_kbd_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
recover_from_error(KBDC kbdc)
{
	/* discard anything left in the output buffer */
	empty_both_buffers(kbdc, 10);

#if 0
	/*
	 * NOTE: KBDC_RESET_KBD may not restore the communication between the
	 * keyboard and the controller.
	 */
	reset_kbd(kbdc);
#else
	/*
	 * NOTE: somehow diagnostic and keyboard port test commands bring the
	 * keyboard back.
	 */
	if (!test_controller(kbdc))
		log(LOG_ERR, "psm: keyboard controller failed.\n");
	/* if there isn't a keyboard in the system, the following error is OK */
	if (test_kbd_port(kbdc) != 0)
		VLOG(1, (LOG_ERR, "psm: keyboard port failed.\n"));
#endif
}