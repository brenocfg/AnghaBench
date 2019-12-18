#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int usb_timeout_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_8__ {int self_suspended; scalar_t__ usb_mode; } ;
struct usb_device {struct usb_device* parent_hub; int /*<<< orphan*/  port_no; TYPE_4__* bus; TYPE_2__ flags; TYPE_1__* hub; } ;
struct TYPE_10__ {TYPE_3__* methods; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* device_suspend ) (struct usb_device*) ;} ;
struct TYPE_7__ {scalar_t__ nports; scalar_t__ ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 int /*<<< orphan*/  UF_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  UHF_PORT_SUSPEND ; 
 int /*<<< orphan*/  UPS_PORT_LS_U3 ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_4__*) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (int) ; 
 int /*<<< orphan*/  stub1 (struct usb_device*) ; 
 struct usb_device* usb_bus_port_get_device (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  usb_dev_resume_peer (struct usb_device*) ; 
 scalar_t__ usb_device_20_compatible (struct usb_device*) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_peer_can_wakeup (struct usb_device*) ; 
 int usb_peer_should_wakeup (struct usb_device*) ; 
 int usb_port_resume_delay ; 
 int usb_suspend_resume (struct usb_device*,int) ; 
 int usbd_get_dma_delay (struct usb_device*) ; 
 int usbd_req_clear_device_feature (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbd_req_clear_port_feature (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_req_set_device_feature (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int usbd_req_set_port_feature (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_req_set_port_link_state (struct usb_device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_sr_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_sr_unlock (struct usb_device*) ; 

__attribute__((used)) static void
usb_dev_suspend_peer(struct usb_device *udev)
{
	struct usb_device *child;
	int err;
	uint8_t x;
	uint8_t nports;

repeat:
	/* be NULL safe */
	if (udev == NULL)
		return;

	/* check if already suspended */
	if (udev->flags.self_suspended)
		return;

	/* we need a parent HUB to do suspend */
	if (udev->parent_hub == NULL)
		return;

	DPRINTF("udev=%p\n", udev);

	/* check if the current device is a HUB */
	if (udev->hub != NULL) {
		nports = udev->hub->nports;

		/* check if all devices on the HUB are suspended */
		for (x = 0; x != nports; x++) {
			child = usb_bus_port_get_device(udev->bus,
			    udev->hub->ports + x);

			if (child == NULL)
				continue;

			if (child->flags.self_suspended)
				continue;

			DPRINTFN(1, "Port %u is busy on the HUB!\n", x + 1);
			return;
		}
	}

	if (usb_peer_can_wakeup(udev)) {
		/*
		 * This request needs to be done before we set
		 * "udev->flags.self_suspended":
		 */

		/* allow device to do remote wakeup */
		err = usbd_req_set_device_feature(udev,
		    NULL, UF_DEVICE_REMOTE_WAKEUP);
		if (err) {
			DPRINTFN(0, "Setting device "
			    "remote wakeup failed\n");
		}
	}

	USB_BUS_LOCK(udev->bus);
	/*
	 * Checking for suspend condition and setting suspended bit
	 * must be atomic!
	 */
	err = usb_peer_should_wakeup(udev);
	if (err == 0) {
		/*
		 * Set that this device is suspended. This variable
		 * must be set before calling USB controller suspend
		 * callbacks.
		 */
		udev->flags.self_suspended = 1;
	}
	USB_BUS_UNLOCK(udev->bus);

	if (err != 0) {
		if (usb_peer_can_wakeup(udev)) {
			/* allow device to do remote wakeup */
			err = usbd_req_clear_device_feature(udev,
			    NULL, UF_DEVICE_REMOTE_WAKEUP);
			if (err) {
				DPRINTFN(0, "Setting device "
				    "remote wakeup failed\n");
			}
		}

		if (udev->flags.usb_mode == USB_MODE_DEVICE) {
			/* resume parent HUB first */
			usb_dev_resume_peer(udev->parent_hub);

			/* reduce chance of instant resume failure by waiting a little bit */
			usb_pause_mtx(NULL, USB_MS_TO_TICKS(20));

			/* resume current port (Valid in Host and Device Mode) */
			err = usbd_req_clear_port_feature(udev->parent_hub,
			    NULL, udev->port_no, UHF_PORT_SUSPEND);

			/* resume settle time */
			usb_pause_mtx(NULL, USB_MS_TO_TICKS(usb_port_resume_delay));
		}
		DPRINTF("Suspend was cancelled!\n");
		return;
	}

	usbd_sr_lock(udev);

	/* notify all sub-devices about suspend */
	err = usb_suspend_resume(udev, 1);

	usbd_sr_unlock(udev);

	if (udev->bus->methods->device_suspend != NULL) {
		usb_timeout_t temp;

		/* suspend device on the USB controller */
		(udev->bus->methods->device_suspend) (udev);

		/* do DMA delay */
		temp = usbd_get_dma_delay(udev);
		if (temp != 0)
			usb_pause_mtx(NULL, USB_MS_TO_TICKS(temp));

	}

	if (usb_device_20_compatible(udev)) {
		/* suspend current port */
		err = usbd_req_set_port_feature(udev->parent_hub,
		    NULL, udev->port_no, UHF_PORT_SUSPEND);
		if (err) {
			DPRINTFN(0, "Suspending port failed\n");
			return;
		}
	} else {
		/* suspend current port */
		err = usbd_req_set_port_link_state(udev->parent_hub,
		    NULL, udev->port_no, UPS_PORT_LS_U3);
		if (err) {
			DPRINTFN(0, "Suspending port failed\n");
			return;
		}
	}

	udev = udev->parent_hub;
	goto repeat;
}