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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {int re_enumerate_wait; int /*<<< orphan*/  next_config_index; int /*<<< orphan*/  port_no; int /*<<< orphan*/ * parent_hub; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  UHF_PORT_ENABLE ; 
 int /*<<< orphan*/  USB_IFACE_INDEX_ANY ; 
 scalar_t__ USB_MODE_HOST ; 
 void* USB_RE_ENUM_DONE ; 
#define  USB_RE_ENUM_PWR_OFF 130 
#define  USB_RE_ENUM_SET_CONFIG 129 
#define  USB_RE_ENUM_START 128 
 int /*<<< orphan*/  USB_UNCONFIG_INDEX ; 
 int /*<<< orphan*/  usb_probe_and_attach (struct usb_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_errstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_req_clear_port_feature (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_req_re_enumerate (struct usb_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_set_config_index (struct usb_device*,int /*<<< orphan*/ ) ; 

void
uhub_explore_handle_re_enumerate(struct usb_device *child)
{
	uint8_t do_unlock;
	usb_error_t err;

	/* check if device should be re-enumerated */
	if (child->flags.usb_mode != USB_MODE_HOST)
		return;

	do_unlock = usbd_enum_lock(child);
	switch (child->re_enumerate_wait) {
	case USB_RE_ENUM_START:
		err = usbd_set_config_index(child,
		    USB_UNCONFIG_INDEX);
		if (err != 0) {
			DPRINTF("Unconfigure failed: %s: Ignored.\n",
			    usbd_errstr(err));
		}
		if (child->parent_hub == NULL) {
			/* the root HUB cannot be re-enumerated */
			DPRINTFN(6, "cannot reset root HUB\n");
			err = 0;
		} else {
			err = usbd_req_re_enumerate(child, NULL);
		}
		if (err == 0)
			err = usbd_set_config_index(child, 0);
		if (err == 0) {
			err = usb_probe_and_attach(child,
			    USB_IFACE_INDEX_ANY);
		}
		child->re_enumerate_wait = USB_RE_ENUM_DONE;
		break;

	case USB_RE_ENUM_PWR_OFF:
		/* get the device unconfigured */
		err = usbd_set_config_index(child,
		    USB_UNCONFIG_INDEX);
		if (err) {
			DPRINTFN(0, "Could not unconfigure "
			    "device (ignored)\n");
		}
		if (child->parent_hub == NULL) {
			/* the root HUB cannot be re-enumerated */
			DPRINTFN(6, "cannot set port feature\n");
			err = 0;
		} else {
			/* clear port enable */
			err = usbd_req_clear_port_feature(child->parent_hub,
			    NULL, child->port_no, UHF_PORT_ENABLE);
			if (err) {
				DPRINTFN(0, "Could not disable port "
				    "(ignored)\n");
			}
		}
		child->re_enumerate_wait = USB_RE_ENUM_DONE;
		break;

	case USB_RE_ENUM_SET_CONFIG:
		err = usbd_set_config_index(child,
		    child->next_config_index);
		if (err != 0) {
			DPRINTF("Configure failed: %s: Ignored.\n",
			    usbd_errstr(err));
		} else {
			err = usb_probe_and_attach(child,
			    USB_IFACE_INDEX_ANY);
		}
		child->re_enumerate_wait = USB_RE_ENUM_DONE;
		break;

	default:
		child->re_enumerate_wait = USB_RE_ENUM_DONE;
		break;
	}
	if (do_unlock)
		usbd_enum_unlock(child);
}