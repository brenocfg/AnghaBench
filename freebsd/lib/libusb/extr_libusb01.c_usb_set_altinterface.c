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
typedef  int /*<<< orphan*/  uint8_t ;
struct libusb20_device {int /*<<< orphan*/  claimed_interface; } ;

/* Variables and functions */
 int libusb20_dev_set_alt_index (void*,int /*<<< orphan*/ ,int) ; 

int
usb_set_altinterface(usb_dev_handle * dev, int alternate)
{
	struct libusb20_device *pdev = (void *)dev;
	int err;
	uint8_t iface;

	iface = pdev->claimed_interface;

	err = libusb20_dev_set_alt_index((void *)dev, iface, alternate);

	if (err)
		return (-1);

	return (0);
}