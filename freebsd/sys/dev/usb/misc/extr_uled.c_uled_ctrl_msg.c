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
typedef  void* uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; void* bRequest; void* bmRequestType; } ;
struct uled_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
uled_ctrl_msg(struct uled_softc *sc, uint8_t rt, uint8_t reqno,
    uint16_t value, uint16_t index, void *buf, uint16_t buflen)
{
	struct usb_device_request req;

	req.bmRequestType = rt;
	req.bRequest = reqno;
	USETW(req.wValue, value);
	USETW(req.wIndex, index);
	USETW(req.wLength, buflen);

	return (usbd_do_request_flags(sc->sc_udev, &sc->sc_mtx, &req, buf,
	    0, NULL, 2000));
}