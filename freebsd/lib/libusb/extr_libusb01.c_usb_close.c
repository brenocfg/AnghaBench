#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_dev_handle ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_DEL (int /*<<< orphan*/ ,struct usb_device*) ; 
 int /*<<< orphan*/  free (struct usb_device*) ; 
 int /*<<< orphan*/  libusb20_be_enqueue_device (int /*<<< orphan*/ *,void*) ; 
 int libusb20_dev_close (void*) ; 
 int /*<<< orphan*/  libusb20_dev_free (void*) ; 
 int /*<<< orphan*/ * usb_backend ; 
 struct usb_device* usb_device (int /*<<< orphan*/ *) ; 
 TYPE_1__ usb_global_bus ; 

int
usb_close(usb_dev_handle * udev)
{
	struct usb_device *dev;
	int err;

	err = libusb20_dev_close((void *)udev);

	if (err)
		return (-1);

	if (usb_backend != NULL) {
		/*
		 * Enqueue USB device to backend queue so that it gets freed
		 * when the backend is re-scanned:
		 */
		libusb20_be_enqueue_device(usb_backend, (void *)udev);
	} else {
		/*
		 * The backend is gone. Free device data so that we
		 * don't start leaking memory!
		 */
		dev = usb_device(udev);
		libusb20_dev_free((void *)udev);
		LIST_DEL(usb_global_bus.devices, dev);
		free(dev);
	}
	return (0);
}