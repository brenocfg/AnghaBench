#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_5__ {int bmRequestType; int bRequest; int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; } ;
typedef  TYPE_2__ usb_device_request_t ;
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  ue_udev; } ;
struct urndis_softc {int /*<<< orphan*/  sc_mtx; TYPE_1__ sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_SHORT_XFER_OK ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UT_READ ; 
 int /*<<< orphan*/  usbd_do_request_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static usb_error_t
urndis_ctrl_msg(struct urndis_softc *sc, uint8_t rt, uint8_t r,
    uint16_t index, uint16_t value, void *buf, uint16_t buflen)
{
	usb_device_request_t req;

	req.bmRequestType = rt;
	req.bRequest = r;
	USETW(req.wValue, value);
	USETW(req.wIndex, index);
	USETW(req.wLength, buflen);

	return (usbd_do_request_flags(sc->sc_ue.ue_udev,
	    &sc->sc_mtx, &req, buf, (rt & UT_READ) ?
	    USB_SHORT_XFER_OK : 0, NULL, 2000 /* ms */ ));
}