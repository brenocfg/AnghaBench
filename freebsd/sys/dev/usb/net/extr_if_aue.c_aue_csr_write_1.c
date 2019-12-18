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
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; scalar_t__* wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct aue_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUE_UR_WRITEREG ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 scalar_t__ uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,scalar_t__*,int) ; 

__attribute__((used)) static void
aue_csr_write_1(struct aue_softc *sc, uint16_t reg, uint8_t val)
{
	struct usb_device_request req;

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = AUE_UR_WRITEREG;
	req.wValue[0] = val;
	req.wValue[1] = 0;
	USETW(req.wIndex, reg);
	USETW(req.wLength, 1);

	if (uether_do_request(&sc->sc_ue, &req, &val, 1000)) {
		/* error ignored */
	}
}