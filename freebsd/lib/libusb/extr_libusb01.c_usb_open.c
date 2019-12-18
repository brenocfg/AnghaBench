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
struct usb_device {int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int LIBUSB20_ERROR_BUSY ; 
 int /*<<< orphan*/  libusb20_be_dequeue_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int libusb20_dev_open (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_backend ; 

usb_dev_handle *
usb_open(struct usb_device *dev)
{
	int err;

	err = libusb20_dev_open(dev->dev, 16 * 2);
	if (err == LIBUSB20_ERROR_BUSY) {
		/*
		 * Workaround buggy USB applications which open the USB
		 * device multiple times:
		 */
		return (dev->dev);
	}
	if (err)
		return (NULL);

	/*
	 * Dequeue USB device from backend queue so that it does not get
	 * freed when the backend is re-scanned:
	 */
	libusb20_be_dequeue_device(usb_backend, dev->dev);

	return (dev->dev);
}