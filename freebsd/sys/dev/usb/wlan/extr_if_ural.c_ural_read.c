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
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ural_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_READ_MAC ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int le16toh (int) ; 
 scalar_t__ ural_do_request (struct ural_softc*,struct usb_device_request*,int*) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static uint16_t
ural_read(struct ural_softc *sc, uint16_t reg)
{
	struct usb_device_request req;
	usb_error_t error;
	uint16_t val;

	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = RAL_READ_MAC;
	USETW(req.wValue, 0);
	USETW(req.wIndex, reg);
	USETW(req.wLength, sizeof (uint16_t));

	error = ural_do_request(sc, &req, &val);
	if (error != 0) {
		device_printf(sc->sc_dev, "could not read MAC register: %s\n",
		    usbd_errstr(error));
		return 0;
	}

	return le16toh(val);
}