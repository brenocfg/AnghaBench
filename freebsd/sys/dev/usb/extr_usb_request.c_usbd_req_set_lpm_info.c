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
typedef  int uint8_t ;
struct usb_device_request {int* wIndex; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int UHF_PORT_L1 ; 
 int /*<<< orphan*/  UR_SET_AND_TEST ; 
 scalar_t__ USB_ERR_IOERROR ; 
 scalar_t__ USB_ERR_PENDING_REQUESTS ; 
 scalar_t__ USB_ERR_STALLED ; 
 scalar_t__ USB_ERR_TIMEOUT ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_OTHER ; 
 scalar_t__ usbd_do_request (struct usb_device*,struct mtx*,struct usb_device_request*,int*) ; 

usb_error_t
usbd_req_set_lpm_info(struct usb_device *udev, struct mtx *mtx,
    uint8_t port, uint8_t besl, uint8_t addr, uint8_t rwe)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t buf[1];

	req.bmRequestType = UT_WRITE_CLASS_OTHER;
	req.bRequest = UR_SET_AND_TEST;
	USETW(req.wValue, UHF_PORT_L1);
	req.wIndex[0] = (port & 0xF) | ((besl & 0xF) << 4);
	req.wIndex[1] = (addr & 0x7F) | (rwe ? 0x80 : 0x00);
	USETW(req.wLength, sizeof(buf));

	/* set default value in case of short transfer */
	buf[0] = 0x00;

	err = usbd_do_request(udev, mtx, &req, buf);
	if (err)
		return (err);

	switch (buf[0]) {
	case 0x00:	/* SUCCESS */
		break;
	case 0x10:	/* NYET */
		err = USB_ERR_PENDING_REQUESTS;
		break;
	case 0x11:	/* TIMEOUT */
		err = USB_ERR_TIMEOUT;
		break;
	case 0x30:	/* STALL */
		err = USB_ERR_STALLED;
		break;
	default:	/* reserved */
		err = USB_ERR_IOERROR;
		break;
	}
	return (err);
}