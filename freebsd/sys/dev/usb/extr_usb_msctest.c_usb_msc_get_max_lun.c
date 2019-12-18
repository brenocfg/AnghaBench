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
typedef  scalar_t__ uint8_t ;
struct usb_device_request {int bRequest; int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 scalar_t__ usbd_do_request (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,scalar_t__*) ; 

__attribute__((used)) static uint8_t
usb_msc_get_max_lun(struct usb_device *udev, uint8_t iface_index)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t buf = 0;


	/* The Get Max Lun command is a class-specific request. */
	req.bmRequestType = UT_READ_CLASS_INTERFACE;
	req.bRequest = 0xFE;		/* GET_MAX_LUN */
	USETW(req.wValue, 0);
	req.wIndex[0] = iface_index;
	req.wIndex[1] = 0;
	USETW(req.wLength, 1);

	err = usbd_do_request(udev, NULL, &req, &buf);
	if (err)
		buf = 0;

	return (buf);
}