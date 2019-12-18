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

/* Variables and functions */
 int libusb20_dev_reset (void*) ; 
 int usb_close (int /*<<< orphan*/ *) ; 

int
usb_reset(usb_dev_handle * dev)
{
	int err;

	err = libusb20_dev_reset((void *)dev);

	if (err)
		return (-1);

	/*
	 * Be compatible with LibUSB from sourceforge and close the
	 * handle after reset!
	 */
	return (usb_close(dev));
}