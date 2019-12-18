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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint16_t ;
struct usb_port_status {int /*<<< orphan*/  wPortChange; int /*<<< orphan*/  wPortStatus; } ;
struct usb_device {int dummy; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int UGETW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UHF_BH_PORT_RESET ; 
 int /*<<< orphan*/  UHF_C_BH_PORT_RESET ; 
 int UPS_CURRENT_CONNECT_STATUS ; 
 int UPS_C_BH_PORT_RESET ; 
 int UPS_PORT_LINK_STATE_GET (int) ; 
#define  UPS_PORT_LS_COMP_MODE 131 
#define  UPS_PORT_LS_LOOPBACK 130 
#define  UPS_PORT_LS_SS_INA 129 
#define  UPS_PORT_LS_U3 128 
 scalar_t__ USB_ERR_TIMEOUT ; 
 int /*<<< orphan*/  USB_MS_TO_TICKS (scalar_t__) ; 
 int /*<<< orphan*/  usb_pause_mtx (struct mtx*,int /*<<< orphan*/ ) ; 
 scalar_t__ usb_port_reset_delay ; 
 scalar_t__ usb_port_reset_recovery ; 
 int /*<<< orphan*/  usbd_errstr (scalar_t__) ; 
 scalar_t__ usbd_req_clear_port_feature (struct usb_device*,struct mtx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_get_port_status (struct usb_device*,struct mtx*,struct usb_port_status*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_set_port_feature (struct usb_device*,struct mtx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_req_warm_reset_port(struct usb_device *udev, struct mtx *mtx,
    uint8_t port)
{
	struct usb_port_status ps;
	usb_error_t err;
	uint16_t n;
	uint16_t status;
	uint16_t change;

	DPRINTF("\n");

	err = usbd_req_get_port_status(udev, mtx, &ps, port);
	if (err)
		goto done;

	status = UGETW(ps.wPortStatus);

	switch (UPS_PORT_LINK_STATE_GET(status)) {
	case UPS_PORT_LS_U3:
	case UPS_PORT_LS_COMP_MODE:
	case UPS_PORT_LS_LOOPBACK:
	case UPS_PORT_LS_SS_INA:
		break;
	default:
		DPRINTF("Wrong state for warm reset\n");
		return (0);
	}

	/* clear any leftover warm port reset changes first */
	usbd_req_clear_port_feature(udev, mtx,
	    port, UHF_C_BH_PORT_RESET);

	/* set warm port reset */
	err = usbd_req_set_port_feature(udev, mtx,
	    port, UHF_BH_PORT_RESET);
	if (err)
		goto done;

	n = 0;
	while (1) {
		/* wait for the device to recover from reset */
		usb_pause_mtx(mtx, USB_MS_TO_TICKS(usb_port_reset_delay));
		n += usb_port_reset_delay;
		err = usbd_req_get_port_status(udev, mtx, &ps, port);
		if (err)
			goto done;

		status = UGETW(ps.wPortStatus);
		change = UGETW(ps.wPortChange);

		/* if the device disappeared, just give up */
		if (!(status & UPS_CURRENT_CONNECT_STATUS))
			goto done;

		/* check if reset is complete */
		if (change & UPS_C_BH_PORT_RESET)
			break;

		/* check for timeout */
		if (n > 1000) {
			n = 0;
			break;
		}
	}

	/* clear port reset first */
	err = usbd_req_clear_port_feature(
	    udev, mtx, port, UHF_C_BH_PORT_RESET);
	if (err)
		goto done;

	/* check for timeout */
	if (n == 0) {
		err = USB_ERR_TIMEOUT;
		goto done;
	}
	/* wait for the device to recover from reset */
	usb_pause_mtx(mtx, USB_MS_TO_TICKS(usb_port_reset_recovery));

done:
	DPRINTFN(2, "port %d warm reset returning error=%s\n",
	    port, usbd_errstr(err));
	return (err);
}