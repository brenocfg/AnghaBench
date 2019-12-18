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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_port_status {int dummy; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UR_GET_STATUS ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_OTHER ; 
 int /*<<< orphan*/  usbd_do_request_flags (struct usb_device*,struct mtx*,struct usb_device_request*,struct usb_port_status*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

usb_error_t
usbd_req_get_port_status(struct usb_device *udev, struct mtx *mtx,
    struct usb_port_status *ps, uint8_t port)
{
	struct usb_device_request req;

	req.bmRequestType = UT_READ_CLASS_OTHER;
	req.bRequest = UR_GET_STATUS;
	USETW(req.wValue, 0);
	req.wIndex[0] = port;
	req.wIndex[1] = 0;
	USETW(req.wLength, sizeof(*ps));

	return (usbd_do_request_flags(udev, mtx, &req, ps, 0, NULL, 1000));
}