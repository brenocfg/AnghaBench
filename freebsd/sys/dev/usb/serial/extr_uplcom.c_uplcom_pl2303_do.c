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
typedef  int usb_error_t ;
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; void* bRequest; void* bmRequestType; } ;
struct usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int usbd_do_request (struct usb_device*,int /*<<< orphan*/ *,struct usb_device_request*,void**) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 

__attribute__((used)) static usb_error_t
uplcom_pl2303_do(struct usb_device *udev, uint8_t req_type, uint8_t request,
    uint16_t value, uint16_t index, uint16_t length)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t buf[4];

	req.bmRequestType = req_type;
	req.bRequest = request;
	USETW(req.wValue, value);
	USETW(req.wIndex, index);
	USETW(req.wLength, length);

	err = usbd_do_request(udev, NULL, &req, buf);
	if (err) {
		DPRINTF("error=%s\n", usbd_errstr(err));
		return (1);
	}
	return (0);
}