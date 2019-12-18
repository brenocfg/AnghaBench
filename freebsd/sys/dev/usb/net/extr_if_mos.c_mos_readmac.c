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
typedef  int /*<<< orphan*/  u_char ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct mos_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  MOS_MAC ; 
 int /*<<< orphan*/  MOS_UR_READREG ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 scalar_t__ uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
mos_readmac(struct mos_softc *sc, u_char *mac)
{
	struct usb_device_request req;
	usb_error_t err;

	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = MOS_UR_READREG;
	USETW(req.wValue, 0);
	USETW(req.wIndex, MOS_MAC);
	USETW(req.wLength, ETHER_ADDR_LEN);

	err = uether_do_request(&sc->sc_ue, &req, mac, 1000);

	if (err) {
		return (-1);
	}
	return (0);
}