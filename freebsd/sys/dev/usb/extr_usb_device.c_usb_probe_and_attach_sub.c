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
typedef  int uint8_t ;
struct usb_interface {scalar_t__ parent_iface_index; int /*<<< orphan*/ * subdev; } ;
struct TYPE_2__ {scalar_t__ peer_suspended; } ;
struct usb_device {TYPE_1__ flags; int /*<<< orphan*/ * parent_dev; } ;
struct usb_attach_arg {int /*<<< orphan*/ * temp_dev; struct usb_interface* iface; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int DEVICE_SUSPEND (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_IFACE_INDEX_ANY ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ device_probe_and_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_quiet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct usb_attach_arg*) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static uint8_t
usb_probe_and_attach_sub(struct usb_device *udev,
    struct usb_attach_arg *uaa)
{
	struct usb_interface *iface;
	device_t dev;
	int err;

	iface = uaa->iface;
	if (iface->parent_iface_index != USB_IFACE_INDEX_ANY) {
		/* leave interface alone */
		return (0);
	}
	dev = iface->subdev;
	if (dev) {

		/* clean up after module unload */

		if (device_is_attached(dev)) {
			/* already a device there */
			return (0);
		}
		/* clear "iface->subdev" as early as possible */

		iface->subdev = NULL;

		if (device_delete_child(udev->parent_dev, dev)) {

			/*
			 * Panic here, else one can get a double call
			 * to device_detach().  USB devices should
			 * never fail on detach!
			 */
			panic("device_delete_child() failed\n");
		}
	}
	if (uaa->temp_dev == NULL) {

		/* create a new child */
		uaa->temp_dev = device_add_child(udev->parent_dev, NULL, -1);
		if (uaa->temp_dev == NULL) {
			device_printf(udev->parent_dev,
			    "Device creation failed\n");
			return (1);	/* failure */
		}
		device_set_ivars(uaa->temp_dev, uaa);
		device_quiet(uaa->temp_dev);
	}
	/*
	 * Set "subdev" before probe and attach so that "devd" gets
	 * the information it needs.
	 */
	iface->subdev = uaa->temp_dev;

	if (device_probe_and_attach(iface->subdev) == 0) {
		/*
		 * The USB attach arguments are only available during probe
		 * and attach !
		 */
		uaa->temp_dev = NULL;
		device_set_ivars(iface->subdev, NULL);

		if (udev->flags.peer_suspended) {
			err = DEVICE_SUSPEND(iface->subdev);
			if (err)
				device_printf(iface->subdev, "Suspend failed\n");
		}
		return (0);		/* success */
	} else {
		/* No USB driver found */
		iface->subdev = NULL;
	}
	return (1);			/* failure */
}