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
typedef  int uint16_t ;
struct usb_xfer {TYPE_1__* xroot; } ;
struct usb_interface {scalar_t__ parent_iface_index; int /*<<< orphan*/  alt_index; int /*<<< orphan*/ * subdev; int /*<<< orphan*/ * idesc; } ;
struct usb_device_request {int bmRequestType; scalar_t__* wIndex; int /*<<< orphan*/  bRequest; int /*<<< orphan*/ * wValue; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVMETHOD (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int ENOTTY ; 
 int ENXIO ; 
#define  UR_GET_INTERFACE 131 
#define  UR_SET_INTERFACE 130 
 int /*<<< orphan*/  USB_ERR_SHORT_XFER ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 int USB_HANDLE_REQUEST (int /*<<< orphan*/ *,struct usb_device_request*,void**,int*,int,scalar_t__*) ; 
 scalar_t__ USB_HR_COMPLETE_OK ; 
 scalar_t__ USB_HR_NOT_COMPLETE ; 
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 int UT_INTERFACE ; 
#define  UT_READ_INTERFACE 129 
#define  UT_WRITE_INTERFACE 128 
 scalar_t__ device_is_attached (int /*<<< orphan*/ *) ; 
 int usb_check_alt_setting (struct usb_device*,struct usb_interface*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_handle_request ; 
 int usb_reset_iface_endpoints (struct usb_device*,scalar_t__) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,scalar_t__) ; 

__attribute__((used)) static usb_error_t
usb_handle_iface_request(struct usb_xfer *xfer,
    void **ppdata, uint16_t *plen,
    struct usb_device_request req, uint16_t off, uint8_t state)
{
	struct usb_interface *iface;
	struct usb_interface *iface_parent;	/* parent interface */
	struct usb_device *udev = xfer->xroot->udev;
	int error;
	uint8_t iface_index;
	uint8_t temp_state;
	uint8_t do_unlock;

	if ((req.bmRequestType & 0x1F) == UT_INTERFACE) {
		iface_index = req.wIndex[0];	/* unicast */
	} else {
		iface_index = 0;	/* broadcast */
	}

	/*
	 * We need to protect against other threads doing probe and
	 * attach:
	 */
	USB_XFER_UNLOCK(xfer);

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	error = ENXIO;

tr_repeat:
	iface = usbd_get_iface(udev, iface_index);
	if ((iface == NULL) ||
	    (iface->idesc == NULL)) {
		/* end of interfaces non-existing interface */
		goto tr_stalled;
	}
	/* set initial state */

	temp_state = state;

	/* forward request to interface, if any */

	if ((error != 0) &&
	    (error != ENOTTY) &&
	    (iface->subdev != NULL) &&
	    device_is_attached(iface->subdev)) {
#if 0
		DEVMETHOD(usb_handle_request, NULL);	/* dummy */
#endif
		error = USB_HANDLE_REQUEST(iface->subdev,
		    &req, ppdata, plen,
		    off, &temp_state);
	}
	iface_parent = usbd_get_iface(udev, iface->parent_iface_index);

	if ((iface_parent == NULL) ||
	    (iface_parent->idesc == NULL)) {
		/* non-existing interface */
		iface_parent = NULL;
	}
	/* forward request to parent interface, if any */

	if ((error != 0) &&
	    (error != ENOTTY) &&
	    (iface_parent != NULL) &&
	    (iface_parent->subdev != NULL) &&
	    ((req.bmRequestType & 0x1F) == UT_INTERFACE) &&
	    (iface_parent->subdev != iface->subdev) &&
	    device_is_attached(iface_parent->subdev)) {
		error = USB_HANDLE_REQUEST(iface_parent->subdev,
		    &req, ppdata, plen, off, &temp_state);
	}
	if (error == 0) {
		/* negativly adjust pointer and length */
		*ppdata = ((uint8_t *)(*ppdata)) - off;
		*plen += off;

		if ((state == USB_HR_NOT_COMPLETE) &&
		    (temp_state == USB_HR_COMPLETE_OK))
			goto tr_short;
		else
			goto tr_valid;
	} else if (error == ENOTTY) {
		goto tr_stalled;
	}
	if ((req.bmRequestType & 0x1F) != UT_INTERFACE) {
		iface_index++;		/* iterate */
		goto tr_repeat;
	}
	if (state != USB_HR_NOT_COMPLETE) {
		/* we are complete */
		goto tr_valid;
	}
	switch (req.bmRequestType) {
	case UT_WRITE_INTERFACE:
		switch (req.bRequest) {
		case UR_SET_INTERFACE:
			/*
			 * We assume that the endpoints are the same
			 * across the alternate settings.
			 *
			 * Reset the endpoints, because re-attaching
			 * only a part of the device is not possible.
			 */
			error = usb_check_alt_setting(udev,
			    iface, req.wValue[0]);
			if (error) {
				DPRINTF("alt setting does not exist %s\n",
				    usbd_errstr(error));
				goto tr_stalled;
			}
			error = usb_reset_iface_endpoints(udev, iface_index);
			if (error) {
				DPRINTF("alt setting failed %s\n",
				    usbd_errstr(error));
				goto tr_stalled;
			}
			/* update the current alternate setting */
			iface->alt_index = req.wValue[0];
			break;

		default:
			goto tr_stalled;
		}
		break;

	case UT_READ_INTERFACE:
		switch (req.bRequest) {
		case UR_GET_INTERFACE:
			*ppdata = &iface->alt_index;
			*plen = 1;
			break;

		default:
			goto tr_stalled;
		}
		break;
	default:
		goto tr_stalled;
	}
tr_valid:
	if (do_unlock)
		usbd_enum_unlock(udev);
	USB_XFER_LOCK(xfer);
	return (0);

tr_short:
	if (do_unlock)
		usbd_enum_unlock(udev);
	USB_XFER_LOCK(xfer);
	return (USB_ERR_SHORT_XFER);

tr_stalled:
	if (do_unlock)
		usbd_enum_unlock(udev);
	USB_XFER_LOCK(xfer);
	return (USB_ERR_STALLED);
}