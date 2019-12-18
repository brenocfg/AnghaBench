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
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  UF_DEVICE_REMOTE_WAKEUP ; 
 int /*<<< orphan*/  UHF_PORT_CONNECTION ; 
 int /*<<< orphan*/  UR_SET_INTERFACE ; 
 int /*<<< orphan*/  USB_MS_HZ ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_VENDOR ; 
 scalar_t__ usbd_do_request_flags (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
u3g_sierra_init(struct usb_device *udev)
{
	struct usb_device_request req;

	req.bmRequestType = UT_VENDOR;
	req.bRequest = UR_SET_INTERFACE;
	USETW(req.wValue, UF_DEVICE_REMOTE_WAKEUP);
	USETW(req.wIndex, UHF_PORT_CONNECTION);
	USETW(req.wLength, 0);

	if (usbd_do_request_flags(udev, NULL, &req,
	    NULL, 0, NULL, USB_MS_HZ)) {
		/* ignore any errors */
	}
	return (0);
}