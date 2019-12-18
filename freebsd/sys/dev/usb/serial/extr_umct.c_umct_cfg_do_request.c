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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct umct_softc {int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; scalar_t__ sc_iface_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETDW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
umct_cfg_do_request(struct umct_softc *sc, uint8_t request,
    uint16_t len, uint32_t value)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t temp[4];

	if (len > 4)
		len = 4;
	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = request;
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, len);
	USETDW(temp, value);

	err = ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom, 
	    &req, temp, 0, 1000);
	if (err) {
		DPRINTFN(0, "device request failed, err=%s "
		    "(ignored)\n", usbd_errstr(err));
	}
	return;
}