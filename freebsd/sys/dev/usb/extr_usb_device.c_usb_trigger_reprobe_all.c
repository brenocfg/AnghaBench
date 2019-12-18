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

/* Variables and functions */
 int /*<<< orphan*/  USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_POWER_DOWN_TIME ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_trigger_reprobe_on_off (int) ; 

__attribute__((used)) static void
usb_trigger_reprobe_all(void)
{

	/*
	 * Set the pull up resistors off for all ports in device mode.
	 */
	usb_trigger_reprobe_on_off(0);

	/*
	 * According to the DWC OTG spec this must be at least 3ms.
	 */
	usb_pause_mtx(NULL, USB_MS_TO_TICKS(USB_POWER_DOWN_TIME));

	/*
	 * Set the pull up resistors back on.
	 */
	usb_trigger_reprobe_on_off(1);
}