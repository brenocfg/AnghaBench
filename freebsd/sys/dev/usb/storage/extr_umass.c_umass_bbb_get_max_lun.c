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
typedef  scalar_t__ uint8_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct umass_softc {char* sc_name; int /*<<< orphan*/  sc_udev; scalar_t__ sc_iface_no; } ;

/* Variables and functions */
 int /*<<< orphan*/  UR_BBB_GET_MAX_LUN ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UT_READ_CLASS_INTERFACE ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 scalar_t__ usbd_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,scalar_t__*) ; 
 char* usbd_errstr (scalar_t__) ; 

__attribute__((used)) static uint8_t
umass_bbb_get_max_lun(struct umass_softc *sc)
{
	struct usb_device_request req;
	usb_error_t err;
	uint8_t buf = 0;

	/* The Get Max Lun command is a class-specific request. */
	req.bmRequestType = UT_READ_CLASS_INTERFACE;
	req.bRequest = UR_BBB_GET_MAX_LUN;
	USETW(req.wValue, 0);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, 1);

	err = usbd_do_request(sc->sc_udev, NULL, &req, &buf);
	if (err) {
		buf = 0;

		/* Device doesn't support Get Max Lun request. */
		printf("%s: Get Max Lun not supported (%s)\n",
		    sc->sc_name, usbd_errstr(err));
	}
	return (buf);
}