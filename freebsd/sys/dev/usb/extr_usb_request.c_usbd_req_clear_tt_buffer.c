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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_device_request {int* wIndex; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct TYPE_2__ {scalar_t__ bDeviceClass; scalar_t__ bDeviceProtocol; } ;
struct usb_device {TYPE_1__ ddesc; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 scalar_t__ UDCLASS_HUB ; 
 scalar_t__ UDPROTO_HSHUBSTT ; 
 int /*<<< orphan*/  UR_CLEAR_TT_BUFFER ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_OTHER ; 
 int /*<<< orphan*/  usbd_do_request (struct usb_device*,struct mtx*,struct usb_device_request*,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_req_clear_tt_buffer(struct usb_device *udev, struct mtx *mtx,
    uint8_t port, uint8_t addr, uint8_t type, uint8_t endpoint)
{
	struct usb_device_request req;
	uint16_t wValue;

	/* For single TT HUBs the port should be 1 */

	if (udev->ddesc.bDeviceClass == UDCLASS_HUB &&
	    udev->ddesc.bDeviceProtocol == UDPROTO_HSHUBSTT)
		port = 1;

	wValue = (endpoint & 0xF) | ((addr & 0x7F) << 4) |
	    ((endpoint & 0x80) << 8) | ((type & 3) << 12);

	req.bmRequestType = UT_WRITE_CLASS_OTHER;
	req.bRequest = UR_CLEAR_TT_BUFFER;
	USETW(req.wValue, wValue);
	req.wIndex[0] = port;
	req.wIndex[1] = 0;
	USETW(req.wLength, 0);
	return (usbd_do_request(udev, mtx, &req, 0));
}