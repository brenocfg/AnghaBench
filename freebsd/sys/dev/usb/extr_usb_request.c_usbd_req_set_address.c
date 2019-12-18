#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {TYPE_2__* bus; } ;
struct mtx {int dummy; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {scalar_t__ (* set_address ) (struct usb_device*,struct mtx*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UR_SET_ADDRESS ; 
 int /*<<< orphan*/  USB_DELAY_STATUS_STAGE ; 
 scalar_t__ USB_ERR_INVAL ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_DEVICE ; 
 scalar_t__ stub1 (struct usb_device*,struct mtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (struct mtx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_set_address_settle ; 
 scalar_t__ usbd_do_request_flags (struct usb_device*,struct mtx*,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

usb_error_t
usbd_req_set_address(struct usb_device *udev, struct mtx *mtx, uint16_t addr)
{
	struct usb_device_request req;
	usb_error_t err;

	DPRINTFN(6, "setting device address=%d\n", addr);

	req.bmRequestType = UT_WRITE_DEVICE;
	req.bRequest = UR_SET_ADDRESS;
	USETW(req.wValue, addr);
	USETW(req.wIndex, 0);
	USETW(req.wLength, 0);

	err = USB_ERR_INVAL;

	/* check if USB controller handles set address */
	if (udev->bus->methods->set_address != NULL)
		err = (udev->bus->methods->set_address) (udev, mtx, addr);

	if (err != USB_ERR_INVAL)
		goto done;

	/* Setting the address should not take more than 1 second ! */
	err = usbd_do_request_flags(udev, mtx, &req, NULL,
	    USB_DELAY_STATUS_STAGE, NULL, 1000);

done:
	/* allow device time to set new address */
	usb_pause_mtx(mtx,
	    USB_MS_TO_TICKS(usb_set_address_settle));

	return (err);
}