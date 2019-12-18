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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_hub_ss_descriptor {int dummy; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDESC_SS_HUB ; 
 int /*<<< orphan*/  UR_GET_DESCRIPTOR ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_READ_CLASS_DEVICE ; 
 int /*<<< orphan*/  usbd_do_request (struct usb_device*,struct mtx*,struct usb_device_request*,struct usb_hub_ss_descriptor*) ; 

usb_error_t
usbd_req_get_ss_hub_descriptor(struct usb_device *udev, struct mtx *mtx,
    struct usb_hub_ss_descriptor *hd, uint8_t nports)
{
	struct usb_device_request req;
	uint16_t len = sizeof(*hd) - 32 + 1 + ((nports + 7) / 8);

	req.bmRequestType = UT_READ_CLASS_DEVICE;
	req.bRequest = UR_GET_DESCRIPTOR;
	USETW2(req.wValue, UDESC_SS_HUB, 0);
	USETW(req.wIndex, 0);
	USETW(req.wLength, len);
	return (usbd_do_request(udev, mtx, &req, hd));
}