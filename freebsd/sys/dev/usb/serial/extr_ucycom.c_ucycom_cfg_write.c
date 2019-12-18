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
typedef  void* uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct usb_device_request {int /*<<< orphan*/  wLength; scalar_t__* wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct ucycom_softc {int sc_flen; int* sc_temp_cfg; int /*<<< orphan*/  sc_ucom; int /*<<< orphan*/  sc_udev; scalar_t__ sc_iface_no; int /*<<< orphan*/  sc_fid; void* sc_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UHID_FEATURE_REPORT ; 
 int /*<<< orphan*/  UR_SET_REPORT ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USETW2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_CLASS_INTERFACE ; 
 scalar_t__ ucom_cfg_do_request (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct usb_device_request*,int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 

__attribute__((used)) static void
ucycom_cfg_write(struct ucycom_softc *sc, uint32_t baud, uint8_t cfg)
{
	struct usb_device_request req;
	uint16_t len;
	usb_error_t err;

	len = sc->sc_flen;
	if (len > sizeof(sc->sc_temp_cfg)) {
		len = sizeof(sc->sc_temp_cfg);
	}
	sc->sc_cfg = cfg;

	req.bmRequestType = UT_WRITE_CLASS_INTERFACE;
	req.bRequest = UR_SET_REPORT;
	USETW2(req.wValue, UHID_FEATURE_REPORT, sc->sc_fid);
	req.wIndex[0] = sc->sc_iface_no;
	req.wIndex[1] = 0;
	USETW(req.wLength, len);

	sc->sc_temp_cfg[0] = (baud & 0xff);
	sc->sc_temp_cfg[1] = (baud >> 8) & 0xff;
	sc->sc_temp_cfg[2] = (baud >> 16) & 0xff;
	sc->sc_temp_cfg[3] = (baud >> 24) & 0xff;
	sc->sc_temp_cfg[4] = cfg;

	err = ucom_cfg_do_request(sc->sc_udev, &sc->sc_ucom,
	    &req, sc->sc_temp_cfg, 0, 1000);
	if (err) {
		DPRINTFN(0, "device request failed, err=%s "
		    "(ignored)\n", usbd_errstr(err));
	}
}