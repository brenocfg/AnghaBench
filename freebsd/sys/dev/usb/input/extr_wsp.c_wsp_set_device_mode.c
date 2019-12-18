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
struct wsp_softc {int /*<<< orphan*/  sc_usb_device; struct wsp_dev_params* sc_params; } ;
struct wsp_dev_params {scalar_t__ tp_type; size_t um_switch_idx; int /*<<< orphan*/  um_req_idx; int /*<<< orphan*/  um_req_val; int /*<<< orphan*/  iface_index; int /*<<< orphan*/  um_size; scalar_t__ um_switch_off; scalar_t__ um_switch_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,scalar_t__) ; 
 scalar_t__ TYPE3 ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 scalar_t__ usbd_req_get_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_set_report (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
wsp_set_device_mode(struct wsp_softc *sc, uint8_t on)
{
	const struct wsp_dev_params *params = sc->sc_params;
	uint8_t	mode_bytes[8];
	usb_error_t err;

	/* Type 3 does not require a mode switch */
	if (params->tp_type == TYPE3)
		return 0;

	err = usbd_req_get_report(sc->sc_usb_device, NULL,
	    mode_bytes, params->um_size, params->iface_index,
	    params->um_req_val, params->um_req_idx);

	if (err != USB_ERR_NORMAL_COMPLETION) {
		DPRINTF("Failed to read device mode (%d)\n", err);
		return (err);
	}

	/*
	 * XXX Need to wait at least 250ms for hardware to get
	 * ready. The device mode handling appears to be handled
	 * asynchronously and we should not issue these commands too
	 * quickly.
	 */
	pause("WHW", hz / 4);

	mode_bytes[params->um_switch_idx] = 
	    on ? params->um_switch_on : params->um_switch_off;

	return (usbd_req_set_report(sc->sc_usb_device, NULL,
	    mode_bytes, params->um_size, params->iface_index, 
	    params->um_req_val, params->um_req_idx));
}