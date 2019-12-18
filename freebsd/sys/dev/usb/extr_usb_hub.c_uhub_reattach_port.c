#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  int uint8_t ;
typedef  int uint16_t ;
struct usb_device {int speed; int depth; int /*<<< orphan*/  bus; TYPE_3__* parent_hub; TYPE_1__* hub; } ;
struct TYPE_8__ {int port_status; int port_change; } ;
struct uhub_softc {scalar_t__ sc_disable_enumeration; struct usb_device* sc_udev; TYPE_4__ sc_st; int /*<<< orphan*/  sc_dev; } ;
typedef  enum usb_hc_mode { ____Placeholder_usb_hc_mode } usb_hc_mode ;
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;
struct TYPE_6__ {int usb_mode; } ;
struct TYPE_7__ {TYPE_2__ flags; } ;
struct TYPE_5__ {int ports; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  UHF_C_PORT_CONNECTION ; 
 int /*<<< orphan*/  UHF_PORT_ENABLE ; 
 int /*<<< orphan*/  UHF_PORT_SUSPEND ; 
 int UPS_CURRENT_CONNECT_STATUS ; 
 int UPS_C_CONNECT_STATUS ; 
#define  UPS_HIGH_SPEED 133 
#define  UPS_LOW_SPEED 132 
 int UPS_OTHER_SPEED ; 
 int UPS_PORT_ENABLED ; 
 int UPS_PORT_MODE_DEVICE ; 
 int UPS_PORT_POWER ; 
 int UPS_PORT_POWER_SS ; 
 int UPS_SUSPEND ; 
 int USB_MODE_DEVICE ; 
 int USB_MODE_HOST ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
#define  USB_SPEED_FULL 131 
#define  USB_SPEED_HIGH 130 
#define  USB_SPEED_LOW 129 
#define  USB_SPEED_SUPER 128 
 scalar_t__ uhub_read_port_status (struct uhub_softc*,int) ; 
 struct usb_device* usb_alloc_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device*,int,int,int,int,int) ; 
 struct usb_device* usb_bus_port_get_device (int /*<<< orphan*/ ,int) ; 
 scalar_t__ usb_disable_enumeration ; 
 int /*<<< orphan*/  usb_free_device (struct usb_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_pause_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_port_powerup_delay ; 
 int usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_req_clear_port_feature (struct usb_device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_reset_port (struct usb_device*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ usbd_req_set_hub_u1_timeout (struct usb_device*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ usbd_req_set_hub_u2_timeout (struct usb_device*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static usb_error_t
uhub_reattach_port(struct uhub_softc *sc, uint8_t portno)
{
	struct usb_device *child;
	struct usb_device *udev;
	enum usb_dev_speed speed;
	enum usb_hc_mode mode;
	usb_error_t err;
	uint16_t power_mask;
	uint8_t timeout;

	DPRINTF("reattaching port %d\n", portno);

	timeout = 0;
	udev = sc->sc_udev;
	child = usb_bus_port_get_device(udev->bus,
	    udev->hub->ports + portno - 1);

repeat:

	/* first clear the port connection change bit */

	err = usbd_req_clear_port_feature(udev, NULL,
	    portno, UHF_C_PORT_CONNECTION);

	if (err)
		goto error;

	/* check if there is a child */

	if (child != NULL) {
		/*
		 * Free USB device and all subdevices, if any.
		 */
		usb_free_device(child, 0);
		child = NULL;
	}
	/* get fresh status */

	err = uhub_read_port_status(sc, portno);
	if (err)
		goto error;

#if USB_HAVE_DISABLE_ENUM
	/* check if we should skip enumeration from this USB HUB */
	if (usb_disable_enumeration != 0 ||
	    sc->sc_disable_enumeration != 0) {
		DPRINTF("Enumeration is disabled!\n");
		goto error;
	}
#endif
	/* check if nothing is connected to the port */

	if (!(sc->sc_st.port_status & UPS_CURRENT_CONNECT_STATUS))
		goto error;

	/* check if there is no power on the port and print a warning */

	switch (udev->speed) {
	case USB_SPEED_HIGH:
	case USB_SPEED_FULL:
	case USB_SPEED_LOW:
		power_mask = UPS_PORT_POWER;
		break;
	case USB_SPEED_SUPER:
		if (udev->parent_hub == NULL)
			power_mask = UPS_PORT_POWER;
		else
			power_mask = UPS_PORT_POWER_SS;
		break;
	default:
		power_mask = 0;
		break;
	}
	if (!(sc->sc_st.port_status & power_mask)) {
		DPRINTF("WARNING: strange, connected port %d "
		    "has no power\n", portno);
	}

	/* check if the device is in Host Mode */

	if (!(sc->sc_st.port_status & UPS_PORT_MODE_DEVICE)) {

		DPRINTF("Port %d is in Host Mode\n", portno);

		if (sc->sc_st.port_status & UPS_SUSPEND) {
			/*
			 * NOTE: Should not get here in SuperSpeed
			 * mode, because the HUB should report this
			 * bit as zero.
			 */
			DPRINTF("Port %d was still "
			    "suspended, clearing.\n", portno);
			err = usbd_req_clear_port_feature(udev,
			    NULL, portno, UHF_PORT_SUSPEND);
		}

		/* USB Host Mode */

		/* wait for maximum device power up time */

		usb_pause_mtx(NULL, 
		    USB_MS_TO_TICKS(usb_port_powerup_delay));

		/* reset port, which implies enabling it */

		err = usbd_req_reset_port(udev, NULL, portno);

		if (err) {
			DPRINTFN(0, "port %d reset "
			    "failed, error=%s\n",
			    portno, usbd_errstr(err));
			goto error;
		}
		/* get port status again, it might have changed during reset */

		err = uhub_read_port_status(sc, portno);
		if (err) {
			goto error;
		}
		/* check if something changed during port reset */

		if ((sc->sc_st.port_change & UPS_C_CONNECT_STATUS) ||
		    (!(sc->sc_st.port_status & UPS_CURRENT_CONNECT_STATUS))) {
			if (timeout) {
				DPRINTFN(0, "giving up port reset "
				    "- device vanished\n");
				goto error;
			}
			timeout = 1;
			goto repeat;
		}
	} else {
		DPRINTF("Port %d is in Device Mode\n", portno);
	}

	/*
	 * Figure out the device speed
	 */
	switch (udev->speed) {
	case USB_SPEED_HIGH:
		if (sc->sc_st.port_status & UPS_HIGH_SPEED)
			speed = USB_SPEED_HIGH;
		else if (sc->sc_st.port_status & UPS_LOW_SPEED)
			speed = USB_SPEED_LOW;
		else
			speed = USB_SPEED_FULL;
		break;
	case USB_SPEED_FULL:
		if (sc->sc_st.port_status & UPS_LOW_SPEED)
			speed = USB_SPEED_LOW;
		else
			speed = USB_SPEED_FULL;
		break;
	case USB_SPEED_LOW:
		speed = USB_SPEED_LOW;
		break;
	case USB_SPEED_SUPER:
		if (udev->parent_hub == NULL) {
			/* Root HUB - special case */
			switch (sc->sc_st.port_status & UPS_OTHER_SPEED) {
			case 0:
				speed = USB_SPEED_FULL;
				break;
			case UPS_LOW_SPEED:
				speed = USB_SPEED_LOW;
				break;
			case UPS_HIGH_SPEED:
				speed = USB_SPEED_HIGH;
				break;
			default:
				speed = USB_SPEED_SUPER;
				break;
			}
		} else {
			speed = USB_SPEED_SUPER;
		}
		break;
	default:
		/* same speed like parent */
		speed = udev->speed;
		break;
	}
	if (speed == USB_SPEED_SUPER) {
		err = usbd_req_set_hub_u1_timeout(udev, NULL,
		    portno, 128 - (2 * udev->depth));
		if (err) {
			DPRINTFN(0, "port %d U1 timeout "
			    "failed, error=%s\n",
			    portno, usbd_errstr(err));
		}
		err = usbd_req_set_hub_u2_timeout(udev, NULL,
		    portno, 128 - (2 * udev->depth));
		if (err) {
			DPRINTFN(0, "port %d U2 timeout "
			    "failed, error=%s\n",
			    portno, usbd_errstr(err));
		}
	}

	/*
	 * Figure out the device mode
	 *
	 * NOTE: This part is currently FreeBSD specific.
	 */
	if (udev->parent_hub != NULL) {
		/* inherit mode from the parent HUB */
		mode = udev->parent_hub->flags.usb_mode;
	} else if (sc->sc_st.port_status & UPS_PORT_MODE_DEVICE)
		mode = USB_MODE_DEVICE;
	else
		mode = USB_MODE_HOST;

	/* need to create a new child */
	child = usb_alloc_device(sc->sc_dev, udev->bus, udev,
	    udev->depth + 1, portno - 1, portno, speed, mode);
	if (child == NULL) {
		DPRINTFN(0, "could not allocate new device\n");
		goto error;
	}
	return (0);			/* success */

error:
	if (child != NULL) {
		/*
		 * Free USB device and all subdevices, if any.
		 */
		usb_free_device(child, 0);
		child = NULL;
	}
	if (err == 0) {
		if (sc->sc_st.port_status & UPS_PORT_ENABLED) {
			err = usbd_req_clear_port_feature(
			    sc->sc_udev, NULL,
			    portno, UHF_PORT_ENABLE);
		}
	}
	if (err) {
		DPRINTFN(0, "device problem (%s), "
		    "disabling port %d\n", usbd_errstr(err), portno);
	}
	return (err);
}