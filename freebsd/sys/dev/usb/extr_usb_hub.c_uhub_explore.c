#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_port {scalar_t__ restartcnt; } ;
struct usb_hub {scalar_t__ nports; struct usb_port* ports; struct uhub_softc* hubsoftc; } ;
struct TYPE_3__ {scalar_t__ self_suspended; } ;
struct usb_device {TYPE_1__ flags; int /*<<< orphan*/  address; struct usb_hub* hub; } ;
struct TYPE_4__ {int port_change; int port_status; } ;
struct uhub_softc {int sc_flags; TYPE_2__ sc_st; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  UHF_C_PORT_ENABLE ; 
 int /*<<< orphan*/  UHF_C_PORT_OVER_CURRENT ; 
 int UHUB_FLAG_DID_EXPLORE ; 
 int UPS_C_CONNECT_STATUS ; 
 int UPS_C_OVERCURRENT_INDICATOR ; 
 int UPS_C_PORT_ENABLED ; 
 int UPS_C_PORT_LINK_STATE ; 
 int UPS_C_SUSPEND ; 
 int UPS_PORT_ENABLED ; 
 scalar_t__ USB_ERR_NORMAL_COMPLETION ; 
 scalar_t__ USB_ERR_TOO_DEEP ; 
 scalar_t__ USB_RESTART_MAX ; 
 scalar_t__ uhub_explore_sub (struct uhub_softc*,struct usb_port*) ; 
 scalar_t__ uhub_is_too_deep (struct usb_device*) ; 
 scalar_t__ uhub_read_port_status (struct uhub_softc*,scalar_t__) ; 
 scalar_t__ uhub_reattach_port (struct uhub_softc*,scalar_t__) ; 
 scalar_t__ uhub_suspend_resume_port (struct uhub_softc*,scalar_t__) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 scalar_t__ usbd_req_clear_port_feature (struct usb_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usb_error_t
uhub_explore(struct usb_device *udev)
{
	struct usb_hub *hub;
	struct uhub_softc *sc;
	struct usb_port *up;
	usb_error_t err;
	uint8_t portno;
	uint8_t x;
	uint8_t do_unlock;

	hub = udev->hub;
	sc = hub->hubsoftc;

	DPRINTFN(11, "udev=%p addr=%d\n", udev, udev->address);

	/* ignore devices that are too deep */
	if (uhub_is_too_deep(udev))
		return (USB_ERR_TOO_DEEP);

	/* check if device is suspended */
	if (udev->flags.self_suspended) {
		/* need to wait until the child signals resume */
		DPRINTF("Device is suspended!\n");
		return (0);
	}

	/*
	 * Make sure we don't race against user-space applications
	 * like LibUSB:
	 */
	do_unlock = usbd_enum_lock(udev);

	for (x = 0; x != hub->nports; x++) {
		up = hub->ports + x;
		portno = x + 1;

		err = uhub_read_port_status(sc, portno);
		if (err) {
			/* most likely the HUB is gone */
			break;
		}
		if (sc->sc_st.port_change & UPS_C_OVERCURRENT_INDICATOR) {
			DPRINTF("Overcurrent on port %u.\n", portno);
			err = usbd_req_clear_port_feature(
			    udev, NULL, portno, UHF_C_PORT_OVER_CURRENT);
			if (err) {
				/* most likely the HUB is gone */
				break;
			}
		}
		if (!(sc->sc_flags & UHUB_FLAG_DID_EXPLORE)) {
			/*
			 * Fake a connect status change so that the
			 * status gets checked initially!
			 */
			sc->sc_st.port_change |=
			    UPS_C_CONNECT_STATUS;
		}
		if (sc->sc_st.port_change & UPS_C_PORT_ENABLED) {
			err = usbd_req_clear_port_feature(
			    udev, NULL, portno, UHF_C_PORT_ENABLE);
			if (err) {
				/* most likely the HUB is gone */
				break;
			}
			if (sc->sc_st.port_change & UPS_C_CONNECT_STATUS) {
				/*
				 * Ignore the port error if the device
				 * has vanished !
				 */
			} else if (sc->sc_st.port_status & UPS_PORT_ENABLED) {
				DPRINTFN(0, "illegal enable change, "
				    "port %d\n", portno);
			} else {

				if (up->restartcnt == USB_RESTART_MAX) {
					/* XXX could try another speed ? */
					DPRINTFN(0, "port error, giving up "
					    "port %d\n", portno);
				} else {
					sc->sc_st.port_change |=
					    UPS_C_CONNECT_STATUS;
					up->restartcnt++;
				}
			}
		}
		if (sc->sc_st.port_change & UPS_C_CONNECT_STATUS) {
			err = uhub_reattach_port(sc, portno);
			if (err) {
				/* most likely the HUB is gone */
				break;
			}
		}
		if (sc->sc_st.port_change & (UPS_C_SUSPEND |
		    UPS_C_PORT_LINK_STATE)) {
			err = uhub_suspend_resume_port(sc, portno);
			if (err) {
				/* most likely the HUB is gone */
				break;
			}
		}
		err = uhub_explore_sub(sc, up);
		if (err) {
			/* no device(s) present */
			continue;
		}
		/* explore succeeded - reset restart counter */
		up->restartcnt = 0;
	}

	if (do_unlock)
		usbd_enum_unlock(udev);

	/* initial status checked */
	sc->sc_flags |= UHUB_FLAG_DID_EXPLORE;

	/* return success */
	return (USB_ERR_NORMAL_COMPLETION);
}