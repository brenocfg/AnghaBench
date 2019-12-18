#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_status {int /*<<< orphan*/  wStatus; } ;
struct TYPE_6__ {scalar_t__ usb_mode; int self_powered; int /*<<< orphan*/  uq_bus_powered; } ;
struct usb_device {scalar_t__ state; int power; int curr_config_index; int /*<<< orphan*/  curr_config_no; TYPE_3__ flags; TYPE_2__* parent_hub; int /*<<< orphan*/  address; struct usb_config_descriptor* cdesc; } ;
struct usb_config_descriptor {int bmAttributes; int bMaxPower; int /*<<< orphan*/  bConfigurationValue; } ;
struct TYPE_5__ {TYPE_1__* hub; } ;
struct TYPE_4__ {int portpower; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int UC_BUS_POWERED ; 
 int UC_SELF_POWERED ; 
 int UDESC_CONFIG ; 
 int UDS_SELF_POWERED ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CFG_ALLOC ; 
 int /*<<< orphan*/  USB_CFG_INIT ; 
 scalar_t__ USB_ERR_NO_POWER ; 
 int /*<<< orphan*/  USB_IFACE_INDEX_ANY ; 
 int USB_MAX_POWER ; 
 scalar_t__ USB_MODE_DEVICE ; 
 scalar_t__ USB_MODE_HOST ; 
 scalar_t__ USB_STATE_ADDRESSED ; 
 scalar_t__ USB_STATE_CONFIGURED ; 
 int USB_UNCONFIG_INDEX ; 
 int /*<<< orphan*/  USB_UNCONFIG_NO ; 
 int /*<<< orphan*/  usb_cdev_create (struct usb_device*) ; 
 scalar_t__ usb_config_parse (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_device_state (struct usb_device*,scalar_t__) ; 
 int /*<<< orphan*/  usb_unconfigure (struct usb_device*,int /*<<< orphan*/ ) ; 
 int usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 int usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_req_get_config_desc_full (struct usb_device*,int /*<<< orphan*/ *,struct usb_config_descriptor**,int) ; 
 scalar_t__ usbd_req_get_descriptor_ptr (struct usb_device*,struct usb_config_descriptor**,int) ; 
 scalar_t__ usbd_req_get_device_status (struct usb_device*,int /*<<< orphan*/ *,struct usb_status*) ; 
 scalar_t__ usbd_req_set_config (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_set_config_index(struct usb_device *udev, uint8_t index)
{
	struct usb_status ds;
	struct usb_config_descriptor *cdp;
	uint16_t power;
	uint16_t max_power;
	uint8_t selfpowered;
	uint8_t do_unlock;
	usb_error_t err;

	DPRINTFN(6, "udev=%p index=%d\n", udev, index);

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	usb_unconfigure(udev, 0);

	if (index == USB_UNCONFIG_INDEX) {
		/*
		 * Leave unallocated when unconfiguring the
		 * device. "usb_unconfigure()" will also reset
		 * the current config number and index.
		 */
		err = usbd_req_set_config(udev, NULL, USB_UNCONFIG_NO);
		if (udev->state == USB_STATE_CONFIGURED)
			usb_set_device_state(udev, USB_STATE_ADDRESSED);
		goto done;
	}
	/* get the full config descriptor */
	if (udev->flags.usb_mode == USB_MODE_DEVICE) {
		/* save some memory */
		err = usbd_req_get_descriptor_ptr(udev, &cdp, 
		    (UDESC_CONFIG << 8) | index);
	} else {
		/* normal request */
		err = usbd_req_get_config_desc_full(udev,
		    NULL, &cdp, index);
	}
	if (err) {
		goto done;
	}
	/* set the new config descriptor */

	udev->cdesc = cdp;

	/* Figure out if the device is self or bus powered. */
	selfpowered = 0;
	if ((!udev->flags.uq_bus_powered) &&
	    (cdp->bmAttributes & UC_SELF_POWERED) &&
	    (udev->flags.usb_mode == USB_MODE_HOST)) {
		/* May be self powered. */
		if (cdp->bmAttributes & UC_BUS_POWERED) {
			/* Must ask device. */
			err = usbd_req_get_device_status(udev, NULL, &ds);
			if (err) {
				DPRINTFN(0, "could not read "
				    "device status: %s\n",
				    usbd_errstr(err));
			} else if (UGETW(ds.wStatus) & UDS_SELF_POWERED) {
				selfpowered = 1;
			}
			DPRINTF("status=0x%04x \n",
				UGETW(ds.wStatus));
		} else
			selfpowered = 1;
	}
	DPRINTF("udev=%p cdesc=%p (addr %d) cno=%d attr=0x%02x, "
	    "selfpowered=%d, power=%d\n",
	    udev, cdp,
	    udev->address, cdp->bConfigurationValue, cdp->bmAttributes,
	    selfpowered, cdp->bMaxPower * 2);

	/* Check if we have enough power. */
	power = cdp->bMaxPower * 2;

	if (udev->parent_hub) {
		max_power = udev->parent_hub->hub->portpower;
	} else {
		max_power = USB_MAX_POWER;
	}

	if (power > max_power) {
		DPRINTFN(0, "power exceeded %d > %d\n", power, max_power);
		err = USB_ERR_NO_POWER;
		goto done;
	}
	/* Only update "self_powered" in USB Host Mode */
	if (udev->flags.usb_mode == USB_MODE_HOST) {
		udev->flags.self_powered = selfpowered;
	}
	udev->power = power;
	udev->curr_config_no = cdp->bConfigurationValue;
	udev->curr_config_index = index;
	usb_set_device_state(udev, USB_STATE_CONFIGURED);

	/* Set the actual configuration value. */
	err = usbd_req_set_config(udev, NULL, cdp->bConfigurationValue);
	if (err) {
		goto done;
	}

	err = usb_config_parse(udev, USB_IFACE_INDEX_ANY, USB_CFG_ALLOC);
	if (err) {
		goto done;
	}

	err = usb_config_parse(udev, USB_IFACE_INDEX_ANY, USB_CFG_INIT);
	if (err) {
		goto done;
	}

#if USB_HAVE_UGEN
	/* create device nodes for each endpoint */
	usb_cdev_create(udev);
#endif

done:
	DPRINTF("error=%s\n", usbd_errstr(err));
	if (err) {
		usb_unconfigure(udev, 0);
	}
	if (do_unlock)
		usbd_enum_unlock(udev);
	return (err);
}