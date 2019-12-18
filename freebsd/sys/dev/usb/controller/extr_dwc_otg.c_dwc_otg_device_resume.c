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
struct usb_device {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  dwc_otg_do_poll (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_otg_device_resume(struct usb_device *udev)
{
	DPRINTF("\n");

	/* poll all transfers again to restart resumed ones */
	dwc_otg_do_poll(udev->bus);
}