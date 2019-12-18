#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wValue; int /*<<< orphan*/  wIndex; void* bRequest; void* bmRequestType; } ;
typedef  TYPE_1__ usb_device_request_t ;
typedef  void* uint8_t ;
typedef  size_t uint16_t ;
struct udl_softc {int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_DEFAULT_TIMEOUT ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,size_t) ; 
 int usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_errstr (int) ; 

__attribute__((used)) static int
udl_ctrl_msg(struct udl_softc *sc, uint8_t rt, uint8_t r,
    uint16_t index, uint16_t value, uint8_t *buf, size_t len)
{
	usb_device_request_t req;
	int error;

	req.bmRequestType = rt;
	req.bRequest = r;
	USETW(req.wIndex, index);
	USETW(req.wValue, value);
	USETW(req.wLength, len);

	error = usbd_do_request_flags(sc->sc_udev, NULL,
	    &req, buf, 0, NULL, USB_DEFAULT_TIMEOUT);

	DPRINTF("%s\n", usbd_errstr(error));

	return (error);
}