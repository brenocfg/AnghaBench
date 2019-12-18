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
typedef  int /*<<< orphan*/  usb_dev_handle ;
struct libusb20_device {int claimed_interface; } ;

/* Variables and functions */

int
usb_claim_interface(usb_dev_handle * dev, int interface)
{
	struct libusb20_device *pdev = (void *)dev;

	pdev->claimed_interface = interface;

	return (0);
}