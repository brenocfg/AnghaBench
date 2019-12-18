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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {scalar_t__ peer_suspended; } ;
struct usb_device {int /*<<< orphan*/  parent_dev; TYPE_1__ flags; int /*<<< orphan*/  address; int /*<<< orphan*/  port_no; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int DEVICE_RESUME (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_USBDEV ; 
 scalar_t__ device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  rebooting ; 

__attribute__((used)) static void
usb_detach_device_sub(struct usb_device *udev, device_t *ppdev,
    char **ppnpinfo, uint8_t flag)
{
	device_t dev;
	char *pnpinfo;
	int err;

	dev = *ppdev;
	if (dev) {
		/*
		 * NOTE: It is important to clear "*ppdev" before deleting
		 * the child due to some device methods being called late
		 * during the delete process !
		 */
		*ppdev = NULL;

		if (!rebooting) {
			device_printf(dev, "at %s, port %d, addr %d "
			    "(disconnected)\n",
			    device_get_nameunit(udev->parent_dev),
			    udev->port_no, udev->address);
		}

		if (device_is_attached(dev)) {
			if (udev->flags.peer_suspended) {
				err = DEVICE_RESUME(dev);
				if (err) {
					device_printf(dev, "Resume failed\n");
				}
			}
		}
		/* detach and delete child */
		if (device_delete_child(udev->parent_dev, dev)) {
			goto error;
		}
	}

	pnpinfo = *ppnpinfo;
	if (pnpinfo != NULL) {
		*ppnpinfo = NULL;
		free(pnpinfo, M_USBDEV);
	}
	return;

error:
	/* Detach is not allowed to fail in the USB world */
	panic("usb_detach_device_sub: A USB driver would not detach\n");
}