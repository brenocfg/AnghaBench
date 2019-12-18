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
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct udav_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  UDAV_REQ_REG_WRITE1 ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_WRITE_VENDOR_DEVICE ; 
 int uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
udav_csr_write1(struct udav_softc *sc, uint16_t offset,
    uint8_t ch)
{
	struct usb_device_request req;

	offset &= 0xff;

	req.bmRequestType = UT_WRITE_VENDOR_DEVICE;
	req.bRequest = UDAV_REQ_REG_WRITE1;
	USETW(req.wValue, ch);
	USETW(req.wIndex, offset);
	USETW(req.wLength, 0x0000);

	return (uether_do_request(&sc->sc_ue, &req, NULL, 1000));
}