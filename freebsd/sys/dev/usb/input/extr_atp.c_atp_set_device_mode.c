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
struct atp_softc {scalar_t__ sc_family; scalar_t__* sc_mode_bytes; int /*<<< orphan*/  sc_usb_device; } ;
typedef  scalar_t__ interface_mode ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 scalar_t__ HID_MODE ; 
 scalar_t__ RAW_SENSOR_MODE ; 
 scalar_t__ TRACKPAD_FAMILY_FOUNTAIN_GEYSER ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ usbd_req_get_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ usbd_req_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static usb_error_t
atp_set_device_mode(struct atp_softc *sc, interface_mode newMode)
{
	uint8_t mode_value;
	usb_error_t err;

	if ((newMode != RAW_SENSOR_MODE) && (newMode != HID_MODE))
		return (USB_ERR_INVAL);

	if ((newMode == RAW_SENSOR_MODE) &&
	    (sc->sc_family == TRACKPAD_FAMILY_FOUNTAIN_GEYSER))
		mode_value = (uint8_t)0x04;
	else
		mode_value = newMode;

	err = usbd_req_get_report(sc->sc_usb_device, NULL /* mutex */,
	    sc->sc_mode_bytes, sizeof(sc->sc_mode_bytes), 0 /* interface idx */,
	    0x03 /* type */, 0x00 /* id */);
	if (err != USB_ERR_NORMAL_COMPLETION) {
		DPRINTF("Failed to read device mode (%d)\n", err);
		return (err);
	}

	if (sc->sc_mode_bytes[0] == mode_value)
		return (err);

	/*
	 * XXX Need to wait at least 250ms for hardware to get
	 * ready. The device mode handling appears to be handled
	 * asynchronously and we should not issue these commands too
	 * quickly.
	 */
	pause("WHW", hz / 4);

	sc->sc_mode_bytes[0] = mode_value;
	return (usbd_req_set_report(sc->sc_usb_device, NULL /* mutex */,
	    sc->sc_mode_bytes, sizeof(sc->sc_mode_bytes), 0 /* interface idx */,
	    0x03 /* type */, 0x00 /* id */));
}