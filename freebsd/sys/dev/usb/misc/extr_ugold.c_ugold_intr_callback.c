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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct usb_xfer {int dummy; } ;
struct usb_page_cache {int dummy; } ;
struct ugold_softc {int sc_num_sensors; int* sc_valid; int /*<<< orphan*/ * sc_calib; int /*<<< orphan*/ * sc_sensor; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int,...) ; 
 int MIN (int,int) ; 
#define  UGOLD_CMD_DATA 131 
#define  UGOLD_CMD_INIT 130 
 size_t UGOLD_INNER ; 
 int UGOLD_MAX_SENSORS ; 
 size_t UGOLD_OUTER ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int ugold_ds75_temp (int,int) ; 
 int /*<<< orphan*/  usbd_copy_out (struct usb_page_cache*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 struct usb_page_cache* usbd_xfer_get_frame (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_max_len (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 
 struct ugold_softc* usbd_xfer_softc (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_status (struct usb_xfer*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ugold_intr_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct ugold_softc *sc = usbd_xfer_softc(xfer);
	struct usb_page_cache *pc;
	uint8_t buf[8];
	int temp;
	int len;

	usbd_xfer_status(xfer, &len, NULL, NULL, NULL);

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
		memset(buf, 0, sizeof(buf));

		pc = usbd_xfer_get_frame(xfer, 0);
		usbd_copy_out(pc, 0, buf, MIN(len, sizeof(buf)));

		switch (buf[0]) {
		case UGOLD_CMD_INIT:
			if (sc->sc_num_sensors)
				break;

			sc->sc_num_sensors = MIN(buf[1], UGOLD_MAX_SENSORS) /* XXX */ ;

			DPRINTF("%d sensor%s type ds75/12bit (temperature)\n",
			    sc->sc_num_sensors, (sc->sc_num_sensors == 1) ? "" : "s");
			break;
		case UGOLD_CMD_DATA:
			switch (buf[1]) {
			case 4:
				temp = ugold_ds75_temp(buf[4], buf[5]);
				sc->sc_sensor[UGOLD_OUTER] = temp + sc->sc_calib[UGOLD_OUTER];
				sc->sc_valid[UGOLD_OUTER] = 1;
				/* FALLTHROUGH */
			case 2:
				temp = ugold_ds75_temp(buf[2], buf[3]);
				sc->sc_sensor[UGOLD_INNER] = temp + sc->sc_calib[UGOLD_INNER];
				sc->sc_valid[UGOLD_INNER] = 1;
				break;
			default:
				DPRINTF("invalid data length (%d bytes)\n", buf[1]);
			}
			break;
		default:
			DPRINTF("unknown command 0x%02x\n", buf[0]);
			break;
		}
		/* FALLTHROUGH */
	case USB_ST_SETUP:
tr_setup:
		usbd_xfer_set_frame_len(xfer, 0, usbd_xfer_max_len(xfer));
		usbd_transfer_submit(xfer);
		break;
	default:			/* Error */
		if (error != USB_ERR_CANCELLED) {
			/* try clear stall first */
			usbd_xfer_set_stall(xfer);
			goto tr_setup;
		}
		break;
	}
}