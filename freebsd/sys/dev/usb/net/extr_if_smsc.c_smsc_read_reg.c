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
typedef  int uint32_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/  wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct smsc_softc {int /*<<< orphan*/  sc_ue; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  SMSC_LOCK_ASSERT (struct smsc_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SMSC_UR_READ_REG ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_VENDOR_DEVICE ; 
 int le32toh (int) ; 
 int /*<<< orphan*/  smsc_warn_printf (struct smsc_softc*,char*,int) ; 
 scalar_t__ uether_do_request (int /*<<< orphan*/ *,struct usb_device_request*,int*,int) ; 

__attribute__((used)) static int
smsc_read_reg(struct smsc_softc *sc, uint32_t off, uint32_t *data)
{
	struct usb_device_request req;
	uint32_t buf;
	usb_error_t err;

	SMSC_LOCK_ASSERT(sc, MA_OWNED);

	req.bmRequestType = UT_READ_VENDOR_DEVICE;
	req.bRequest = SMSC_UR_READ_REG;
	USETW(req.wValue, 0);
	USETW(req.wIndex, off);
	USETW(req.wLength, 4);

	err = uether_do_request(&sc->sc_ue, &req, &buf, 1000);
	if (err != 0)
		smsc_warn_printf(sc, "Failed to read register 0x%0x\n", off);

	*data = le32toh(buf);
	
	return (err);
}