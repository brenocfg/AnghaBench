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
typedef  int /*<<< orphan*/  usb_timeout_t ;
typedef  scalar_t__ usb_error_t ;
typedef  void uint8_t ;
typedef  scalar_t__ uint16_t ;
struct usb_process {int /*<<< orphan*/  up_mtx; } ;
struct usb_device_request {int bmRequestType; int /*<<< orphan*/  wLength; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int UE_DIR_IN ; 
 scalar_t__ UGETW (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_ERR_IOERROR ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ usb_proc_is_gone (struct usb_process*) ; 
 scalar_t__ usbd_do_request_flags (struct usb_device*,int /*<<< orphan*/ ,struct usb_device_request*,void*,scalar_t__,scalar_t__*,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_do_request_proc(struct usb_device *udev, struct usb_process *pproc,
    struct usb_device_request *req, void *data, uint16_t flags,
    uint16_t *actlen, usb_timeout_t timeout)
{
	usb_error_t err;
	uint16_t len;

	/* get request data length */
	len = UGETW(req->wLength);

	/* check if the device is being detached */
	if (usb_proc_is_gone(pproc)) {
		err = USB_ERR_IOERROR;
		goto done;
	}

	/* forward the USB request */
	err = usbd_do_request_flags(udev, pproc->up_mtx,
	    req, data, flags, actlen, timeout);

done:
	/* on failure we zero the data */
	/* on short packet we zero the unused data */
	if ((len != 0) && (req->bmRequestType & UE_DIR_IN)) {
		if (err)
			memset(data, 0, len);
		else if (actlen && *actlen != len)
			memset(((uint8_t *)data) + *actlen, 0, len - *actlen);
	}
	return (err);
}