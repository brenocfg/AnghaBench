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
typedef  scalar_t__ usb_error_t ;
struct usb_port_status {int /*<<< orphan*/  wPortStatus; } ;
struct usb_device {scalar_t__ refcount; int /*<<< orphan*/  ref_cv; } ;
struct usb_bus {struct usb_device** devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UHF_PORT_POWER ; 
 int UPS_PORT_MODE_DEVICE ; 
 scalar_t__ USB_DEV_REF_MAX ; 
 size_t USB_ROOT_HUB_ADDR ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 int devclass_get_maxunit (int /*<<< orphan*/ ) ; 
 struct usb_bus* devclass_get_softc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_devclass_ptr ; 
 int /*<<< orphan*/  usb_ref_lock ; 
 int usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_req_clear_port_feature (struct usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_get_port_status (struct usb_device*,int /*<<< orphan*/ *,struct usb_port_status*,int) ; 
 scalar_t__ usbd_req_set_port_feature (struct usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usb_trigger_reprobe_on_off(int on_not_off)
{
	struct usb_port_status ps;
	struct usb_bus *bus;
	struct usb_device *udev;
	usb_error_t err;
	int do_unlock, max;

	max = devclass_get_maxunit(usb_devclass_ptr);
	while (max >= 0) {
		mtx_lock(&usb_ref_lock);
		bus = devclass_get_softc(usb_devclass_ptr, max);
		max--;

		if (bus == NULL || bus->devices == NULL ||
		    bus->devices[USB_ROOT_HUB_ADDR] == NULL) {
			mtx_unlock(&usb_ref_lock);
			continue;
		}

		udev = bus->devices[USB_ROOT_HUB_ADDR];

		if (udev->refcount == USB_DEV_REF_MAX) {
			mtx_unlock(&usb_ref_lock);
			continue;
		}

		udev->refcount++;
		mtx_unlock(&usb_ref_lock);

		do_unlock = usbd_enum_lock(udev);
		if (do_unlock > 1) {
			do_unlock = 0;
			goto next;
		}

		err = usbd_req_get_port_status(udev, NULL, &ps, 1);
		if (err != 0) {
			DPRINTF("usbd_req_get_port_status() "
			    "failed: %s\n", usbd_errstr(err));
			goto next;
		}

		if ((UGETW(ps.wPortStatus) & UPS_PORT_MODE_DEVICE) == 0)
			goto next;

		if (on_not_off) {
			err = usbd_req_set_port_feature(udev, NULL, 1,
			    UHF_PORT_POWER);
			if (err != 0) {
				DPRINTF("usbd_req_set_port_feature() "
				    "failed: %s\n", usbd_errstr(err));
			}
		} else {
			err = usbd_req_clear_port_feature(udev, NULL, 1,
			    UHF_PORT_POWER);
			if (err != 0) {
				DPRINTF("usbd_req_clear_port_feature() "
				    "failed: %s\n", usbd_errstr(err));
			}
		}

next:
		mtx_lock(&usb_ref_lock);
		if (do_unlock)
			usbd_enum_unlock(udev);
		if (--(udev->refcount) == 0)
			cv_broadcast(&udev->ref_cv);
		mtx_unlock(&usb_ref_lock);
	}
}